#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "objectbase.hpp"
#include "gtfm.hpp"

namespace qbRT
{
    class ObjPlane: public ObjectBase
    {
        public:
            // Default constructor
            ObjPlane();

            // Override the destructor.
            virtual ~ObjPlane() override;

            // Override the function to test for intersection
            virtual bool TestIntersections( const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                        qbVector<double> &localNormal, qbVector<double> &localColor) override;
            
        private:
        
    };
}
#endif