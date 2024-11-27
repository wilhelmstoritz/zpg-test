#include "SceneBuilder.h"
#include "LightFlashlight.h"
#include "TransformationAnimationRotate.h"

#include "basicShaderResources.h"
#include "basicModelResources.h"
#include "ModelLibrary.h"
#include "modelLetters.h"
#include "tmpResources.h"

#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// include the standard C++ headers
//#include <cstdlib> // rand, srand
//#include <ctime>   // seeding random numbers

void SceneBuilder::createTemporaryScene() {
    //std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random number generator

    // skybox
    this->m_modelFactory->createModel(
        "skybox",
        //"shaderViewProjection", ModelLibrary::MODEL_SKYBOX_RNDCOLORS, ModelFactory::s_defaultPositionColorBufferList, 0, 36,
        //"shaderLambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        //"shaderPhong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        "shaderTMP", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        this->m_dimensions, glm::vec3(0.f), -this->m_dimensions / glm::vec3(2.f));
        //this->m_dimensions, glm::vec3(0.f), glm::vec3(-this->m_dimensions.x / 2.f, 0.f, -this->m_dimensions.z / 2.f));

    // models
    this->m_modelFactory->createVertexResources("tmpBushes", sizeof(bushes), bushes, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpGift", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpPlain", sizeof(plain), plain, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpSphere", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpSuziFlat", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpSuziSmooth", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("tmpTree", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList);

    this->m_modelFactory->createVertexResources("tmpWall", ModelLibrary::MODEL_BASIC_WALL, ModelFactory::s_defaultPositionNormalBufferList);

    //this->m_modelFactory->createModel("tmpBushes01", "shaderLambertian", "tmpBushes", 0, 8730,         glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-9.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpGift01", "shaderLambertian", "tmpGift", 0, 66624,            glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-6.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpPlain01", "shaderLambertian", "tmpPlain", 0, 6,              glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-3.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpSphere01", "shaderLambertian", "tmpSphere", 0, 2880,         glm::vec3(1.f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpSuziFlat01", "shaderLambertian", "tmpSuziFlat", 0, 2904,     glm::vec3(1.f), glm::vec3(0.f), glm::vec3(3.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpSuziSmooth01", "shaderLambertian", "tmpSuziSmooth", 0, 2904, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(6.f, 0.f, 0.f));
    //this->m_modelFactory->createModel("tmpTree01", "shaderLambertian", "tmpTree", 0, 92814,            glm::vec3(1.f), glm::vec3(0.f), glm::vec3(9.f, 0.f, 0.f));

    this->m_modelFactory->createModel("tmpWall01", "shaderTMP", "tmpWall", 0, 6, glm::vec3(10.f), glm::vec3(0.f), glm::vec3(0.f));

    //this->m_modelFactory->getModel("tmpBushes01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpGift01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpPlain01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpSphere01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(0.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpSuziFlat01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(3.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpSuziSmooth01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(6.f, 0.f, 0.f)));
    //this->m_modelFactory->getModel("tmpTree01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(9.f, 0.f, 0.f)));

    std::shared_ptr<TransformationAnimationRotate> animationRotate = std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(.01f, .02f, .03f));
    //this->m_modelFactory->getModel("tmpWall01")->getTransformation()->updateRotateStep(animationRotate);

    // light source
    Light* light = new Light("light01default", Light::LightType::POINT, glm::vec3(0.f, 40.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(glm::vec3(0.f, .3f, 0.f));
    light->setSpecularColor(glm::vec3(0.f, .3f, 0.0f));
    this->m_scene->addLight(light);

    light = new Light("light02", Light::LightType::SPOT, glm::vec3(8.f, 0.f, 1.f));
    light->setDirection(glm::vec3(-6.f, 0.f, -1.f));
    light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(glm::vec3(0.f, 0.f, 1.0f));
    light->setSpecularColor(glm::vec3(1.f, 0.f, 0.0f));
    this->m_scene->addLight(light);

    light = new Light("light03", Light::LightType::SPOT, glm::vec3(-100.f, 50.f, 100.f));
    light->setDirection(glm::vec3(2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(3.f);
    light->setDiffuseColor(glm::vec3(1.f, 1.f, 0.f)); // yellow
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.0f)); // white
    //this->m_scene->addLight(light);

    // camera position & flashlight
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 0.f, 20.f),
        glm::vec3(0.f, 0.f, -1.f));

    LightFlashlight* flashlight = new LightFlashlight("flashlight", this->m_scene->getCamera());
    this->m_scene->addLight(flashlight);
}
