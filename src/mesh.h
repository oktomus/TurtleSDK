#ifndef __TURTLE_MESH__
#define __TURTLE_MESH__

// Turtle
#include "shader.h"

// STD
#include <vector>

// Graphic
#include <assimp/Importer.hpp>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 TexCoords;
    /*
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    */
};

struct Texture{
    GLuint id;
    std::string type;
};

class Model;
class Terrain;

/**
 * @brief Mesh wrapper.
 *
 * Keep a link on the VBOs and VAO of a model.
 */
class Mesh
{

    friend Model;
    friend Terrain;

public:

    Mesh(const std::vector<Vertex> &vertices,
         const std::vector<GLuint> & indices,
         const std::vector<Texture> & textures);

    /**
     * @brief Draw the model
     */
    void draw(const Shader & shader, const GLenum& mode = -1) const;

    /**
     * @brief Update the data buffer
     */
    void updateDataBuffer();

private:

    std::vector<Texture> textures_;
    std::vector<Vertex> points_;
    std::vector<GLuint> indices_;

    /**
     * @brief Mode used to draw.
     * GL_TRIANGLES, QUADS, ...
     */
    GLenum _drawMode = GL_TRIANGLES;

    /**
     * @brief Vertex Array Object id.
     */
    GLuint _vaoId;

    /**
     * @brief Vertex buffer object id
     */
    GLuint _vboId;

    /**
     * @brief Generate and allocate a buffer in the VAO
     * @param idLocation        Where to store the id
     * @param bufType           The buffer type
     * @param data              The points to copy in the buffer
     */
    template <class T>
    void addBuffer(
            GLuint &idLocation,
            GLenum bufType,
            const std::vector<T>& data);

    void init();


};



#endif
