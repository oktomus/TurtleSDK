#ifndef __TURTLE_OBJECT__
#define __TURTLE_OBJECT__

#include <memory>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "shader.h"

class Turtle;

/**
  * @brief Wrapper of a model
  * Can be positioned in the spaces
  * Usefulle when creating instances, avoid to duplicate the model
  */
class Object
{

    friend Turtle;

public:

    /**
      * @brief Create an empty object. Not used in the application yet.
      */
    Object();

    /**
      * @brief Create a world object
      * @param  The model linked to the object
      */
    Object(std::shared_ptr<Model>);

    /**
     * @brief Draw the model's meshes
     * @param shader    Shader used to draw
     */
    void draw(const Shader & shader);
    
    void ui();

private:

    std::shared_ptr<Model> model_;

    glm::vec3 translate_ = {0, 0, 0};
    glm::vec3 scale_ = {1, 1, 1};
    glm::vec3 rotate_ = {0, 0, 0};

    glm::mat4 transform_;

};

#endif
