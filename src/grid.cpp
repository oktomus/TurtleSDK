#include "grid.h"

Grid GridGenerator::flatGrid(float pSize, unsigned int pSlicing)
{
    // Result grid
    Grid res;
    res.size_ = pSize;
    res.slicing_ = pSlicing;

    // Preparation
    float x = -pSize / 2.0;
    float z = -pSize / 2.0;
    res.points.reserve(pSlicing * pSlicing);

    float tr = pSize / float(pSlicing); // Each point translation

    // Create points
    while(z <= pSize/2)
    {
       res.points.push_back(glm::vec2(x, z));

       x += tr;
       if(x > pSize/2)
       {
           x = -pSize/2;
           z += tr;
       }
    }

    res.indices.reserve(6 * (pSlicing - 1) * (pSlicing - 1));

    for(size_t row = 0; row < pSlicing; row++)
    {
        for(size_t col = 0; col < pSlicing; col++)
        {
            // top left
            res.indices.push_back(row * (pSlicing + 1) + col);
            // bottom left
            res.indices.push_back((row + 1) * (pSlicing + 1) + col);
            // bottom right
            res.indices.push_back((row + 1) * (pSlicing + 1) + col + 1);
            // top right
            res.indices.push_back(row * (pSlicing + 1) + col + 1);
            // top left
            res.indices.push_back(row * (pSlicing + 1) + col);
            // bottom right
            res.indices.push_back((row + 1) * (pSlicing + 1) + col + 1);

        }

    }

    return res;
}
