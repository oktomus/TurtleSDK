#ifndef __TURTLE_MODEL__
#define __TURTLE_MODEL__

// Turtle
#include "shader.h"
#include "mesh.h"

// STD
#include <string>
#include <vector>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/postprocess.h>

/**
 * @brief A set of one or more mesh.
 */
class Model{

public:

    /**
     * @brief Create a model from a given path
     * @param path      Path to the object (obj)
     */
    Model(const std::string & path);

    /**
     * @brief Draw the model's meshes
     * @param shader    Shader used to draw
     */
    void draw(const Shader & shader);


    void ui();

    glm::vec3 translate_;
    glm::vec3 scale_;
    glm::vec3 rotate_;

    glm::mat4 transform_;

private:

    /**
     * @brief Meshes included in the model
     */
    std::vector<Mesh> meshes;

    /**
     * @brief The directory in which the object is stored
     */
    std::string directory;

    /**
     * @brief Load the given model
     * @param path      Path to the model
     */
    void loadModel(const std::string & path);

    /**
     * @brief Create a mesh base on an assimp mesh node
     * @param mesh      The assimp mesh node
     * @param scene     The assimp scene node
     * @return          The mesh
     */
    Mesh processAiMesh(aiMesh *mesh, const aiScene * scene);


    /**
      * @brief Load object textures inside opengl
      */
    std::vector<Texture> loadMaterialTextures(
                     aiMaterial *mat,
                     aiTextureType type,
                     std::string typeName);
};

GLuint textureFromFile(const char *path, const std::string &directory, bool gamma = false);

#endif
