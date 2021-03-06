//////////////////////////////// -*- C++ -*- //////////////////////////////
//
// AUTHOR
//    Peter Shirley, Cornell University, shirley@graphics.cornell.edu 
//
// COPYRIGHT
//    Copyright (c) 1995  Peter Shirley. All rights reserved.
//
//    Permission to use, copy, modify, and distribute this software for any
//    purpose without fee is hereby granted, provided that this entire
//    notice is included in all copies of any software which is or includes
//    a copy or modification of this software and in all copies of the
//    a copy or modification of this software and in all copies of the
//    supporting documentation for such software.
//
// DISCLAIMER
//    Neither the Peter Shirley nor Cornell nor any of their
//    employees, makes any warranty, express or implied, or assumes any
//    liability or responsibility for the accuracy, completeness, or
//    usefulness of any information, apparatus, product, or process
//    disclosed, or represents that its use would not infringe
//    privately-owned rights.  
//
///////////////////////////////////////////////////////////////////////////



#ifndef MRGRID_H
#define MRGRID_H


#include <mrSurfaceList.h>
#include <ggGrid.h>


class mrGrid : public mrSurface {
public:
  virtual ggBoolean print(ostream& s) const;

  virtual ggBoolean shadowHit(        
             const ggRay3& r,    // ray being sent
             double time,     // time ray is sent
             double tmin, // minimum hit parameter to be searched for
             double tmax, // maximum hit parameter to be searched for
             double& t,
             ggVector3& N,  
             ggBoolean& emits,
             ggSpectrum& kEmit
             ) const;

  virtual ggBoolean viewingHit(        
             const ggRay3& r,    // ray being sent
             double time,     // time ray is sent
             double tmin, // minimum hit parameter to be searched for
             double tmax, // maximum hit parameter to be searched for
             mrViewingHitRecord&,
             ggMaterialRecord& rec
             ) const;

  //  returns true if bounding box is found
  virtual ggBoolean boundingBox(
             double time1, // low end of time range
             double time2, // low end of time range
             ggBox3& bbox)
             const;

   virtual ggBoolean selectVisiblePoint(
             const ggPoint3& x,   // viewpoint
             const ggVector3& Nx, // unit vector at x
             const ggPoint2& uv,   // input coordinate
             const double time,// time of query
             ggPoint3& on_light,  // point corresponding to uv
             double& prob)     // probability of selecting on_light
             const;


   mrGrid(double time1, double time2,
          mrSurfaceList *lPtr,
          ggPoint3 min, // minimum point of bounding box
        ggPoint3 max, // maximum point of bounding box
         double multiplier,   // how many grid cells per object in each dimension
         int perCell,   // maximum number of objects per cell
         int maxDepth ); // number of nests possible



  protected:
      ggGrid<mrSurface *> grid;
      mrSurfaceList *list;
      ggBox3 bbox;
      double multiplier;
      int rayCounter;
      void insert(double time1, double time2, mrSurface *obj_ptr);
      int surfaceCounter;
};


#endif
