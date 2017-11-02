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

EBOTriangle::EBOTriangle(
        float xa, float ya, float za,
        float xb, float yb, float zb,
        float xc, float yc, float zc) : Base(GL_TRIANGLES, 3)
{
    data = {
        xa, ya, za,
        xb, yb, zb,
        xc, yc, zc
    };

    indices = {
        0, 1, 2
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
        // front
        // 0 bottom left
        x - size, y - size, z + size,
        // 1 bottom right
        x + size, y - size, z + size,
        // 2 top right
        x + size, y + size, z + size,
        // 3 bottom left
        x - size, y + size, z + size,
        // Back
        // 4 Bottom right
        x + size, y - size, z - size,
        // 5 Bottom left
        x - size, y - size, z - size,
        // 6 Top left
        x - size, y + size, z - size,
        // 7 Top right
        x + size, y + size, z - size,
    };
    indices = {
        0, 1 ,3,
        1, 2, 3,

        4, 5 ,7,
        5, 6, 7,

        0, 3, 6,
        6, 5, 3,

        7, 4, 2,
        2, 1, 2,

        0, 1, 5,
        5, 4, 3,

        0, 2, 6,
        6, 7, 2,
    };

    prepare();


}
