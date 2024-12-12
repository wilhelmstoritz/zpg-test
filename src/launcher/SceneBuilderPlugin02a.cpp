#include "SceneBuilderPlugin02a.h"

#include "resShaders.h"

#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin02a::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createVertexShader  ("vert:view_projection_matrix", VSHADER_VIEW_PROJECTION_MATRIX);
    this->m_shaderWarehouse->createFragmentShader("frag:view_projection_matrix", FSHADER_VIEW_PROJECTION_MATRIX);

    this->m_shaderWarehouse->createShaderProgram("shader:view_projection_matrix",
        *this->m_shaderWarehouse->getShader("vert:view_projection_matrix"),
        *this->m_shaderWarehouse->getShader("frag:view_projection_matrix"));
}

void SceneBuilderPlugin02a::createModels() {
    this->m_modelWarehouse->createModel("02::bushes",     "shader:view_projection_matrix", sizeof(bushes),     bushes,     ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 8730);
    this->m_modelWarehouse->createModel("02::gift",       "shader:view_projection_matrix", sizeof(gift),       gift,       ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 66624);
    this->m_modelWarehouse->createModel("02::plain",      "shader:view_projection_matrix", sizeof(plain),      plain,      ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 6);
    this->m_modelWarehouse->createModel("02::sphere",     "shader:view_projection_matrix", sizeof(sphere),     sphere,     ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 2880);
    this->m_modelWarehouse->createModel("02::suziFlat",   "shader:view_projection_matrix", sizeof(suziFlat),   suziFlat,   ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 2904);
    this->m_modelWarehouse->createModel("02::suziSmooth", "shader:view_projection_matrix", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 2904);
    this->m_modelWarehouse->createModel("02::tree",       "shader:view_projection_matrix", sizeof(tree),       tree,       ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 92814);

    this->m_modelWarehouse->getModel("02::bushes"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02::gift"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02::plain"     )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02::sphere"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 0.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02::suziFlat"  )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 3.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02::suziSmooth")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 6.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02::tree"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 9.f, 0.f, 0.f)));

    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 0.f, 16.f),
        glm::vec3(0.f, 0.f, -1.f));
}
