#ifndef __TURTLE_GROUND__
#define __TURTLE_GROUND__

#include "model.h"

/**
 * @brief Low poly ground of the world
 */
class Ground: public Model
{

public:

    /**
     * @brief Create the ground
     */
    Ground();

    float size_;
    float baseHeight_;
    float heightFactor_ = 3;
    glm::vec3 color_ = {0.39, 0.78, 0.36};
    glm::vec3 outsideColor_ = {0.4, 0.4, 0.4};

    /**
     * @brief Generate a random height for the ground
     */
    void randomize();
    void draw(const Shader & shader);

    void ui();

private:

    void updateVars();

};

#endif
