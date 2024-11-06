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

    VAO* getVAO(const std::string& t_name) const;

    VAO* createVertexResources(const std::string& t_name, const std::vector<float>& dataVBO);

    std::unique_ptr<Model> createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const std::vector<float>& dataVBO,
        GLint t_first,
        GLsizei t_count,
        const glm::vec3& t_position,
        float t_angleX, float t_angleY, float t_angleZ,
        const glm::vec3& t_scale);

private:
    ShaderFactory* m_shaderFactory;

    std::unordered_map<std::string, std::unique_ptr<VBO>> m_vbos; // also retention for lifetime management
    std::unordered_map<std::string, std::unique_ptr<VAO>> m_vaos;
};
