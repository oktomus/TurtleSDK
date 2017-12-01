#ifndef __TURTLE_SKYBOX__
#define __TURTLE_SKYBOX__

// Turtle
#include "shader.h"

// STD
#include <string>
#include <vector>

class Turtle;

/**
 * @brief A Cubemap
 */
class SkyBox{

    friend Turtle;

public:

    /**
     * @brief Create a skybox by specifying the file path and the extension
     * ex: world, .png, will use world_bk.png, ...
     */
    SkyBox(const std::string &, const std::string &);

    /**
     * @brief Draw the Skybox
     */
    void draw(Shader & sh);

protected:

    GLuint vao;

    GLuint cubemap;

private:

    /**
     * @brief Tell if the object should be drawn or not
     */
    bool draw_ = true;

    /**
      * Load the cubemap textures
      */
    unsigned int loadCubemap(const std::vector<std::string>&);

};

#endif
