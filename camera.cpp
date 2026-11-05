// camera.cpp

#include "camera.hpp"
#include "ray.hpp"
#include "math.h"

qbRT::Camera::Camera()
{
    // The default constructor initializes the camera parameters to default values.

    m_cameraPosition = qbVector<double>{std::vector<double>{0.0, -10, 0.0}};
    m_cameraLookAt = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
    m_cameraUp = qbVector<double>{std::vector<double>{0.0, 0.0, 1.8}};
    m_cameraLength = 1.0;
    m_cameraHorzSize = 1.0;
    m_cameraAspectRatio = 1.0;
}

void qbRT::Camera::SetPosition(const qbVector<double> &newPosition)
{
    m_cameraPosition = newPosition;
}

void qbRT::Camera::SetLookAt(const qbVector<double> &newLookAt)
{
    m_cameraLookAt = newLookAt;
}

void qbRT::Camera::SetUp(const qbVector<double> &upVector)
{
    m_cameraUp = upVector;
}

void qbRT::Camera::SetLength(double newLength)
{
    m_cameraLength = newLength;
}

void qbRT::Camera::SetHorzSize(double newSize)
{
    m_cameraHorzSize = newSize;
}

void qbRT::Camera::SetAspect(double newAspect)
{
    m_cameraAspectRatio = newAspect;
}

//Method to return the camera position
qbVector<double> qbRT::Camera::GetPosition()
{
    return m_cameraPosition;
}

// Method to return the camera look at point
qbVector<double> qbRT::Camera::GetLookAt()
{
    return m_cameraLookAt;
}

// Method to return the camera up vector of the camera
qbVector<double> qbRT::Camera::GetUp()
{
    return m_cameraUp;
}

// Method to return the length of the camera
double qbRT::Camera::GetLength()
{
    return m_cameraLength;
}


// Method to return the horizontal size of the camera
double qbRT::Camera::GetHorzSize()
{
    return m_cameraHorzSize;
}

// Method to return the aspect ratio of the camera
double qbRT::Camera::GetAspect()
{
    return m_cameraAspectRatio;
}

// Method to return the U vector of the camera
qbVector<double> qbRT::Camera::GetU()
{
    return m_projectionScreenU;
}

// Method to return the V vector of the camera
qbVector<double> qbRT::Camera::GetV()
{
    return m_projectionScreenV;
}

// Method to return the screen center of the camera
qbVector<double> qbRT::Camera::GetScreenCenter()
{
    return m_projectionScreenCenter;
}

// Function to compute the camera geometry based on the current parameters.
void qbRT::Camera::UpdateCameraGeometry()
{
    // First, compute the vector from the camera position to the look-at position
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector.Normalize();

    //Second Compute the U and V vectors for the projection screen
    m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU.Normalize();
    m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_projectionScreenV.Normalize();

    // Thirdly, compute the position of the center point of the screen
    m_projectionScreenCenter = m_cameraPosition + (m_cameraLength * m_alignmentVector);

    // Modify the U and V vectors to match the size and aspect ratio
    m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
    m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);

    
}

// Function return array from the center of camera
qbRT::Ray qbRT::Camera::GenerateRay(float proScreenX, float proScreenY)
{
    // Compute the location of the screen point in world coordinates.
    qbVector<double> screenWorldPart1 = m_projectionScreenCenter + (m_projectionScreenU * proScreenX);
    qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);
    
    // Use this point along with the camera position to compute the ray.
    return qbRT::Ray(m_cameraPosition, screenWorldCoordinate); 

}