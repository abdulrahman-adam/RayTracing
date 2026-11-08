// objectbas.hpp
#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"
#include "gtfm.hpp"

namespace qbRT
{
    class ObjectBase
    {
    public:
        // Constructor and destructor
        ObjectBase();
        virtual ~ObjectBase();

        // Function to test for intersections
        virtual bool TestIntersections(const Ray &castRay, qbVector<double> & intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

        // Function to set the transform matrix.
        void SetTransformMatrix(const qbRT::GTform &transformMatrix);

        // Function to test whether two floating-point numbers are close being equal.
        bool CloseEnough(const double f1, const double f2);

        // Public member variables
    public:
        // the base Color of the object
        qbVector<double> m_baseColor {3};
        //The geometrix transform applied to the object.
        qbRT::GTform m_transformMatrix;
    };
}

#endif // OBJECTBASE_H

