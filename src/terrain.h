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

};

#endif
