#ifndef QBIMAGE_H
#define QBIMAGE_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class qbImage
{
    public:
        // the constructor.
        qbImage();

        // the destructor.
        ~qbImage();

        // Function to initialise.
        void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);

        // Function to set color of the pixels.
        void SetPixel(const int x, const int y, const double red, const double green, const double blue);

        // Function to return the image of display
        void Display();

        // Function to return the dimentions of the image
        int GetXSize();
        int GetYSize();

    private:
        // Function return the view of colors
        Uint32 ConvertColor(const double red, const double green, const double blue);
        void InitTexture();

    private:
        // Arrays to store image data.
        std::vector<std::vector<double>> m_rChannel;
        std::vector<std::vector<double>> m_gChannel;
        std::vector<std::vector<double>> m_bChannel;

        // Store the dimensions of the image.
        int m_xSize, m_ySize;

        // SDL stuff
        SDL_Renderer *m_pRenderer;
        SDL_Texture *m_pTexture;
};

#endif // QBIMAGE_H
