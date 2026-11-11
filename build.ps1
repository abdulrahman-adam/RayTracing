# build.ps1 - Compile and run the ray tracer.
# Usage (in the VS Code terminal):  .\build.ps1

# Make g++ available in this terminal.
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH

g++ *.cpp qbRayTrace/*.cpp qbRayTrace/qbLights/*.cpp qbRayTrace/qbPrimatives/*.cpp qbRayTrace/qbMaterials/*.cpp `
    -o raytracer.exe -std=c++17 `
    -IC:/msys64/ucrt64/include/SDL2 -Dmain=SDL_main `
    -LC:/msys64/ucrt64/lib -lmingw32 -lSDL2main -lSDL2

if ($LASTEXITCODE -eq 0) {
    .\raytracer.exe
}
