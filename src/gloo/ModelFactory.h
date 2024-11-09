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
    static const VAO::BufferInfo s_defaultBuffer;
    static const VAO::BufferInfo s_defaultPositionBuffer;
    static const VAO::BufferInfo s_defaultColorBuffer;
    static const VAO::BufferInfo s_defaultNormalBuffer;

    static const std::vector<VAO::BufferInfo> s_defaultBufferList;
    static const std::vector<VAO::BufferInfo> s_defaultPositionColorBufferList;
    static const std::vector<VAO::BufferInfo> s_defaultPositionNormalBufferList;

    ModelFactory(ShaderFactory* t_shaderFactory);
    //~ModelFactory() = default;

    void clearAll();

    /* will become private after the end of development/debugging */
    void addVBO(const std::string& t_name, std::unique_ptr<VBO> t_vbo);
    void addVAO(const std::string& t_name, std::unique_ptr<VAO> t_vao);
    void addModel(const std::string& t_name, std::unique_ptr<Model> t_model);
    /* will become private after the end of development/debugging */

    VBO* getVBO(const std::string& t_name) const;
    VAO* getVAO(const std::string& t_name) const;
    Model* getModel(const std::string& t_name) const;
    const std::unordered_map<std::string, std::unique_ptr<Model>>* getModels() const;
    //const std::unordered_map<std::string, Model*> getModels() const;
    //const std::vector<Model*> getModels() const;

    VBO* createVBO(const std::string& t_name, const size_t t_size, const float* t_data);
    VBO* createVBO(const std::string& t_name, const std::vector<float>& t_data);
    VAO* createVAO(const std::string& t_name, const VBO& t_vbo, const std::vector<VAO::BufferInfo>& t_bufferInfoList);
    VAO* createVAO(const std::string& t_name, const std::string& t_vboName, const std::vector<VAO::BufferInfo>& t_bufferInfoList);
    VAO* createVertexResources(const std::string& t_name, const size_t t_size, const float* t_data, const std::vector<VAO::BufferInfo>& t_bufferInfoList);
    VAO* createVertexResources(const std::string& t_name, const std::vector<float>& t_data, const std::vector<VAO::BufferInfo>& t_bufferInfoList);

    /*
    Model* createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const std::string& t_vaoName,
        GLint t_first, GLsizei t_count);
    Model* createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const size_t t_vboSize, const float* t_vboData, const std::vector<VAO::BufferInfo>& t_bufferInfoList,
        GLint t_first, GLsizei t_count);
    Model* createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const std::vector<float>& t_vboData, const std::vector<VAO::BufferInfo>& t_bufferInfoList,
        GLint t_first, GLsizei t_count);
    */
    Model* createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const std::string& t_vaoName,
        GLint t_first, GLsizei t_count,
        const glm::vec3& t_scale = glm::vec3(1.0f),
        const glm::vec3& t_rotation = glm::vec3(0.0f),
        const glm::vec3& t_position = glm::vec3(0.0f));
    Model* createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const size_t t_vboSize, const float* t_vboData, const std::vector<VAO::BufferInfo>& t_bufferInfoList,
        GLint t_first, GLsizei t_count,
        const glm::vec3& t_scale = glm::vec3(1.0f),
        const glm::vec3& t_rotation = glm::vec3(0.0f),
        const glm::vec3& t_position = glm::vec3(0.0f));
    Model* createModel(
        const std::string& t_name,
        const std::string& t_shaderProgramName,
        const std::vector<float>& t_vboData, const std::vector<VAO::BufferInfo>& t_bufferInfoList,
        GLint t_first, GLsizei t_count,
        const glm::vec3& t_scale = glm::vec3(1.0f),
        const glm::vec3& t_rotation = glm::vec3(0.0f),
        const glm::vec3& t_position = glm::vec3(0.0f));

private:
    ShaderFactory* m_shaderFactory;

    std::unordered_map<std::string, std::unique_ptr<VBO>> m_vbos; // also retention for lifetime management
    std::unordered_map<std::string, std::unique_ptr<VAO>> m_vaos;
    std::unordered_map<std::string, std::unique_ptr<Model>> m_models;
};
