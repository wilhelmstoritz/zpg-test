#pragma once

#include "VBO.h"
#include "VAO.h"
#include "IBO.h"
#include "Model.h"

// glm
#include <glm/glm.hpp>

// standard c++ libraries
#include <memory>
#include <string>

class ModelFactory {
public:
    // - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
    static const VAO::bufferInfoT BUFFERINFO3_POSITION;

    static const VAO::bufferInfoT BUFFERINFO6_POSITION;
    static const VAO::bufferInfoT BUFFERINFO6_COLOR;
    static const VAO::bufferInfoT BUFFERINFO6_NORMAL;

    static const VAO::bufferInfoT BUFFERINFO8_POSITION;
    static const VAO::bufferInfoT BUFFERINFO8_NORMAL;
    static const VAO::bufferInfoT BUFFERINFO8_TEXTUREUV;

    static const std::vector<VAO::bufferInfoT> BUFFERINFOLIST_POSITION;
    static const std::vector<VAO::bufferInfoT> BUFFERINFOLIST_POSITION_COLOR;
    static const std::vector<VAO::bufferInfoT> BUFFERINFOLIST_POSITION_NORMAL;
    static const std::vector<VAO::bufferInfoT> BUFFERINFOLIST_POSITION_NORMAL_TEXTURE;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    ModelFactory() = default;
    ~ModelFactory() = default;

    std::unique_ptr<VBO> createVBO(const size_t t_size, const float* t_data);
    std::unique_ptr<VBO> createVBO(const std::vector<float>& t_data);
    std::unique_ptr<VAO> createVAO(const VBO& t_vbo, const std::vector<VAO::bufferInfoT>& t_bufferInfoList);
    std::unique_ptr<IBO> createIBO(const size_t t_size, const unsigned int* t_data);
    std::unique_ptr<IBO> createIBO(const std::vector<unsigned int>& t_data);

    template <typename T = Model, typename = typename std::enable_if<std::is_base_of<Model, T>::value>::type>
    std::unique_ptr<T> createModel(
        const std::string& t_name,
		ShaderProgram* t_shaderProgram,
		VAO* t_vao, IBO* t_ibo,
        const GLint t_first, const GLsizei t_count,
        const glm::vec3& t_scale = glm::vec3(1.0f),
        const glm::vec3& t_rotation = glm::vec3(0.0f),
        const glm::vec3& t_position = glm::vec3(0.0f));
    template <typename T = Model, typename = typename std::enable_if<std::is_base_of<Model, T>::value>::type>
    std::unique_ptr<T> createModel(
        const std::string& t_name,
        ShaderProgram* t_shaderProgram,
        VAO* t_vao,
        const GLint t_first, const GLsizei t_count,
        const glm::vec3& t_scale = glm::vec3(1.0f),
        const glm::vec3& t_rotation = glm::vec3(0.0f),
        const glm::vec3& t_position = glm::vec3(0.0f));
};

// === templates implementation ================================================
#include "ModelFactory.tpp"
