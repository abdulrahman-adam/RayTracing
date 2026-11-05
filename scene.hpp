#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "qbImage.hpp"
#include "camera.hpp"
#include "objsphere.hpp"

namespace qbRT

{
    class Scene
    {
        public:
        // The default constructor
        Scene();
        // Function to perform the rendering.
        bool Render(qbImage &outputImage);
        // Private functions
        private:

        // private members
        private:
            //The camera that we will use.
            qbRT::Camera m_camera;
            // A unit sphere on the origin for testing
            qbRT::ObjSphere m_testSphere;
    };
}

#endif