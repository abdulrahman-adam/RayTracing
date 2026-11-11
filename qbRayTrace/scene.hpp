// scene.hpp

/*
The scene class definition . A class to handle information about the scene and rendering
to an image.

*/




#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "qbImage.hpp"
#include "camera.hpp"
#include "./qbPrimatives/objsphere.hpp"
#include "./qbPrimatives/objplane.hpp"
#include "./qbLights/pointlight.hpp"
#include "./qbMaterials/materialbase.hpp"

namespace qbRT

{
    class Scene
    {
        public:
        // The default constructor
        Scene();
        // Function to perform the rendering.
        bool Render(qbImage &outputImage);

        // Function to cast a ray into the scene.
        bool CastRay( qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
                      qbVector<double> &closestPoint, qbVector<double> &colsestLocalNormal,
                      qbVector<double> &closestLocalColor);
        // Private functions
        private:

        // private members
        private:
            //The camera that we will use.
            qbRT::Camera m_camera;
            //The list of the objects in the scene
            std::vector<std::shared_ptr<qbRT::ObjectBase>> m_objectList;

            // The list of the lights in the scene
            std::vector<std::shared_ptr<qbRT::LightBase>> m_lightList;
    };
}

#endif