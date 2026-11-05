// scene.cpp
#include "scene.hpp"

// The constructor
qbRT::Scene::Scene()

{

}

// FUnction to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage)
{
    // Get the dimentions of the output image
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    // Create some colour variations.
    for(int x=0; x<xSize; ++x)
    {
        for(int y=0; y<ySize; ++y)
        {
            double red = (static_cast<double>(x)/static_cast<double>(xSize)) * 255.0;
            double green = (static_cast<double>(y)/static_cast<double>(ySize)) * 255.0;
            outputImage.SetPixel(x,y, red, green, 0.0);
        }
    }

    return true;
}