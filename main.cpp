#include "CApp.h"

int main(int argc, char *argv[])
{
    CApp theApp;

    return theApp.OnExecute();
}



// LANCER LE PROJET 
// $env:PATH = "C:\msys64\ucrt64\bin;$env:PATH"
// g++ main.cpp CApp.cpp qbImage.cpp -o raytracer.exe -IC:\msys64\ucrt64\include -LC:\msys64\ucrt64\lib -lmingw32 -lSDL2main -lSDL2
// .\raytracer.exe