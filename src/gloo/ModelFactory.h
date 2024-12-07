#pragma once

#include "Model.h"
#include "VAO.h"
#include "VBO.h"

// include GLM
#include <glm/glm.hpp>

// include the standard C++ headers
#include <memory>
#include <string>

class ModelFactory {
public:
    // - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
    static const VAO::BufferInfo s_defaultBuffer;
    static const VAO::BufferInfo s_defaultPositionBuffer;
    static const VAO::BufferInfo s_defaultColorBuffer;
    static const VAO::BufferInfo s_defaultNormalBuffer;

    static const std::vector<VAO::BufferInfo> s_defaultBufferList;
    static const std::vector<VAO::BufferInfo> s_defaultPositionColorBufferList;
    static const std::vector<VAO::BufferInfo> s_defaultPositionNormalBufferList;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    ModelFactory() = default;
    ~ModelFactory() = default;

    std::unique_ptr<VBO> createVBO(const size_t t_size, const float* t_data);
    std::unique_ptr<VBO> createVBO(const std::vector<float>& t_data);
    std::unique_ptr<VAO> createVAO(const VBO& t_vbo, const std::vector<VAO::BufferInfo>& t_bufferInfoList);

    std::unique_ptr<Model> createModel(
		ShaderProgram* t_shaderProgram,
		VAO* t_vao,
        const GLint t_first, const GLsizei t_count,
        const glm::vec3& t_scale = glm::vec3(1.0f),
        const glm::vec3& t_rotation = glm::vec3(0.0f),
        const glm::vec3& t_position = glm::vec3(0.0f));
};
