#include "SceneBuilderPlugin01.h"
#include "Config.h"

#include "resShaders.h"
#include "resModels.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPlugin01::setSceneProperties(Scene* t_scene) {
    t_scene->setTitle("1 | "
        + Config::WINDOW_TITLE
        + Config::WINDOW_TITLE_HELP);
}

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
    this->m_shaderWarehouse->createShaderProgram("01::shader:basic",
        *this->m_shaderWarehouse->getShader("vert:basic"),
        *this->m_shaderWarehouse->getShader("frag:basic"));

    this->m_shaderWarehouse->createShaderProgram("01::shader:color_from_position",
        *this->m_shaderWarehouse->getShader("vert:color_from_position"),
        *this->m_shaderWarehouse->getShader("frag:color_from_position"));

    this->m_shaderWarehouse->createShaderProgram("01::shader:color_data",
        *this->m_shaderWarehouse->getShader("vert:color_data"),
        *this->m_shaderWarehouse->getShader("frag:color_data"));

    this->m_shaderWarehouse->createShaderProgram("01::shader:yellow",
        *this->m_shaderWarehouse->getShader("vert:basic"),
        *this->m_shaderWarehouse->getShader("frag:yellow"));
}

void SceneBuilderPlugin01::createModels() {
    /* 1st task models */
    this->m_modelWarehouse->createVertexResources("res:triangle",            MODEL_TRIANGLE,           ModelFactory::BUFFERINFOLIST_POSITION);
    this->m_modelWarehouse->createVertexResources("res:triangle_color_data", MODEL_TRIANGLE_COLORDATA, ModelFactory::BUFFERINFOLIST_POSITION_COLOR);
    this->m_modelWarehouse->createVertexResources("res:square",              MODEL_SQUARE,             ModelFactory::BUFFERINFOLIST_POSITION);

    float PENTAGON_POINTS[] = { // 15 vertices (3 floats per vertex; 5 triangles)
        // 1st triangle
         0.f,   0.f,  0.f, // centre
         1.f,   0.f,  0.f, // apex #1
          .3f,  1.f,  0.f, // apex #2
        // 2nd triangle
         0.f,   0.f,  0.f, // centre
          .3f,  1.f,  0.f, // apex #2
         -.8f,   .6f, 0.f, // apex #3
        // 3rd triangle
         0.f,   0.f,  0.f, // centre
         -.8f,   .6f, 0.f, // apex #3
         -.8f,  -.6f, 0.f, // apex #4
        // 4th triangle
         0.f,   0.f,  0.f, // centre
         -.8f,  -.6f, 0.f, // apex #4
          .3f, -1.f,  0.f, // apex #5
        // 5th triangle
         0.f,   0.f,  0.f, // centre
          .3f, -1.f,  0.f, // apex #5
         1.f,   0.f,  0.f  // apex #1
    };
    this->m_modelWarehouse->createVertexResources("res:pentagon", sizeof(PENTAGON_POINTS), PENTAGON_POINTS, ModelFactory::BUFFERINFOLIST_POSITION);

    this->m_modelWarehouse->createModel("01::triangle",                     "01::shader:basic",               "res:triangle", 0, 3);
    this->m_modelWarehouse->createModel("01::triangle:color_from_position", "01::shader:color_from_position", "res:triangle", 0, 3);
    this->m_modelWarehouse->createModel("01::triangle:color_data",          "01::shader:color_data",          "res:triangle_color_data", 0, 3);
    this->m_modelWarehouse->createModel("01::square",                       "01::shader:yellow",              "res:square", 0, 6);
    this->m_modelWarehouse->createModel("01::pentagon",                     "01::shader:basic",               "res:pentagon", 0, 15);
}

void SceneBuilderPlugin01::addContextToScene() {
	// add models to the scene
    //this->m_scene->addModel("triangle",                     this->m_modelWarehouse->getModel("01::triangle"));
    //this->m_scene->addModel("triangle:color_from_position", this->m_modelWarehouse->getModel("01::triangle:color_from_position"));
    this->m_scene->addModel("triangle:color_data",          this->m_modelWarehouse->getModel("01::triangle:color_data"));
	this->m_scene->addModel("square",                       this->m_modelWarehouse->getModel("01::square"));
	this->m_scene->addModel("pentagon",                     this->m_modelWarehouse->getModel("01::pentagon"));
}
