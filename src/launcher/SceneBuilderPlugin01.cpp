#include "SceneBuilderPlugin01.h"

#include "resShaders.h"
#include "resModels.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin01::createShaders() {
    // vertex & fragment shaders
    this->m_shaderWarehouse->createVertexShader  ("vert:basic", VSHADER_BASIC);
    this->m_shaderWarehouse->createFragmentShader("frag:basic", FSHADER_BASIC);

    this->m_shaderWarehouse->createVertexShader  ("vert:color_from_position", VSHADER_COLORFROMPOSITION);
    this->m_shaderWarehouse->createFragmentShader("frag:color_from_position", FSHADER_COLORFROMPOSITION);

    this->m_shaderWarehouse->createVertexShader  ("vert:color_data", VSHADER_COLORDATA);
    this->m_shaderWarehouse->createFragmentShader("frag:color_data", FSHADER_COLORDATA);

    this->m_shaderWarehouse->createFragmentShader("frag:yellow", FSHADER_YELLOW);

    // shader programs
    this->m_shaderWarehouse->createShaderProgram("shader:basic",
        *this->m_shaderWarehouse->getShader("vert:basic"),
        *this->m_shaderWarehouse->getShader("frag:basic"));

    this->m_shaderWarehouse->createShaderProgram("shader:color_from_position",
        *this->m_shaderWarehouse->getShader("vert:color_from_position"),
        *this->m_shaderWarehouse->getShader("frag:color_from_position"));

    this->m_shaderWarehouse->createShaderProgram("shader:color_data",
        *this->m_shaderWarehouse->getShader("vert:color_data"),
        *this->m_shaderWarehouse->getShader("frag:color_data"));

    this->m_shaderWarehouse->createShaderProgram("shader:yellow",
        *this->m_shaderWarehouse->getShader("vert:basic"),
        *this->m_shaderWarehouse->getShader("frag:yellow"));
}

void SceneBuilderPlugin01::createModels() {
    /* 1st task models */
    this->m_modelWarehouse->createVertexResources("res:triangle",            MODEL_TRIANGLE,           ModelFactory::BUFFERINFOLIST_DEFAULT);
    this->m_modelWarehouse->createVertexResources("res:triangle_color_data", MODEL_TRIANGLE_COLORDATA, ModelFactory::BUFFERINFOLIST_POSITION_COLOR);
    this->m_modelWarehouse->createVertexResources("res:square",              MODEL_SQUARE,             ModelFactory::BUFFERINFOLIST_DEFAULT);

    float PENTAGON_POINTS[] = { // 15 vertices (3 floats per vertex; 5 triangles)
        // 1st triangle
         0.0f,     0.0f,    0.0f, // centre
         1.0f,     0.0f,    0.0f, // apex #1
         0.3090f,  0.9511f, 0.0f, // apex #2
        // 2nd triangle
         0.0f,     0.0f,    0.0f, // centre
         0.3090f,  0.9511f, 0.0f, // apex #2
        -0.8090f,  0.5878f, 0.0f, // apex #3
        // 3rd triangle
         0.0f,     0.0f,    0.0f, // centre
        -0.8090f,  0.5878f, 0.0f, // apex #3
        -0.8090f, -0.5878f, 0.0f, // apex #4
        // 4th triangle
         0.0f,     0.0f,    0.0f, // centre
        -0.8090f, -0.5878f, 0.0f, // apex #4
         0.3090f, -0.9511f, 0.0f, // apex #5
        // 5th triangle
         0.0f,     0.0f,    0.0f, // centre
         0.3090f, -0.9511f, 0.0f, // apex #5
         1.0f,     0.0f,    0.0f  // apex #1
    };
    this->m_modelWarehouse->createVertexResources("res:pentagon", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::BUFFERINFOLIST_DEFAULT);

    //this->m_modelWarehouse->createModel("01::triangle",                     "shader:basic",               "res:triangle", 0, 3);
    //this->m_modelWarehouse->createModel("01::triangle:color_from_position", "shader:color_from_position", "res:triangle", 0, 3);
    this->m_modelWarehouse->createModel("01::triangle:color_data",          "shader:color_data",          "res:triangle_color_data", 0, 3);
    this->m_modelWarehouse->createModel("01::square",                       "shader:yellow",              "res:square", 0, 6);
    //this->m_modelWarehouse->createModel("01::pentagon",                     "shader:basic",               "res:pentagon", 0, 15);
}
