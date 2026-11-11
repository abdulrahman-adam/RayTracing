#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f

// Default constructor.
qbRT::ObjectBase::ObjectBase()
{
    
}

// The destructor.
qbRT::ObjectBase::~ObjectBase()
{

}

void qbRT::ObjectBase::SetTransformMatrix(const qbRT::GTform &transformMatrix)
{
    m_transformMatrix = transformMatrix;
}



// Funcction to test for intersections
bool qbRT::ObjectBase::TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    // This is a base class function and should be overridden by derived classes.
    // It returns false to indicate that no intersection was found.
    return false;
}

// Fucntion to to assign a material.
bool qbRT::ObjectBase::AssignMaterial(const std::shared_ptr<qbRT::MaterialBase> &objectMaterial)
{
    m_pMaterial = objectMaterial;
    m_hasMaterial = true;
    return m_hasMaterial;
}

//Function to test whether two floating-point numbers are close enough to being equal.
bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2)
{
    // This function checks if two floating-point numbers are close enough to be considered equal.
    // It uses a small epsilon value to determine the closeness.
    return fabs(f1 - f2) < EPSILON;
}
