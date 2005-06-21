////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
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

/** @file
 *
 * Definition of the Queries namespace.
 *
 */

#include "Queries.hxx"
#include "ToolAPI.hxx"

using namespace OpenSpeedShop::Framework;



/**
 * Get metric values by function in a thread.
 *
 * Gets the current list of functions in the specified thread and evalutes the
 * specified metric, in the specified collector, over the entire time interval.
 * The results are returned in a map of functions to metric values. Only those
 * functions with non-zero metric values will be present in the returned map.
 *
 * @param collector    Collector for which to get a metric.
 * @param metric       Unique identifier of the metric.
 * @param thread       Thread for which to get metric values.
 * @retval result      Smart pointer to a map of the thread's functions to
 *                     their metric values.
 */
void Queries::GetMetricByFunctionInThread(
    const Collector& collector, const std::string& metric,
    const Thread& thread,
    SmartPtr<std::map<Function, double> >& result)
{
    // Time interval covering earliest to latest possible time
    const TimeInterval Forever = 
	TimeInterval(Time::TheBeginning(), Time::TheEnd());

    // Allocate a new map of functions to doubles
    result = SmartPtr<std::map<Function, double> >(
	new std::map<Function, double>()
	);
    Assert(!result.isNull());
    
    // Get the current list of functions in this thread
    std::set<Function> functions = thread.getFunctions();
    
    // Iterate over each function
    for(std::set<Function>::const_iterator
	    i = functions.begin(); i != functions.end(); ++i) {
	
	// Get the address range of this function
	AddressRange range = i->getAddressRange();
	
	// Evalute the metric over this address range
	double value = 0.0;
	collector.getMetricValue(metric, thread, range, Forever, value);
	
	// Add this function and its metric value to the map
	if(value != 0.0)
	    result->insert(std::make_pair(*i, value));
	
    }    
}



/**
 * Get metric values by statement in a function.
 *
 * Gets the current list of statements in the specified function and evalutes
 * the specified metric, in the specified collector, over the entire time
 * interval. The results are returned in a map of statements to metric values.
 * Only those statements with non-zero metric values will be present in the
 * returned map.
 *
 * @param collector    Collector for which to get a metric.
 * @param metric       Unique identifier of the metric.
 * @param function     Function for which to get metric values.
 * @retval result      Smart pointer to a map of the function's statements to
 *                     their metric values.
 */
void Queries::GetMetricByStatementInFunction(
    const Collector& collector, const std::string& metric,
    const Function& function,
    SmartPtr<std::map<Statement, double> >& result)
{
    // Time interval covering earliest to latest possible time
    const TimeInterval Forever = 
	TimeInterval(Time::TheBeginning(), Time::TheEnd());
    
    // Allocate a new map of statements to doubles
    result = SmartPtr<std::map<Statement, double> >(
	new std::map<Statement, double>()
	);
    Assert(!result.isNull());

    // Get the thread containing this function
    Thread thread = function.getThread();

    // Get the list of statements in this function
    std::set<Statement> statements = function.getStatements();
    
    // Iterate over each statement
    for(std::set<Statement>::const_iterator
	    i = statements.begin(); i != statements.end(); ++i) {
	
	// Get the address ranges of this statement
	std::set<AddressRange> ranges = i->getAddressRanges();
	
	// Iterate over each address range
	double value = 0.0;
	for(std::set<AddressRange>::const_iterator
		j = ranges.begin(); j != ranges.end(); ++j ) {
	    
	    // Evalute the metric over this address range
	    double tmp = 0.0;
	    collector.getMetricValue(metric, thread, *j, Forever, value);
	    value += tmp;
	    
	}
	
	// Add this function and its metric value to the map
	if(value != 0.0)
	    result->insert(std::make_pair(*i, value));
	
    }
}


/**
 * Get metric values by statement in a file.
 *
 * Gets the current list of statements in the specified file and evalutes
 * the specified metric, in the specified collector, over the entire time
 * interval. The results are returned in a map of statements to metric values.
 * Only those statements with non-zero metric values will be present in the
 * returned map.
 *
 * @param collector    Collector for which to get a metric.
 * @param metric       Unique identifier of the metric.
 * @param file         File for which to get metric values.
 * @param Thread       Thread for which to query.
 * @retval result      Smart pointer to a map of the file's statements to
 *                     their metric values.
 */
void Queries::GetMetricByStatementInFileForThread(
    const Collector& collector,
    const std::string& metric,
    const std::string& path,
    const Thread& thread,
    SmartPtr<std::map<int, double> >& result)
{
    // Time interval covering earliest to latest possible time
    const TimeInterval Forever = 
	  TimeInterval(Time::TheBeginning(), Time::TheEnd());
    
    // Allocate a new map of statements to doubles
    result = SmartPtr<std::map<int, double> >(
	  new std::map<int, double>()
	);
    Assert(!result.isNull());


    // Get the list of statements in this file
    std::set<Statement> statements = thread.getStatementsBySourceFile(path);
    
    // Iterate over each statement
	double value = 0.0;
    for(std::set<Statement>::const_iterator
	    i = statements.begin(); i != statements.end(); ++i)
    {
	  value = 0.0;
      Statement s = *i;
      int statement_line = (int)s.getLine();
	
	  // Get the address ranges of this statement
	  std::set<AddressRange> ranges = i->getAddressRanges();
	
	  // Iterate over each address range
	  for(std::set<AddressRange>::const_iterator
		  j = ranges.begin(); j != ranges.end(); ++j )
      {
	    // Evalute the metric over this address range
	    double tmp = 0.0;
	    collector.getMetricValue(metric, thread, *j, Forever, tmp);
	    value += tmp;
	  }
	
	  // Add this statement and its metric value to the map
	  if(value != 0.0)
      {
	    result->insert(std::make_pair(statement_line, value));
      }
	
    }
}

