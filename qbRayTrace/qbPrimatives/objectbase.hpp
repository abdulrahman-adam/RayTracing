// objectbas.hpp
#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../../qbLinAlg/qbVector.h"
#include "../ray.hpp"
#include "../gtfm.hpp"

namespace qbRT
{
    // Forward declare the material base class. This will be overriden later.
    class MaterialBase;

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

        // Function to assign a material.
        bool AssignMaterial(const std::shared_ptr<qbRT::MaterialBase> &objectMaterial);



        // Public member variables
    public:
        // the base Color of the object
        qbVector<double> m_baseColor {3};
        //The geometrix transform applied to the object.
        qbRT::GTform m_transformMatrix;

        // Areference to the material assigned to this object.
        std::shared_ptr<qbRT::MaterialBase> m_pMaterial;

        // A flag to indicate wether this object has amaterial or not.
        bool m_hasMaterial = false;
    };
}

#endif // OBJECTBASE_H

