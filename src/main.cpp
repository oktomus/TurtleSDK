#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "turtle.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/postprocess.h>

int main()
{

    Turtle & a = Turtle::getInstance();

    try
    {
        a.init();
    }
    catch(const std::exception &e)
    {
        fprintf(stderr, "\nInitialisation failed. Reason:\n%s\n", e.what());
        a.terminate();
        exit(2);
    }

    a.mainLoop();
    a.terminate();

    return 0;

}
