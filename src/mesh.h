#ifndef __TURTLE_MESH__
#define __TURTLE_MESH__

// STD
#include <vector>

// Graphic
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @brief Mesh wrapper.
 *
 * Keep a link on the VBOs and VAO of a model.
 */
class Mesh
{

private:

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
     *
     * If 0, ebo is not used.
     */
    GLuint _eboCount;

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

public:

    Mesh();

    /**
     * @brief Set the points of the model
     * @param data      The points
     */
    void setPoints(const std::vector<GLfloat>& data);

    /**
     * @brief Set the element object array buffer
     * @param data      Indices to use to draw the model
     */
    void setIndices(const std::vector<unsigned int>& data);

    /**
     * @brief Draw the model
     */
    void draw() const;

    /**
     * @brief Draw the points of the model
     */
    void drawPoints() const;

    /**
     * @brief Get the transform matrix of the model
     * @return A 4 by 4 matrix
     */
    const glm::mat4& getTransform();

    /**
     * @brief Create a triangle with 3 points
     * @param points    A vector of 3 points
     * @return          The corresponding mesh
     */
    static Mesh triangle(const std::vector<GLfloat> & points);

};



#endif
