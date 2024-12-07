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
    this->m_shaderWarehouse->createVertexShader("vert02_viewProjectionMatrix", VSHADER_02_VIEW_PROJECTION_MATRIX);
    this->m_shaderWarehouse->createFragmentShader("frag02_viewProjectionMatrix", FSHADER_02_VIEW_PROJECTION_MATRIX);

    this->m_shaderWarehouse->createShaderProgram("shader02_viewProjectionMatrix",
        *this->m_shaderWarehouse->getShader("vert02_viewProjectionMatrix"),
        *this->m_shaderWarehouse->getShader("frag02_viewProjectionMatrix"));
}

void SceneBuilderPlugin02a::createModels() {
    this->m_modelWarehouse->createModel("model02_bushes",     "shader02_viewProjectionMatrix", sizeof(bushes),     bushes,     ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 8730);
    this->m_modelWarehouse->createModel("model02_gift",       "shader02_viewProjectionMatrix", sizeof(gift),       gift,       ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 66624);
    this->m_modelWarehouse->createModel("model02_plain",      "shader02_viewProjectionMatrix", sizeof(plain),      plain,      ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 6);
    this->m_modelWarehouse->createModel("model02_sphere",     "shader02_viewProjectionMatrix", sizeof(sphere),     sphere,     ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 2880);
    this->m_modelWarehouse->createModel("model02_suziFlat",   "shader02_viewProjectionMatrix", sizeof(suziFlat),   suziFlat,   ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 2904);
    this->m_modelWarehouse->createModel("model02_suziSmooth", "shader02_viewProjectionMatrix", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 2904);
    this->m_modelWarehouse->createModel("model02_tree",       "shader02_viewProjectionMatrix", sizeof(tree),       tree,       ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 92814);

    this->m_modelWarehouse->getModel("model02_bushes"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("model02_gift"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("model02_plain"     )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("model02_sphere"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(0.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("model02_suziFlat"  )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(3.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("model02_suziSmooth")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(6.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("model02_tree"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(9.f, 0.f, 0.f)));

    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 0.f, 16.f),
        glm::vec3(0.f, 0.f, -1.f));
}
