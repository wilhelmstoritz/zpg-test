#include "ShaderFactory.h"
#include "data.h"

// --- public ------------------------------------------------------------------
void ShaderFactory::addShader(const std::string& t_name, std::unique_ptr<Shader> t_shader) {
    this->m_shaders[t_name] = std::move(t_shader);
}

void ShaderFactory::addShaderProgram(const std::string& t_name, std::unique_ptr<ShaderProgram> t_program) {
    this->m_shaderPrograms[t_name] = std::move(t_program);
}

Shader* ShaderFactory::getShader(const std::string& t_name) const {
    auto it = this->m_shaders.find(t_name);
    return (it != this->m_shaders.end()) ? it->second.get() : nullptr;
}

ShaderProgram* ShaderFactory::getShaderProgram(const std::string& t_name) const {
    auto it = this->m_shaderPrograms.find(t_name);
    return (it != this->m_shaderPrograms.end()) ? it->second.get() : nullptr;
}

// === factory =================================================================
void ShaderFactory::createDefaultShaders() {
    // vertex & fragment shaders
    addShader("v_default", std::make_unique<VertexShader>(DEFAULT_VERTEX_SHADER));
    addShader("f_default", std::make_unique<FragmentShader>(DEFAULT_FRAGMENT_SHADER));

    addShader("v_defaultColorFromPosition", std::make_unique<VertexShader>(DEFAULT_VERTEX_SHADER_COLORFROMPOSITION));
    addShader("f_defaultColorFromPosition", std::make_unique<FragmentShader>(DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION));

    addShader("v_defaultColorData", std::make_unique<VertexShader>(DEFAULT_VERTEX_SHADER_COLORDATA));
    addShader("f_defaultColorData", std::make_unique<FragmentShader>(DEFAULT_FRAGMENT_SHADER_COLORDATA));

    addShader("f_yellow", std::make_unique<FragmentShader>(YELLOW_FRAGMENT_SHADER));

    // shader programs
    auto defaultProgram = std::make_unique<ShaderProgram>(*getShader("v_default"), *getShader("f_default"));
    addShaderProgram("default", std::move(defaultProgram));

    defaultProgram = std::make_unique<ShaderProgram>(*getShader("v_defaultColorFromPosition"), *getShader("f_defaultColorFromPosition"));
    addShaderProgram("defaultColorFromPosition", std::move(defaultProgram));

    defaultProgram = std::make_unique<ShaderProgram>(*getShader("v_defaultColorData"), *getShader("f_defaultColorData"));
    addShaderProgram("defaultColorData", std::move(defaultProgram));

    defaultProgram = std::make_unique<ShaderProgram>(*getShader("v_default"), *getShader("f_yellow"));
    addShaderProgram("yellow", std::move(defaultProgram));
}

void ShaderFactory::createTransformingShaders() {
    // vertex & fragment shaders
    addShader("v_transformingColorData", std::make_unique<VertexShader>(TRANSFORMING_VERTEX_SHADER_COLORDATA));
    addShader("f_transformingColorData", std::make_unique<FragmentShader>(TRANSFORMING_FRAGMENT_SHADER_COLORDATA));

    // shader programs
    auto defaultProgram = std::make_unique<ShaderProgram>(*getShader("v_transformingColorData"), *getShader("f_transformingColorData"));
    addShaderProgram("transformingColorData", std::move(defaultProgram));
}
