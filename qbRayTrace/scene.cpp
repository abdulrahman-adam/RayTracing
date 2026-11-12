// scene.cpp


/**
The scene class implementation . A class to handle information about the scene and rendering to an image.
 */


#define _USE_MATH_DEFINES   // makes M_PI available (must come before any include)
#include <cmath>
#include "scene.hpp"
#include "./qbMaterials/simplematerial.hpp"
#include <iostream>

// The constructor
qbRT::Scene::Scene()

{
    // Create some materials
    auto yellowDiffuse = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
    auto blueDiffuse = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
    auto floorMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());



    // Blue diffuse material
    blueDiffuse -> m_baseColor = qbVector<double>{std::vector<double>{0.2, 0.2, 0.8}};
    blueDiffuse -> m_reflectivity = 0.05;
    blueDiffuse -> m_shininess = 5.0;

    // Yellow diffuse material
    yellowDiffuse -> m_baseColor = qbVector<double>{std::vector<double>{0.8, 0.8, 0.3}};
    yellowDiffuse -> m_reflectivity = 0.05;
    yellowDiffuse -> m_shininess = 5.0;

    // Floor material
    floorMaterial -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
    floorMaterial -> m_reflectivity = 0.5;
    floorMaterial -> m_shininess = 0.0;

    // Maximum number of reflection rays (0 would disable reflections).
    qbRT::MaterialBase::m_maxReflectionRays = 3;

    //Configure the camera
    // m_camera.SetPosition( qbVector<double>{std::vector<double>{0.0, -10.0, -1.0}});
    m_camera.SetPosition( qbVector<double>{std::vector<double>{3.0, -5.0, -2.0}});
    m_camera.SetLookAt  ( qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}} );
    m_camera.SetUp      ( qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}} );
    m_camera.SetHorzSize(0.75);
    m_camera.SetAspect  (16.0 / 9.0);
    m_camera.UpdateCameraGeometry();

    // Create and setup some onjects.
    auto floor = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
    floor -> SetTransformMatrix(qbRT::GTform { qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
                                               qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                               qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
    floor -> AssignMaterial (floorMaterial);

    // Cylinder
    auto cylinder1 = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
    cylinder1 -> SetTransformMatrix(qbRT::GTform { qbVector<double>{std::vector<double>{-1.0, 0.0, 0.0}},
                                                   qbVector<double>{std::vector<double>{-M_PI / 4.0, 0.0, 0.0}},
                                                   qbVector<double>{std::vector<double>{0.5, 0.5, 1.0}}});
    cylinder1 -> AssignMaterial (blueDiffuse);

    // Cone
    auto cone1 = std::make_shared<qbRT::Cone> (qbRT::Cone());
    cone1 -> SetTransformMatrix(qbRT::GTform { qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}},
                                               qbVector<double>{std::vector<double>{M_PI/ 4.0, 0.0, 0.0}},
                                               qbVector<double>{std::vector<double>{0.5, 0.5, 1.0}}});
    cone1 -> AssignMaterial (yellowDiffuse);


    // Put this object into the scene
    m_objectList.push_back(floor);
    m_objectList.push_back(cylinder1);
    m_objectList.push_back(cone1);
   
    
    // Construct a test light.
    m_lightList.push_back(std::make_shared<qbRT::PointLight>(qbRT::PointLight()));
    m_lightList.at(0) -> m_location = qbVector<double>{std::vector<double>{5.0, -10.0, -5.0}};
    m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double>{0.0, 0.0, 1.0}};

    m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
    m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {-5.0, -10.0, -5.0}};
    m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 0.0, 0.0}};

    m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
    m_lightList.at(2) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
    m_lightList.at(2) -> m_color = qbVector<double> {std::vector<double> {0.0, 1.0, 0.0}};



}

// FUnction to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage)
{
    // Get the dimentions of the output image
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();
    //Loop over each pixel in the output image
    qbRT::Ray cameraRay;
    qbVector<double> intPoint{3};
    qbVector<double> localNormal{3};
    qbVector<double> localColor{3};
    double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
    double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;
    for (int y=0; y<ySize; ++y)
    {
        // DIsplat progress.
        std::cout << "Processing line " << y << " of " << ySize << "-" << std::endl;

        for (int x=0; x<xSize; ++x)
        {
            //Normalize x and y coordinate
            double normX = (static_cast<double>(x) * xFact) - 1.0;
            double normY = (static_cast<double>(y) * yFact) - 1.0;

            // Generate the for this pixel.
            m_camera.GenerateRay(normX, normY, cameraRay);



            // Test for intersections with all objects in the scene.
            std::shared_ptr<qbRT::ObjectBase> closestObject;
            qbVector<double> closestInPoint     {3};
            qbVector<double> closestLocalNormal {3};
            qbVector<double> closestLocalColor  {3};
            bool intersectionFound = CastRay(cameraRay, closestObject, closestInPoint, closestLocalNormal, closestLocalColor);

            
             // Compute the illumination for the closest object assuming that there was a valid intersection
            if (intersectionFound)
            {
                // Check if the object has a material
                if (closestObject -> m_hasMaterial)
                {
                    // Reset the reflection ray counter for this pixel.
                    qbRT::MaterialBase::m_reflectionRayCount = 0;

                    // Use the material to compute the color.
                    qbRT::MaterialBase::m_reflectionRayCount = 0;
                    qbVector<double> color = closestObject -> m_pMaterial -> ComputeColor( m_objectList, m_lightList,
                                                                                        closestObject, closestInPoint,
                                                                                        closestLocalNormal, cameraRay);
                    
                    outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
                }
                else
                {
                    // Use the basic method to compute the color.
                    qbVector<double> matColor = qbRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList,
                                                                                        closestObject, closestInPoint,
                                                                                        closestLocalNormal, closestObject -> m_baseColor);
                    outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
                }
            }      
        }
    }
    return true;
}

// Function to cast a ray into the scene
bool qbRT::Scene::CastRay( qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
                            qbVector<double> &closestPoint, qbVector<double> &closestLocalNormal,
                            qbVector<double> &closestLocalColor)

{
    qbVector<double> intPoint    {3};
    qbVector<double> localNormal {3};
    qbVector<double> localColor  {3};
    double minDist = 1e6;
    bool intersectionFound = false;


    for (auto currentObject : m_objectList)
    {
        bool validInt = currentObject -> TestIntersections(castRay, intPoint, localNormal, localColor);
            // If we have a valid intersection.
        if(validInt)
        {
            // Set the flag to indicate that we found an intersection
            intersectionFound = true;

            // Compute the distance between the camera and the point of intersection
            double dist = (intPoint - castRay.m_point1).norm();

            // If this object is closer to the camera than any one that we have seen before store rference to it.
            if (dist < minDist)
            {
                minDist = dist;
                closestObject = currentObject;
                closestPoint = intPoint;
                closestLocalNormal = localNormal;
                closestLocalColor = localColor;
            } 
        }
    } 

    return intersectionFound;
}