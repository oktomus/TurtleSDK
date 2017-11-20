#ifndef __TURTLE_TERRAIN__
#define __TURTLE_TERRAIN__

#include "grid.h"
#include "model.h"

/**
 * @brief A Terrain
 */
class Terrain: public Model
{

public:

    /**
     * @brief Generate a terrain from a grid
     */
    Terrain(const Grid&);

    /**
     * @brief Randomize the height of the terrain using a perlin noise
     */
    void randomize();

    void ui();

    /**
     * @brief Randomize a given set of point
     * @param pPoints
     */
    static void randomize(std::vector<Vertex> & pPoints, unsigned int pSlicing);

private:

    /**
     * @brief Width of the terrain
     */
    float width_;

    /**
     * @brief Height of the terrain
     */
    float height_;

    /**
     * @brief Number of slice on the terrain
     */
    unsigned int slicing_;

};

#endif
