#include "SceneBuilderPlugin01.h"
#include "resShaders.h"
#include "resModels.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin01::createShaders() {
    // vertex & fragment shaders
    this->m_shaderFactory->createVertexShader("basic_vshader", BASIC_VSHADER);
    this->m_shaderFactory->createFragmentShader("basic_fshader", BASIC_FSHADER);

    this->m_shaderFactory->createVertexShader("basic_vshaderColorFromPosition", BASIC_VSHADER_COLORFROMPOSITION);
    this->m_shaderFactory->createFragmentShader("basic_fshaderColorFromPosition", BASIC_FSHADER_COLORFROMPOSITION);

    this->m_shaderFactory->createVertexShader("basic_vshaderColorData", BASIC_VSHADER_COLORDATA);
    this->m_shaderFactory->createFragmentShader("basic_fshaderColorData", BASIC_FSHADER_COLORDATA);

    this->m_shaderFactory->createFragmentShader("basic_fshaderYellow", BASIC_FSHADER_YELLOW);

    // shader programs
    this->m_shaderFactory->createShaderProgram("basic_shader",
        *this->m_shaderFactory->getShader("basic_vshader"),
        *this->m_shaderFactory->getShader("basic_fshader"));

    this->m_shaderFactory->createShaderProgram("basic_shaderColorFromPosition",
        *this->m_shaderFactory->getShader("basic_vshaderColorFromPosition"),
        *this->m_shaderFactory->getShader("basic_fshaderColorFromPosition"));

    this->m_shaderFactory->createShaderProgram("basic_shaderColorData",
        *this->m_shaderFactory->getShader("basic_vshaderColorData"),
        *this->m_shaderFactory->getShader("basic_fshaderColorData"));

    this->m_shaderFactory->createShaderProgram("basic_shaderYellow",
        *this->m_shaderFactory->getShader("basic_vshader"),
        *this->m_shaderFactory->getShader("basic_fshaderYellow"));
}

void SceneBuilderPlugin01::createModels() {
    /* 1st task models */
    this->m_modelFactory->createVertexResources("1stTriangle", MODEL_TRIANGLE, ModelFactory::s_defaultBufferList);
    this->m_modelFactory->createVertexResources("1stTriangleColorData", MODEL_TRIANGLE_COLORDATA, ModelFactory::s_defaultPositionColorBufferList);
    this->m_modelFactory->createVertexResources("1stSquare", MODEL_SQUARE, ModelFactory::s_defaultBufferList);
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
    this->m_modelFactory->createVertexResources("1stPentagon", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::s_defaultBufferList);

    //this->m_modelFactory->createModel("1stTriangle", "basic_shader", "1stTriangle", 0, 3);
    //this->m_modelFactory->createModel("1stTriangleColorFromPosition", "basic_shaderColorFromPosition", "1stTriangle", 0, 3);
    this->m_modelFactory->createModel("1stTriangleColorData", "basic_shaderColorData", "1stTriangleColorData", 0, 3);
    this->m_modelFactory->createModel("1stSquare", "basic_shaderYellow", "1stSquare", 0, 6);
    this->m_modelFactory->createModel("1stPentagon", "basic_shader", "1stPentagon", 0, 15);

    // all at once; some vertex resources are created twice this way
    //this->m_modelFactory->createModel("1stTriangle", "basic_shader", MODEL_TRIANGLE, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("1stTriangleColorFromPosition", "basic_shaderColorFromPosition", MODEL_TRIANGLE, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("1stTriangleColorData", "basic_shaderColorData", MODEL_TRIANGLE_COLORDATA, ModelFactory::s_defaultPositionColorBufferList, 0, 3);
    //this->m_modelFactory->createModel("1stSquare", "basic_shaderYellow", MODEL_SQUARE, ModelFactory::s_defaultBufferList, 0, 6);
    //this->m_modelFactory->createModel("1stPentagon", "basic_shader", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::s_defaultBufferList, 0, 15);
}
