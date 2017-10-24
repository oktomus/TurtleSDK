
/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/


//#include <imgui.h>
// STL
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

// System
#include <cstdio>

// Graphics
// - GLEW (always before "gl.h")
#include <GL/glew.h>
// - GL
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
// - GLUT
#include <GL/glut.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Custom
#include "model/primitive.h"
#include "world.h"
#include "shader/baseShader.h"

/******************************************************************************
 ****************************** NAMESPACE SECTION *****************************
 ******************************************************************************/

/******************************************************************************
 ************************* DEFINE AND CONSTANT SECTION ************************
 ******************************************************************************/


world::World globalWorld;

// Shader program
std::vector<shader::Base> materials;

// Mesh parameters
glm::vec3 _meshColor;

std::vector<std::unique_ptr<model::Base>> models;


/******************************************************************************
 ***************************** TYPE DEFINITION ********************************
 ******************************************************************************/

/******************************************************************************
 ***************************** METHOD DEFINITION ******************************
 ******************************************************************************/

/******************************************************************************
 ***************************** METHOD DEFINITION ******************************
 ******************************************************************************/

bool initialize();
bool checkExtensions();
bool initializeShaderProgram();
bool finalize();

/******************************************************************************
 * Initialize all
 ******************************************************************************/
bool initialize()
{
    std::cout << "Initialize all..." << std::endl;

    bool statusOK = true;

    if ( statusOK )
    {
        statusOK = checkExtensions();
    }

    if ( statusOK )
    {
        statusOK = initializeShaderProgram();
    }

    globalWorld.init();


    _meshColor = glm::vec3(0.f, 1.f, 0.f);


       models.push_back(std::make_unique<model::Triangle>(
       -.3f, -.3f, 0.f, 
       .3f, -.3f, 0.f, 
       .15f, .15f, 0.f)
       );

       models.push_back(std::make_unique<model::Triangle>(
       .5f, -.3f, 0.f, 
       .9f, .0f, 0.f, 
       .7f, .3f, 0.f
       ));

       models.push_back(std::make_unique<model::Quad>(
       -.5f, -.5f, 0.f,
       .5f, -.5f, 0.f,
       .5f, .5f, 0.f,
       -.5f, .5f, 0.f
       ));

    models.push_back(std::make_unique<model::Cube>(0.f, 0.f, 0.f, .4f));
    /*
       models.push_back(std::make_unique<model::Triangle>(
       .45f, -.45f, 0.f ,
       -.45f, -.55f, 0.f,
       .55f, .55f, 0.f
       ));
     */

    return statusOK;
}

/******************************************************************************
 * Finalize all
 ******************************************************************************/
bool finalize()
{
    bool statusOK = true;

    std::cout << "Finalize all..." << std::endl;

    return statusOK;
}

/******************************************************************************
 * Check GL extensions
 ******************************************************************************/
bool checkExtensions()
{
    bool statusOK = true;

    std::cout << "Check GL extensions..." << std::endl;

    return statusOK;
}

/******************************************************************************
 * Initialize shader program
 ******************************************************************************/
bool initializeShaderProgram()
{

    bool statusOK = true;

    std::cout << "Initialize shader program...\n" << std::endl;

    materials.push_back(shader::Base("shaders/animated"));

    return statusOK;
}

/******************************************************************************
 * Callback to display the scene
 ******************************************************************************/
