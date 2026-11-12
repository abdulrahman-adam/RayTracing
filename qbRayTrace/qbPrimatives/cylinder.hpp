

#ifndef CYLINDER_H
#define CYLINDER_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace qbRT
{
    class Cylinder : public ObjectBase
    {
        public:
        // Default Construct
        Cylinder();

        //Override the destruct
        virtual ~Cylinder() override;

        // Override the function to test for intersections.
        virtual bool TestIntersections( const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                       qbVector<double> &localNormal, qbVector<double> &localColor) override;

    };
}
#endif