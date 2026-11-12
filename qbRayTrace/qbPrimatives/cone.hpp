

#ifndef CONE_H
#define CONE_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace qbRT
{
    class Cone : public ObjectBase
    {
        public:
        // Default construct
        Cone();

        // OVerride the destruct
        virtual ~Cone() override;

        //Override the function to test for intersections.
        virtual bool TestIntersections( const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                             qbVector<double> &localNormal, qbVector<double> &localColor) override;
    };
}

#endif