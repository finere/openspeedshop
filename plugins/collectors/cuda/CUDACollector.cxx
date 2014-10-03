////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014 Argo Navis Technologies. All Rights Reserved.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
// details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////

/** @file Definition of the CUDACollector class. */

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>
#include <cstring>
#include <map>
#include <vector>
 
#include "KrellInstitute/Messages/CUDA_data.h"

#include "AddressRange.hxx"
#include "StackTrace.hxx"

#include "CUDACollector.hxx"
#include "CUDAExecDetail.hxx"
#include "CUDAXferDetail.hxx"

using namespace boost;
using namespace OpenSpeedShop::Framework;
using namespace std;



/** Anonymous namespace hiding implementation details. */
namespace {

    /** Type returned for the CUDA kernel execution detail metrics. */
    typedef map<StackTrace, vector<CUDAExecDetail> > ExecDetails;

    /** Type returned for the CUDA data transfer detail metrics. */
    typedef map<StackTrace, vector<CUDAXferDetail> > XferDetails;

    /** Type of function invoked when visiting individual addresses. */
    typedef function<void (uint64_t)> AddressVisitor;

    /** Type of function invoked when visiting individual CUDA messages. */
    typedef function<
        void (const CBTF_cuda_data&, const CBTF_cuda_message&)
        > MessageVisitor;

    /**
     * Visitor extracting the unique addresses referenced by a CUDA message.
     */
    void extractUniqueAddresses(const CBTF_cuda_data& data,
                                const CBTF_cuda_message& message,
                                const AddressVisitor& visitor)
    {
        switch (message.type)
        {
            
        case EnqueueRequest:
            {
                const CUDA_EnqueueRequest& msg = 
                    message.CBTF_cuda_message_u.enqueue_request;
                
                for (uint32_t i = msg.call_site;
                     (i < data.stack_traces.stack_traces_len) &&
                         (data.stack_traces.stack_traces_val[i] != 0);
                     ++i)
                {
                    visitor(data.stack_traces.stack_traces_val[i]);
                }
            }
            break;
            
        case OverflowSamples:
            {
                const CUDA_OverflowSamples& msg =
                    message.CBTF_cuda_message_u.overflow_samples;
                
                for (uint32_t i = 0; i < msg.pcs.pcs_len; ++i)
                {
                    visitor(msg.pcs.pcs_val[i]);
                }
            }
            break;
            
        default:
            break;
        }
    }
    
    /** Visitor used to insert an address into a buffer of unique addresses. */
    void insertIntoAddressBuffer(uint64_t address, PCBuffer& buffer)
    {
        UpdatePCBuffer(address, &buffer);
    }

    /** Visitor used to insert an address into a set of unique addresses. */
    void insertIntoAddressSet(uint64_t address, set<Address>& addresses)
    {
        addresses.insert(address);
    }
    
    /**
     * Visit the individual CUDA messages packed within a performance data blob.
     */
    void visit(const Blob& blob, const MessageVisitor& visitor)
    {
        CBTF_cuda_data data;
        memset(&data, 0, sizeof(data));

        blob.getXDRDecoding(
            reinterpret_cast<xdrproc_t>(xdr_CBTF_cuda_data), &data
            );
        
        for (u_int i = 0; i < data.messages.messages_len; ++i)
        {
            visitor(data, data.messages.messages_val[i]);
        }
        
        xdr_free(reinterpret_cast<xdrproc_t>(xdr_CBTF_cuda_data),
                 reinterpret_cast<char*>(&data));        
    }
        
} // namespace <anonymous>



/**
 * Collector's factory method.
 *
 * Factory method for instantiating a collector implementation. This is the
 * only function that is externally visible from outside the collector plugin.
 *
 * @return    New instance of this collector's implementation.
 */
extern "C" CollectorImpl* cuda_LTX_CollectorFactory()
{
    return new CUDACollector();
}



/**
 * Default constructor.
 *
 * Constructs a new CUDA collector with the proper metadata.
 */
CUDACollector::CUDACollector() :
    CollectorImpl("cuda", "CUDA",
                  "Intercepts all calls to CUDA memory copy/set and kernel "
                  "executions and records, for each call, the current stack "
                  "trace and start/end time, as well as additional relevant "
                  "information depending on the operation. In addition, has "
                  "the ability to periodically sample hardware event counts "
                  "via PAPI for both the CPU and GPU.")
{
    // Declare our metrics
    declareMetric(Metadata("exec_time",
                           "CUDA Kernel Execution Time",
                           "CUDA kernel execution time in seconds.",
                           typeid(double)));
    declareMetric(Metadata("exec_inclusive_details",
                           "Inclusive CUDA Kernel Execution Details",
                           "Inclusive CUDA kernel execution details.",
                           typeid(ExecDetails)));
    declareMetric(Metadata("exec_exclusive_details",
                           "Exclusive CUDA Kernel Execution Details",
                           "Exclusive CUDA kernel execution details.",
                           typeid(ExecDetails)));

    declareMetric(Metadata("xfer_time",
                           "CUDA Data Transfer Time",
                           "CUDA data transfer time in seconds.",
                           typeid(double)));
    declareMetric(Metadata("xfer_inclusive_details",
                           "Inclusive CUDA Data Transfer Details",
                           "Inclusive CUDA data transfer details.",
                           typeid(XferDetails)));
    declareMetric(Metadata("xfer_exclusive_details",
                           "Exclusive CUDA Data Transfer Details",
                           "Exclusive CUDA data transfer details.",
                           typeid(XferDetails)));

    // TODO: Add additional metrics for hardware counter sampling data...
}



