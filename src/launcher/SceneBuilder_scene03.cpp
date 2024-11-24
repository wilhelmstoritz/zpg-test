#include "SceneBuilder.h"

#include "ModelLibrary.h"
#include "modelLetters.h"

#include "sphere.h"

void SceneBuilder::createScene_03_illuminatedSpheres() {
    // skybox
    this->m_modelFactory->createModel(
        "skybox",
        //"shaderLambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        "shaderPhong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::s_defaultPositionNormalBufferList, 0, 36,
        this->m_dimensions, glm::vec3(0.f), -this->m_dimensions / glm::vec3(2.f));

    // spheres
    this->m_modelFactory->createVertexResources("sphere", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList);

    this->m_modelFactory->createModel("sphere01", "shaderLambertian", "sphere", 0, 17280, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(2.f, 0.f, 0.f));
    this->m_modelFactory->createModel("sphere02", "shaderLambertian", "sphere", 0, 17280, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(0.f, 2.f, 0.f));
    this->m_modelFactory->createModel("sphere03", "shaderPhong", "sphere", 0, 17280, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-2.f, 0.f, 0.f));
    this->m_modelFactory->createModel("sphere04", "shaderPhong", "sphere", 0, 17280, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(0.f, -2.f, 0.f));

    // letters
    this->m_modelFactory->createVertexResources("letter_L", ModelLetters::getLetter(ModelLetters::LETTER_L), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_P", ModelLetters::getLetter(ModelLetters::LETTER_P), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_a", ModelLetters::getLetter(ModelLetters::LETTER_a), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_b", ModelLetters::getLetter(ModelLetters::LETTER_b), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_e", ModelLetters::getLetter(ModelLetters::LETTER_e), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_h", ModelLetters::getLetter(ModelLetters::LETTER_h), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_i", ModelLetters::getLetter(ModelLetters::LETTER_i), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_o", ModelLetters::getLetter(ModelLetters::LETTER_o), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_m", ModelLetters::getLetter(ModelLetters::LETTER_m), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_n", ModelLetters::getLetter(ModelLetters::LETTER_n), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_g", ModelLetters::getLetter(ModelLetters::LETTER_g), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_r", ModelLetters::getLetter(ModelLetters::LETTER_r), ModelFactory::s_defaultPositionNormalBufferList);
    this->m_modelFactory->createVertexResources("letter_t", ModelLetters::getLetter(ModelLetters::LETTER_t), ModelFactory::s_defaultPositionNormalBufferList);

    float size = 0.1f;
    float offsetX = 13.f;
    float offsetY = 13.f;
    this->m_modelFactory->createModel("letter_L01", "shaderLambertian", "letter_L", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_L), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_a01", "shaderLambertian", "letter_a", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_a), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1)), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_m01", "shaderLambertian", "letter_m", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_m), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 2), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_b01", "shaderLambertian", "letter_b", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_b), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 3), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_e01", "shaderLambertian", "letter_e", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_e), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 4), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_r01", "shaderLambertian", "letter_r", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_r), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 5), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_t01", "shaderLambertian", "letter_t", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_t), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 6), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_i01", "shaderLambertian", "letter_i", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_i), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 7), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_a02", "shaderLambertian", "letter_a", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_a), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 8), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_n01", "shaderLambertian", "letter_n", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_n), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 9), size * offsetY, 0.f));

    offsetX = -43.f;
    offsetY = -19.f;
    this->m_modelFactory->createModel("letter_P11", "shaderPhong", "letter_P", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_h11", "shaderPhong", "letter_h", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1)), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_o11", "shaderPhong", "letter_o", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 2), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_n11", "shaderPhong", "letter_n", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 3), size * offsetY, 0.f));
    this->m_modelFactory->createModel("letter_g11", "shaderPhong", "letter_g", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 4), size * offsetY, 0.f));

    // light sources
    Light* light = new Light("light01default", 1, glm::vec3(0.f, 0.f, 0.f));
    light->setDiffuseColor(glm::vec3(0.f, 0.f, 1.0f));
    light->setSpecularColor(glm::vec3(1.f, 0.f, 0.0f));
    this->m_scene->addLight(light);

    //this->m_scene->addLight(new Light("light02", 1, glm::vec3(-10.f, 10.f, 10.f)));

    // camera position; corresponding to the scene
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 0.f, 11.f),
        glm::vec3(0.f, 0.f, -1.f));
}
