#include "primitive.h"

/*
                 ▀             ▀      ▄      ▀                 
 ▄▄▄▄    ▄ ▄▄  ▄▄▄    ▄▄▄▄▄  ▄▄▄    ▄▄█▄▄  ▄▄▄    ▄   ▄   ▄▄▄  
 █▀ ▀█   █▀  ▀   █    █ █ █    █      █      █    ▀▄ ▄▀  █▀  █ 
 █   █   █       █    █ █ █    █      █      █     █▄█   █▀▀▀▀ 
 ██▄█▀   █     ▄▄█▄▄  █ █ █  ▄▄█▄▄    ▀▄▄  ▄▄█▄▄    █    ▀█▄▄▀ 
 █                                                             
 */

using namespace model;

Triangle::Triangle(
        float xa, float ya, float za,
        float xb, float yb, float zb,
        float xc, float yc, float zc) : Base(GL_TRIANGLES, 3)
{
    data = {
        xa, ya, za,
        xb, yb, zb,
        xc, yc, zc
    };

    prepare();
}

