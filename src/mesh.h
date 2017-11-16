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

/**
 * @brief Mesh wrapper.
 *
 * Keep a link on the VBOs and VAO of a model.
 */
class Mesh
{

public:

    Mesh(const std::vector<Vertex> &vertices,
         const std::vector<GLuint> & indices,
         const std::vector<Texture> & textures);

    /**
     * @brief Draw the model
     */
    void draw(const Shader & shader, const GLenum& mode = -1) const;

    /**
     * @brief Draw the points of the model
     */
    void drawPoints(const Shader & shader) const;

    /**
     * @brief Get the transform matrix of the model
     * @return A 4 by 4 matrix
     */
    const glm::mat4& getTransform();

    /**
     * @brief Create a triangle with 3 points
     * @return          The corresponding mesh
     */
    static Mesh triangle();

    /**
     * @brief Create one quad
     * @return          The mesh
     */
    static Mesh quad();

private:

    std::vector<Texture> textures_;

    /**
     * @brief Model's position
     */
    glm::vec3 _position;

    /**
     * @brief Model's rotation
     */
    glm::vec3 _rotation;

    /**
     * @brief Model's scale
     */
    glm::vec3 _scale;

    /**
     * @brief Model's transform matrix
     */
    glm::mat4 _transform;

    /**
     * @brief State of the transform matrix.
     *
     * If true, the transfrom matrix should be recalculated before
     * returning it.
     *
     * Set to true each time the position, rotation or scale is
     * changed.
     */
    bool _transformUpdate;

    /**
     * @brief Mode used to draw.
     * GL_TRIANGLES, QUADS, ...
     */
    GLenum _drawMode;

    /**
     * @brief Vertex Array Object id.
     */
    GLuint _vaoId;

    /**
     * @brief Number of point in the mesh.
     */
    GLuint _vertCount;

    /**
     * @brief Amount of indices in the EBO.
     */
    GLuint _indicesCount;

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


};



#endif
