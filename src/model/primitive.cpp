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

Quad::Quad(
        float xa, float ya, float za,
        float xb, float yb, float zb,
        float xc, float yc, float zc,
        float xd, float yd, float zd) : Base(GL_QUADS, 4)
{
    data = {
        xa, ya, za,
        xb, yb, zb,
        xc, yc, zc,
        xd, yd, zd
    };

    indices = {
        0, 1 ,3,
        1, 2, 3
    };

    prepare();
}

Cube::Cube(float x, float y, float z, float size) :
    Base(GL_QUADS, 24)
{
    data = {
        // Front
        x - size, y - size, z + size,
        x + size, y - size, z + size,
        x + size, y + size, z + size,
        x - size, y + size, z + size,

        // Back
        x + size, y - size, z - size,
        x - size, y - size, z - size,
        x - size, y + size, z - size,
        x + size, y + size, z - size,

        // Right
        x + size, y - size, z + size,
        x + size, y - size, z - size,
        x + size, y + size, z - size,
        x + size, y + size, z + size,

        x - size, y - size, z - size,
        x - size, y - size, z + size,
        x - size, y + size, z + size,
        x - size, y + size, z - size,

        x - size, y + size, z - size,
        x - size, y + size, z + size,
        x + size, y + size, z + size,
        x + size, y + size, z - size,

        x - size, y - size, z + size,
        x - size, y - size, z - size,
        x + size, y - size, z - size,
        x + size, y - size, z + size
    };

    prepare();


}
