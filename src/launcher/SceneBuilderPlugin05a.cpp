#include "SceneBuilderPlugin05a.h"
#include "AppUtils.h"
#include "Config.h"
#include "Light.h"
#include "TransformationAnimationRotate.h"

#include "ModelLibrary.h"
#include "suzi_flat.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPlugin05a::setSceneProperties(Scene* t_scene) {
    t_scene->setTitle("6 | " + t_scene->getTitle());
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin05a::preProcess() {
    // scene size
    this->m_scene->setSize(
        Config::SKYBOX_MIN_VIRTUALWORLD,
        Config::SKYBOX_MAX);

    this->setEnvironment();
}

void SceneBuilderPlugin05a::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("05:a:shader:texture",         (this->m_shaderResourcesPath + "05/texture.vert.glsl"                ).c_str(), (this->m_shaderResourcesPath + "05/texture.frag.glsl"        ).c_str());
    this->m_shaderWarehouse->createShaderProgram("05:a:shader:texture_cubemap", (this->m_shaderResourcesPath + "05/texture-cubemap.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/texture-cubemap.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("05:a:shader:texture_xtra",    (this->m_shaderResourcesPath + "05/xtra-workaround-terrain.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/texture.frag.glsl"        ).c_str());

    this->m_shaderWarehouse->createShaderProgram("05:a:shader:phong",           (this->m_shaderResourcesPath + "05/normals.vert.glsl"                ).c_str(), (this->m_shaderResourcesPath + "05/phong.frag.glsl"          ).c_str());
    this->m_shaderWarehouse->createShaderProgram("05:a:shader:phong_texture",   (this->m_shaderResourcesPath + "05/normals-texture.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/phong-texture.frag.glsl"  ).c_str());
}

void SceneBuilderPlugin05a::createLights() {
	// daylight
    Light* light = this->m_lightWarehouse->createLight("05:a:daylight", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f, 99.f, 0.f));
    //light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(glm::vec3(1.f, .98f, .765f)); // warm white; daylight sunshine
    light->setSpecularColor(glm::vec3(1.f, 1.f, .9f));
    light->setAttenuation(glm::vec3(.1f, .001f, .0001f));
}

void SceneBuilderPlugin05a::createModels() {
    Model* model;
    std::vector<GLsizei> numVerticesList;

    // skybox
    this->m_modelWarehouse->createModel(
        "05:a:skybox",
        "05:a:shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(this->m_size.x, this->m_size.y, this->m_size.z),
        glm::vec3(0.f),
        glm::vec3(this->m_min.x, this->m_min.y, this->m_min.z));

    // skycube
    this->m_modelWarehouse->createVertexResources("res:skycube", ModelLibrary::MODEL_SKYCUBE, ModelFactory::BUFFERINFOLIST_POSITION);
    //numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:skycube", (this->m_modelResourcesPath + "skybox.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "05:a:skycube",
        "05:a:shader:texture_cubemap",
		// --- library model ---
        "res:skycube", 0, 36,
        glm::vec3(20.f),
		// --- obj model -------
        //"resobj:skycube0", // vao
		//"resobj:skycube0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        //0, numVerticesList[0],
        //glm::vec3(40.f),
		// ---------------------
        glm::vec3(0.f),
        glm::vec3(this->m_center.x - 30.f, this->m_center.y, this->m_center.z));
	model->setTextureID(10); // texture unit 10; skycube (cubemap texture)

    // skydome
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:skydome", (this->m_modelResourcesPath + "skydome.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "05:a:skydome",
        "05:a:shader:texture",
        "resobj:skydome0", // vao
        //"resobj:skydome0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(3.f),
        glm::vec3(0.f),
        glm::vec3(this->m_center.x + 30.f, this->m_center.y, this->m_center.z));
    model->setTextureID(11); // texture unit 11; skydome
    model->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, 1.f / 60.f, 0.f))); // 1 min for a full rotation

    //this->m_modelWarehouse->createVertexResources("res:surface_texture", ModelLibrary::MODEL_SURFACE_TEXTURE, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL_TEXTURE);
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:terrain", (this->m_modelResourcesPath + "teren.obj").c_str());
    //numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:terrain", (this->m_modelResourcesPath + "teren.triangulated.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "05:a:terrain",
        //"05:a:shader:phong_texture",
        // --- library model ---
        //"05:a:shader:texture",
        //"res:surface_texture", 0, 6,
        //glm::vec3(20.f),
        //glm::vec3(-90.f, 0.f, 0.f),
        // --- obj model -------
        "05:a:shader:texture_xtra",
        "resobj:terrain0", // vao
        "resobj:terrain0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(0.3f),
        glm::vec3(0.f),
        // ---------------------
        glm::vec3(this->m_center.x + 30.f, this->m_center.y - 20.f, this->m_center.z));
    //model->setTextureID(0);  // texture unit 0; grass
    model->setTextureID(12); // texture unit 12; ground

    // cubes
    this->m_modelWarehouse->createVertexResources("res:cube_texture", ModelLibrary::MODEL_CUBE_TEXTURE, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL_TEXTURE);

    model = this->m_modelWarehouse->createModel(
        "05:a:cube01",
        //"05:a:shader:phong_texture", "res:cube_texture", 0, 36,
        "05:a:shader:texture", "res:cube_texture", 0, 36,
        glm::vec3(3.f),
        glm::vec3(0.f),
        glm::vec3(this->m_center.x - 30.f - 1.5f, this->m_center.y - 1.5f, this->m_center.z - 1.5f));
    model->setTextureID(1); // texture unit 1; wood

    model = this->m_modelWarehouse->createModel(
        "05:a:cube02",
        //"05:a:shader:phong_texture", "res:cube_texture", 0, 36,
        "05:a:shader:texture", "res:cube_texture", 0, 36,
        glm::vec3(3.f),
        glm::vec3(0.f),
        glm::vec3(this->m_center.x + 30.f - 1.5f, this->m_center.y - 1.5f, this->m_center.z - 1.5f));
    model->setTextureID(1); // texture unit 1; wood

    // suzi
    model = this->m_modelWarehouse->createModel(
        "05:a:suzi01",
        "05:a:shader:phong", sizeof(suziFlat), suziFlat, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f),
        glm::vec3(0.f),
        glm::vec3(this->m_center.x - 30.f, 3.f, this->m_center.z));
    model->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation

    model = this->m_modelWarehouse->createModel(
        "05:a:suzi02",
        "05:a:shader:phong", sizeof(suziFlat), suziFlat, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f),
        glm::vec3(0.f),
        glm::vec3(this->m_center.x + 30.f, 3.f, this->m_center.z));
    model->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation*/
}

