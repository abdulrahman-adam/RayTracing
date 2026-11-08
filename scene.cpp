// scene.cpp


/**
The scene class implementation . A class to handle information about the scene and rendering to an image.
 */


#include "scene.hpp"
#include <iostream>

// The constructor
qbRT::Scene::Scene()

{
    //Configure the camera
    m_camera.SetPosition( qbVector<double>{std::vector<double>{0.0, -10.0, -1.0}} );
    m_camera.SetLookAt  ( qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}} );
    m_camera.SetUp      ( qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}} );
    m_camera.SetHorzSize(0.25);
    m_camera.SetAspect  (16.0 / 9.0);
    m_camera.UpdateCameraGeometry();

    //Construct a test sphere.
    m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
    m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
    m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));

    // Construct a test plane
    m_objectList.push_back(std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane()));
    m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double> {128.0, 128.0, 128.0}};

    // Define a transform for the plane
    qbRT::GTform planeMatrix;
    planeMatrix.SetTransform( qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
                              qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                              qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});
    m_objectList.at(3) -> SetTransformMatrix(planeMatrix);
    
    // Modify the Sphere
    qbRT::GTform testMatrix1, testMatrix2, testMatrix3;
    testMatrix1.SetTransform( qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
                              qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                              qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});

    testMatrix2.SetTransform( qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                              qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                              qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});

    testMatrix3.SetTransform( qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
                              qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                              qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});

    m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
    m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
    m_objectList.at(2) -> SetTransformMatrix(testMatrix3);

    // Modify the color
    m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{64.0, 128.0, 200.0}};
    m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{255.0, 128.0, 0.0}};
    m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{255.0, 200.0, 0.0}};




    // Construct a test light.
    m_lightList.push_back(std::make_shared<qbRT::PointLight>(qbRT::PointLight()));
    m_lightList.at(0) -> m_location = qbVector<double>{std::vector<double>{5.0, -10.0, -5.0}};
    m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double>{255.0, 255.0, 255.0}};
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
    for (int x=0; x<xSize; ++x)
    {
        for (int y=0; y<ySize; ++y)
        {
            //Normalize x and y coordinate
            double normX = (static_cast<double>(x) * xFact) - 1.0;
            double normY = (static_cast<double>(y) * yFact) - 1.0;

            // Generate the for this pixel.
            m_camera.GenerateRay(normX, normY, cameraRay);



            // Test for intersections with all objects in the scene.
            std::shared_ptr<qbRT::ObjectBase> closestObject;
            qbVector<double> closestIntPoint    {3};
            qbVector<double> closestLocalNormal {3};
            qbVector<double> closestLocalColor {3};
            double minDist = 1e6;
            bool intersectionFound = false;


            for (auto currentObject : m_objectList)
            {
                bool validInt = currentObject -> TestIntersections(cameraRay, intPoint, localNormal, localColor);
                 // If we have a valid intersection.
                if(validInt)
                {
                    // Set the flag to indicate that we found an intersection
                    intersectionFound = true;

                    // Compute the distance between the camera and the point of intersection
                    double dist = (intPoint - cameraRay.m_point1).norm();

                    // If this object is closer to the camera than any one that we have seen before store rference to it.
                    if (dist < minDist)
                    {
                        minDist = dist;
                        closestObject = currentObject;
                        closestIntPoint = intPoint;
                        closestLocalNormal = localNormal;
                        closestLocalColor = localColor;
                    } 
                }
            } 
            
             // Compute the illumination for the closest object assuming that there was a valid intersection
        if (intersectionFound)
        {
            // Compute the intensity of illumination
            double intensity;
            qbVector<double> color {3};
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            bool validIllum = false;
            bool illumFound = false;
            for (auto currentLight : m_lightList)
            {
                validIllum = currentLight -> ComputeIllumination(closestIntPoint, closestLocalNormal, m_objectList, closestObject, color, intensity);
                if (validIllum)
                {
                    illumFound = true;
                    red += color.GetElement(0) * intensity;
                    green += color.GetElement(1) * intensity;
                    blue += color.GetElement(2) * intensity;
                }
            }

            if (illumFound)
            {
                red *= closestLocalColor.GetElement(0);
                green *= closestLocalColor.GetElement(1);
                blue *= closestLocalColor.GetElement(2);
                outputImage.SetPixel(x, y, red, green, blue);
            }
        } 
    }
}
    return true;
}