/**
 * Get the default parameter values.
 *
 * Implement getting our default parameter values.
 *
 * @return    Blob containing the default parameter values.
 */
Blob CUDACollector::getDefaultParameterValues() const
{
    // This method's implementation is intentionally empty.
    //
    // The CUDA collector is only available for the CBTF-based data collection
    // model. And that data collection model doesn't use this method.

    return Blob();
}



/**
 * Get a parameter value.
 *
 * Implement getting one of our parameter values.
 *
 * @param parameter    Unique identifier of the parameter.
 * @param data         Blob containing the parameter values.
 * @retval ptr         Untyped pointer to the parameter value.
 */
void CUDACollector::getParameterValue(const string& parameter,
                                      const Blob& data, void* ptr) const
{
    // This method's implementation is intentionally empty.
    //
    // The CUDA collector is only available for the CBTF-based data collection
    // model. And that data collection model doesn't use this method.
}



/**
 * Set a parameter value.
 *
 * Implements setting one of our parameter values.
 *
 * @param parameter    Unique identifier of the parameter.
 * @param ptr          Untyped pointer to the parameter value.
 * @retval data        Blob containing the parameter values.
 */
void CUDACollector::setParameterValue(const string& parameter,
                                      const void* ptr, Blob& data) const
{
    // This method's implementation is intentionally empty.
    //
    // The CUDA collector is only available for the CBTF-based data collection
    // model. And that data collection model doesn't use this method.
}



/**
 * Start data collection.
 *
 * Implement starting data collection for the specified threads.
 *
 * @param collector    Collector starting data collection.
 * @param threads      Threads for which to start collecting data.
 */
void CUDACollector::startCollecting(const Collector& collector,
                                    const ThreadGroup& threads) const
{
    // This method's implementation is intentionally empty.
    //
    // The CUDA collector is only available for the CBTF-based data collection
    // model. And that data collection model doesn't use this method.
}



/**
 * Stops data collection.
 *
 * Implement stopping data collection for the specified threads.
 *
 * @param collector    Collector stopping data collection.
 * @param threads      Threads for which to stop collecting data.
 */
void CUDACollector::stopCollecting(const Collector& collector,
                                   const ThreadGroup& threads) const
{
    // This method's implementation is intentionally empty.
    //
    // The CUDA collector is only available for the CBTF-based data collection
    // model. And that data collection model doesn't use this method.
}



/**
 * Get metric values.
 *
 * Implements getting one of this collector's metric values over all subextents
 * of the specified extent for a particular thread, for one of the collected
 * performance data blobs.
 *
 * @param metric        Unique identifier of the metric.
 * @param collector     Collector for which to get values.
 * @param thread        Thread for which to get values.
 * @param extent        Extent of the performance data blob.
 * @param blob          Blob containing the performance data.
 * @param subextents    Subextents for which to get values.
 * @retval ptr          Untyped pointer to the values of the metric.
 */
void CUDACollector::getMetricValues(const string& metric,
                                    const Collector& collector,
                                    const Thread& thread,
                                    const Extent& extent,
                                    const Blob& blob,
                                    const ExtentGroup& subextents,
                                    void* ptr) const
{
    MessageVisitor visitor;

    if (metric == "exec_time")
    {
        // ...
    }
    else if (metric == "exec_inclusive_details")
    {
        // ...
    }
    else if (metric == "exec_exclusive_details")
    {
        // ...
    }
    else if (metric == "xfer_time")
    {
        // ...
    }
    else if (metric == "xfer_inclusive_details")
    {
        // ...
    }
    else if (metric == "xfer_exclusive_details")
    {
        // ...
    }

    if (visitor)
    {
        visit(blob, visitor);
    }
}



/**
 * Get unique PC values.
 *
 * Implements getting all of the unique program counter (PC) values encountered
 * for a particular thread, for one of the collected performance data blobs.
 *
 * @param thread     Thread for which to get unique PC values.
 * @param blob       Blob containing the performance data.
 * @retval buffer    Buffer of the unique PC values.
 */
void CUDACollector::getUniquePCValues(const Thread& thread,
                                      const Blob& blob,
                                      PCBuffer* buffer) const
{
    AddressVisitor inserter = bind(insertIntoAddressBuffer, _1, ref(*buffer));
    MessageVisitor visitor = bind(extractUniqueAddresses, _1, _2, inserter);
    visit(blob, visitor);
}



/**
 * Get unique PC values.
 *
 * Implements getting all of the unique program counter (PC) values encountered
 * for a particular thread, for one of the collected performance data blobs.
 *
 * @param thread        Thread for which to get unique PC values.
 * @param blob          Blob containing the performance data.
 * @retval addresses    Set of unique PC values.
 */
void CUDACollector::getUniquePCValues(const Thread& thread,
                                      const Blob& blob,
                                      set<Address>& addresses) const
{
    AddressVisitor inserter = bind(insertIntoAddressSet, _1, ref(addresses));
    MessageVisitor visitor = bind(extractUniqueAddresses, _1, _2, inserter);
    visit(blob, visitor);
}