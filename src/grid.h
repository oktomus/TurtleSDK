#ifndef __TURTLE_GRID__
#define __TURTLE_GRID__

#include <glm/vec2.hpp>
#include <vector>

class GridGenerator;

/**
 * @brief A point grid
 */
class Grid{

    friend GridGenerator;

public:

    /**
     * @brief Points of the grid
     */
    std::vector<glm::vec2> points;

    /**
     * @brief Indices of the grid
     */
    std::vector<unsigned int> indices;

private:

    /**
     * @brief Private constructor
     */
    Grid(){}

    /**
     * @brief The width and height of the grid
     */
    float size_;

    /**
     * @brief Number of slice per axis
     */
    unsigned int slicing_;
};

/**
 * @brief Grid generator
 */
class GridGenerator{

public:

    /**
     * @brief Generate a flat grid
     * @param float     The size
     * @param unsigned int     The number of slice on each axis
     * @return
     */
    static Grid flatGrid(float, unsigned int);

};


#endif
