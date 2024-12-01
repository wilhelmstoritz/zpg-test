#include "SceneBuilder.h"
#include "Config.h"
#include "TransformationStepTranslate.h"
#include "TransformationStepRotate.h"
#include "TransformationStepScale.h"

#include "resModels.h"

#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

void SceneBuilder::createModels_01() {
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

void SceneBuilder::createModels_02() {
    /* 2nd task models */
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