void SceneBuilderPlugin05a::loadTextures() {
    //this->m_textureWarehouse->loadTexture("tex:grass", (this->m_textureResourcesPath + "grass.png").c_str(), GL_TEXTURE0);
    this->m_textureWarehouse->loadTexture("tex:wood",  (this->m_textureResourcesPath + "test.png" ).c_str(), GL_TEXTURE1);

	this->m_textureWarehouse->loadTexture("tex:skycube", // cubemap texture
        (this->m_textureResourcesPath + "cubemap/posx.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/negx.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/posy.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/negy.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/posz.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/negz.jpg").c_str(),
        GL_TEXTURE10);
    this->m_textureWarehouse->loadTexture("tex:skydome", (this->m_textureResourcesPath + "skydome.png"     ).c_str(), GL_TEXTURE11);
    this->m_textureWarehouse->loadTexture("tex:ground",  (this->m_textureResourcesPath + "cubemap/negy.jpg").c_str(), GL_TEXTURE12);
}

void SceneBuilderPlugin05a::postProcess() {
    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(this->m_center.x, this->m_center.y, this->m_max.z - 1.f),
        glm::vec3(0.f, 0.f, -1.f));
}

void SceneBuilderPlugin05a::addContextToScene() {
    // add lights to the scene
    this->m_scene->addLight("daylight", this->m_lightWarehouse->getLight("05:a:daylight"));

    // add models and lights to the scene
	this->m_scene->addModel("skybox",  this->m_modelWarehouse->getModel("05:a:skybox"));

    this->m_scene->addModel("skycube", this->m_modelWarehouse->getModel("05:a:skycube"));
    this->m_scene->addModel("skydome", this->m_modelWarehouse->getModel("05:a:skydome"));
    this->m_scene->addModel("terrain", this->m_modelWarehouse->getModel("05:a:terrain"));

    this->m_scene->addModel("cube01",  this->m_modelWarehouse->getModel("05:a:cube01"));
    this->m_scene->addModel("cube02",  this->m_modelWarehouse->getModel("05:a:cube02"));
    this->m_scene->addModel("suzi01",  this->m_modelWarehouse->getModel("05:a:suzi01"));
    this->m_scene->addModel("suzi02",  this->m_modelWarehouse->getModel("05:a:suzi02"));
}
