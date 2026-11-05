#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "qbImage.hpp"

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
    };
}

#endif