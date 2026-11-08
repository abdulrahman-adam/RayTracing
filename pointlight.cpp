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
        // Check whether another object blocks the light (shadow).
        double lightDist = (m_location - intPoint).norm();
        qbRT::Ray lightRay (startPoint, startPoint + lightDir);

        qbVector<double> poi       {3};
        qbVector<double> poiNormal {3};
        qbVector<double> poiColor  {3};
        bool validInt = false;
        for (auto sceneObject : objectList)
        {
            if (sceneObject != currentObject)
            {
                validInt = sceneObject -> TestIntersections(lightRay, poi, poiNormal, poiColor);

                // An object behind the light does not cast a shadow.
                if (validInt)
                {
                    double dist = (poi - startPoint).norm();
                    if (dist > lightDist)
                        validInt = false;
                }
            }

            if (validInt)
                break;
        }

        if (validInt)
        {
            // The point is in shadow.
            color = m_color;
            intensity = 0.0;
            return false;
        }

        //We do have illumination
        color = m_color;
        intensity = m_intensity * (1.0 - (angle / 1.5708));
        return true;
    }
}