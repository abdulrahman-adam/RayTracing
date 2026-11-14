

#ifndef IMAGE_H
#define IMAGE_H

#include "texturebase.hpp"
#include <string>
#include <cstdint>
#include "SDL2/SDL.h"

namespace qbRT
{
    namespace Texture
    {
        class Image : public TextureBase
        {
            public:
              Image();
              virtual ~Image();

              // Function to return the color 
              virtual qbVector<double> GetColor(const qbVector<double> &uvCoords) override;

              // Function to load the image to be used.
              bool LoadImage(std::string fileName);
            
            private:
              std::string m_fileName;
              SDL_Surface * m_imageSurface;
              SDL_PixelFormat * m_pixelFormat;
              bool m_imageLoaded = false;
              int m_xSize, m_ySize, m_pitch;
              uint8_t m_bytesPerPixel;
              uint32_t m_rMask, m_gMask, m_bMask, m_aMask;
         };
    }
}
#endif // IMAGE_H