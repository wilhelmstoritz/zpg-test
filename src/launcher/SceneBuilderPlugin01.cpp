#include "SceneBuilderPlugin01.h"

#include "resShaders.h"
#include "resModels.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin01::createShaders() {
    // vertex & fragment shaders
    this->m_shaderWarehouse->createVertexShader("vert01", VSHADER_01);
    this->m_shaderWarehouse->createFragmentShader("frag01", FSHADER_01);

    this->m_shaderWarehouse->createVertexShader("vert01_colorFromPosition", VSHADER_01_COLORFROMPOSITION);
    this->m_shaderWarehouse->createFragmentShader("frag01_colorFromPosition", FSHADER_01_COLORFROMPOSITION);

    this->m_shaderWarehouse->createVertexShader("vert01_colorData", VSHADER_01_COLORDATA);
    this->m_shaderWarehouse->createFragmentShader("frag01_colorData", FSHADER_01_COLORDATA);

    this->m_shaderWarehouse->createFragmentShader("frag01_yellow", FSHADER_01_YELLOW);

    // shader programs
    this->m_shaderWarehouse->createShaderProgram("shader01",
        *this->m_shaderWarehouse->getShader("vert01"),
        *this->m_shaderWarehouse->getShader("frag01"));

    this->m_shaderWarehouse->createShaderProgram("shader01_colorFromPosition",
        *this->m_shaderWarehouse->getShader("vert01_colorFromPosition"),
        *this->m_shaderWarehouse->getShader("frag01_colorFromPosition"));

    this->m_shaderWarehouse->createShaderProgram("shader01_colorData",
        *this->m_shaderWarehouse->getShader("vert01_colorData"),
        *this->m_shaderWarehouse->getShader("frag01_colorData"));

    this->m_shaderWarehouse->createShaderProgram("shader01_yellow",
        *this->m_shaderWarehouse->getShader("vert01"),
        *this->m_shaderWarehouse->getShader("frag01_yellow"));
}

void SceneBuilderPlugin01::createModels() {
    /* 1st task models */
    this->m_modelWarehouse->createVertexResources("res01_triangle",          MODEL_TRIANGLE,           ModelFactory::BUFFERINFOLIST_DEFAULT);
    this->m_modelWarehouse->createVertexResources("res01_triangleColorData", MODEL_TRIANGLE_COLORDATA, ModelFactory::BUFFERINFOLIST_POSITION_COLOR);
    this->m_modelWarehouse->createVertexResources("res01_square",            MODEL_SQUARE,             ModelFactory::BUFFERINFOLIST_DEFAULT);

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
    this->m_modelWarehouse->createVertexResources("res01_pentagon", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::BUFFERINFOLIST_DEFAULT);

    //this->m_modelWarehouse->createModel("model01_triangle",                  "shader01",                   "res01_triangle", 0, 3);
    //this->m_modelWarehouse->createModel("model01_triangleColorFromPosition", "shader01_colorFromPosition", "res01_triangle", 0, 3);
    this->m_modelWarehouse->createModel("model01_triangleColorData",         "shader01_colorData",         "res01_triangleColorData", 0, 3);
    this->m_modelWarehouse->createModel("model01_square",                    "shader01_yellow",            "res01_square", 0, 6);
    //this->m_modelWarehouse->createModel("model01_pentagon",                  "shader01",                   "res01_pentagon", 0, 15);
}
