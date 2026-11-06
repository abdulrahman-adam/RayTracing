//pointlight.ccp
#include "pointlight.hpp"
#include <cmath>

// Default constructor
qbRT::PointLight::PointLight()
{
    m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
    m_intensity = 1.0;
}

// Destructor
qbRT::PointLight::~PointLight()
{

}

// Function to compute illumination
bool qbRT::PointLight::ComputeIllumination( const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                            const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                            const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                            qbVector<double> &color, double &intensity)
{
    //Construct a vector pointing from the intersection point to the light.
    qbVector<double> lightDir = (m_location - intPoint).Normalized();
    // compute a starting point
    qbVector<double> startPoint = intPoint;

    // compute the anglebetween the local normal and the light ray.
    // Note that we asume that localNormal is a until vector.

    double angle = acos(qbVector<double>::dot(localNormal, lightDir));

    //If the normal is pointing away from the light, then we have no illumination.
    if (angle > 1.5708)
    {
        // No illumination
        color = m_color;
        intensity = 0.0;
        return false;
    }
    else
    {
        //We do have illumination
        color = m_color;
        intensity = m_intensity * (1.0 - (angle / 1.5708));
        return true;
    }
}