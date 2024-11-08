#pragma once

#include "Model.h"
#include "ShaderFactory.h"
#include "VAO.h"
#include "VBO.h"
#include "TransformationStepTranslate.h"
#include "TransformationStepRotate.h"
#include "TransformationStepScale.h"

// include GLM
#include <glm/glm.hpp>

// include the standard C++ headers
#include <memory>
#include <string>

class ModelFactory {
public:
    ModelFactory(ShaderFactory* t_shaderFactory);

    void addVBO(const std::string& t_name, std::unique_ptr<VBO> t_vbo);
    void addVAO(const std::string& t_name, std::unique_ptr<VAO> t_vao);
    void addModel(const std::string& t_name, std::unique_ptr<Model> t_model);

    VBO* getVBO(const std::string& t_name) const;
    VAO* getVAO(const std::string& t_name) const;
    Model* getModel(const std::string& t_name) const;

    VBO* createVBO(const std::string& t_name, const std::vector<float>& t_data);
    VAO* createVAO(const std::string& t_name, const VBO& t_VBO);
    VAO* createVertexResources(const std::string& t_name, const std::vector<float>& t_data);

    Model* createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const std::string& t_VAOName,
        GLint t_first, GLsizei t_count);
    Model* createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const std::string& t_VAOName,
        GLint t_first, GLsizei t_count,
        const glm::vec3& t_position,
        float t_angleX, float t_angleY, float t_angleZ,
        const glm::vec3& t_scale);
    Model* createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const std::vector<float>& dataVBO,
        GLint t_first, GLsizei t_count,
        const glm::vec3& t_position,
        float t_angleX, float t_angleY, float t_angleZ,
        const glm::vec3& t_scale);

private:
    ShaderFactory* m_shaderFactory;

    std::unordered_map<std::string, std::unique_ptr<VBO>> m_vbos; // also retention for lifetime management
    std::unordered_map<std::string, std::unique_ptr<VAO>> m_vaos;
    std::unordered_map<std::string, std::unique_ptr<Model>> m_models;
};
