#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "turtle.h"

int main( int argc, char** argv )
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
