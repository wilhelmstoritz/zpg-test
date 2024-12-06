#include "SceneBuilderPlugin_scene02.h"
#include "resShaders.h"
#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin_scene02::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderFactory->createVertexShader("vshaderViewProjection", VSHADER_VIEW_PROJECTION);
    this->m_shaderFactory->createFragmentShader("fshaderViewProjection", FSHADER_VIEW_PROJECTION);

    this->m_shaderFactory->createShaderProgram("shaderViewProjection",
        *this->m_shaderFactory->getShader("vshaderViewProjection"),
        *this->m_shaderFactory->getShader("fshaderViewProjection"));
}

void SceneBuilderPlugin_scene02::createModels() {
    // first/also try with the 'defaultColorData' shader program
    this->m_modelFactory->createModel("2ndBushes", "shaderViewProjection", sizeof(bushes), bushes, ModelFactory::s_defaultPositionNormalBufferList, 0, 8730);
    this->m_modelFactory->createModel("2ndGift", "shaderViewProjection", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624);
    this->m_modelFactory->createModel("2ndPlain", "shaderViewProjection", sizeof(plain), plain, ModelFactory::s_defaultPositionNormalBufferList, 0, 6);
    this->m_modelFactory->createModel("2ndSphere", "shaderViewProjection", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList, 0, 2880);
    this->m_modelFactory->createModel("2ndSuziFlat", "shaderViewProjection", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 2904);
    this->m_modelFactory->createModel("2ndSuziSmooth", "shaderViewProjection", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 2904);
    this->m_modelFactory->createModel("2ndTree", "shaderViewProjection", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList, 0, 92814);

    this->m_modelFactory->getModel("2ndBushes")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndGift")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndPlain")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndSphere")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(0.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndSuziFlat")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(3.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndSuziSmooth")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(6.f, 0.f, 0.f)));
    this->m_modelFactory->getModel("2ndTree")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(9.f, 0.f, 0.f)));

    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 0.f, 16.f),
        glm::vec3(0.f, 0.f, -1.f));
}