void display( void )
{
    // Timer info
    const int currentTime = glutGet( GLUT_ELAPSED_TIME );

    //ImGui::Text("Hello, world!");

    //--------------------
    // START frame
    //--------------------
    // Clear the color buffer (of the main framebuffer)
    // - color used to clear
    glClearColor( 0.f, 0.f, 0.f, 0.f );
    glClearDepth( 1.f );
    // - clear the "color" framebuffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_BLEND);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    //--------------------
    // Activate shader program
    //--------------------
    shader::Base& mat = materials.at(0);
    mat.use();

    //--------------------
    // Send uniforms to GPU
    //--------------------
    GLint uniformLocation;
    // Retrieve camera parameters
    // Retrieve 3D model / scene parameters
    glm::mat4 modelMatrix;
    const bool useMeshAnimation = true; // TODO: use keyboard to activate/deactivate

    if ( useMeshAnimation )
    {
        modelMatrix = glm::rotate( modelMatrix, static_cast< float >( currentTime ) * 0.001f, glm::vec3( 0.0f, 1.f, 0.f ) );
    }

    // Camera
    // - view matrix
    uniformLocation = glGetUniformLocation( mat.id(), "viewMatrix" );
    if ( uniformLocation >= 0 )
    {
        glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, glm::value_ptr(globalWorld.currentCamera().viewMatrix() ) );
    }
    // - projection matrix
    uniformLocation = glGetUniformLocation( mat.id(), "projectionMatrix" );
    if ( uniformLocation >= 0 )
    {
        glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, glm::value_ptr(globalWorld.currentCamera().projectionMatrix() ) );
    }
    // Mesh
    // - model matrix
    uniformLocation = glGetUniformLocation( mat.id(), "modelMatrix" );
    if ( uniformLocation >= 0 )
    {
        glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, glm::value_ptr( modelMatrix ) );
    }
    // - mesh color
    uniformLocation = glGetUniformLocation( mat.id(), "meshColor" );
    if ( uniformLocation >= 0 )
    {
        glUniform3fv( uniformLocation, 1, glm::value_ptr( _meshColor ) );
    }
    // Animation
    uniformLocation = glGetUniformLocation( mat.id(), "time" );
    if ( uniformLocation >= 0 )
    {
        glUniform1f( uniformLocation, static_cast< float >( currentTime ) );
    }

    glPolygonMode( GL_FRONT, GL_FILL );

    for (std::unique_ptr<model::Base>& mod: models)
    {
        mod->draw();
        mod->draw_points();
    }

    // Deactivate current shader program
    glUseProgram( 0 );

    //--------------------
    // END frame
    //--------------------
    // OpenGL commands are not synchrone, but asynchrone (stored in a "command buffer")
    glFlush();
    // Swap buffers for "double buffering" display mode (=> swap "back" and "front" framebuffers)
    glutSwapBuffers();
}

/******************************************************************************
 * Callback continuously called when events are not being received
 ******************************************************************************/
void idle( void )
{
    // Mark current window as needing to be redisplayed
    glutPostRedisplay();
}

/******************************************************************************
 * Main function
 ******************************************************************************/
int main( int argc, char** argv )
{
    std::cout << "TP3 - Transform" << std::endl;

    // Initialize the GLUT library
    glutInit( &argc, argv );

    //glutInitContextVersion( 3, 3 );
    //glutInitContextProfile( GLUT_COMPATIBILITY_PROFILE );

    // Grahics window
    // - configure the main framebuffer to store rgba colors,
    //   and activate double buffering (for fluid/smooth visualization)
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    // - window size and position
    glutInitWindowSize( 640, 480 );
    glutInitWindowPosition( 50, 50 );
    // - create the window
    glutCreateWindow( "TurtleSDK" );

    // Callbacks
    // - callback called when displaying window (user custom fonction pointer: "void f( void )")
    glutDisplayFunc( display );
    // - callback continuously called when events are not being received
    glutIdleFunc( idle );

    // Initialize the GLEW library
    // - mandatory to be able to use OpenGL extensions,
    //   because OpenGL core API is made of OpenGL 1 and other functions are null pointers (=> segmentation fault !)
    //   Currently, official OpenGL version is 4.5 (or 4.6)
    GLenum error = glewInit();
    if ( error != GLEW_OK )
    {
        fprintf( stderr, "Error: %s\n", glewGetErrorString( error ) );
        exit( -1 );
    }

    // Initialize all your resources (graphics, data, etc...)
    initialize();

    // Enter the GLUT main event loop (waiting for events: keyboard, mouse, refresh screen, etc...)
    glutMainLoop();

    // Clean all
    //finalize();
}
