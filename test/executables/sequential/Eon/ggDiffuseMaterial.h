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



#ifndef GGDIFFUSEMATERIAL_H
#define GGDIFFUSEMATERIAL_H


#include <ggMaterial.h>

class ggDiffuseMaterial : public ggMaterial {
public:

  virtual ggBoolean print(ostream&) const;
        
  virtual ggBoolean getInfo(const ggRay3& rayIn,
                            const ggPoint3& p,
                            const ggONB3& uvw,
                            const double& cover,
                            ggMaterialRecord& material) const;

  ggDiffuseMaterial(const ggSpectrum&, ggBoolean hasBrdf);

protected:
// R: absolute reflectance
   ggSpectrum R;
   ggDiffuseMaterial() {}
};

#endif

