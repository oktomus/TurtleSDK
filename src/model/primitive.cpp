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
        float xd, float yd, float zd) : Base(GL_TRIANGLES, 4)
{
    // A bottom left
    // B bottom right
    // C top right
    // D top left
    data = {
        xa, ya, za,
        xb, yb, zb,
        xc, yc, zc,
        xd, yd, zd
    };

    indices = {
        0, 1 ,2,
        2, 3, 0

    };

    prepare();
}

Cube::Cube(float x, float y, float z, float size) :
    Base(GL_TRIANGLES, 8)
{
    data = {
        // front
        x - size, y - size, z + size,
        x + size, y - size, z + size,
        x + size, y + size, z + size,
        x - size, y + size, z + size,
        // Back
        x + size, y - size, z - size,
        x - size, y - size, z - size,
        x - size, y + size, z - size,
        x + size, y + size, z - size,
    };
    // 0 bottom left
    // 1 bottom right
    // 2 top right
    // 3 top left
    // 4 Bottom right
    // 5 Bottom left
    // 6 Top left
    // 7 Top right
    indices = {
        // Front
        0, 1 ,3,
        1, 2, 3,
        // Back
        4, 5 ,7,
        5, 6, 7,
        // Left
        6, 0, 3,
        5, 6, 0,
        // Right
        7, 4, 2,
        2, 1, 4,
        // Bottom
        0, 1, 5,
        5, 4, 1,
        // Top
        3, 2, 6,
        6, 7, 2
    };

    prepare();


}
