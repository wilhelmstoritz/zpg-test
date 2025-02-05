#include "VBO.h"

// glm
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// --- public ------------------------------------------------------------------
VBO::VBO(const size_t t_size, const float* t_data) {
	glGenBuffers(1, &this->m_ID);
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, t_size, t_data, GL_STATIC_DRAW);
}

VBO::VBO(const std::vector<float>& t_data)
	: VBO(t_data.size() * sizeof(float), t_data.data()) { }

VBO::~VBO() {
	glDeleteBuffers(1, &this->m_ID);
}

void VBO::bind()   const { glBindBuffer(GL_ARRAY_BUFFER, this->m_ID); }
void VBO::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

// apply transformations to each vertex of the model directly to VBO memory
void VBO::transform(glm::mat4 t_vertexTransformation) {
	// get buffer size directly from VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
	int bufferSize = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

	// the number of vertices
	size_t vertexCount = bufferSize / (3 * sizeof(float)); // each vertex has 3 float values: position only

	// buffer mapping to memory
	float* bufferPtr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (bufferPtr) {
		for (size_t i = 0; i < vertexCount; ++i) {
			// load the original coordinates of the vertex directly from the VBO memory; apply the transformation
			glm::vec4 originalVertex(bufferPtr[i * 3], bufferPtr[i * 3 + 1], bufferPtr[i * 3 + 2], 1.f);
			glm::vec4 transformedVertex = t_vertexTransformation * originalVertex;

			// write the transformed vertex back to VBO memory; position
			bufferPtr[i * 3] = transformedVertex.x;
			bufferPtr[i * 3 + 1] = transformedVertex.y;
			bufferPtr[i * 3 + 2] = transformedVertex.z;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER); // unmap buffer after editing
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// apply transformations to each vertex of the model directly to VBO memory; with respect to normals
void VBO::transform(glm::mat4 t_vertexTransformation, glm::mat4 t_normalTransformation) {
	// get buffer size directly from VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
	int bufferSize = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

	// the number of vertices
	size_t vertexCount = bufferSize / (6 * sizeof(float)); // each vertex has 6 float values: position + normal

	// buffer mapping to memory
	float* bufferPtr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (bufferPtr) {
		for (size_t i = 0; i < vertexCount; ++i) {
			// load the original coordinates of the vertex directly from the VBO memory; apply the transformation
			glm::vec4 originalVertex(bufferPtr[i * 6], bufferPtr[i * 6 + 1], bufferPtr[i * 6 + 2], 1.f);
			glm::vec4 transformedVertex = t_vertexTransformation * originalVertex;

			// load the normal directly from the VBO memory; apply the transformation
			glm::vec4 originalNormal(bufferPtr[i * 6 + 3], bufferPtr[i * 6 + 4], bufferPtr[i * 6 + 5], 0.f);
			glm::vec4 transformedNormal = t_normalTransformation * originalNormal;

			// write the transformed vertex back to VBO memory; position and normal
			bufferPtr[i * 6] = transformedVertex.x;
			bufferPtr[i * 6 + 1] = transformedVertex.y;
			bufferPtr[i * 6 + 2] = transformedVertex.z;

			bufferPtr[i * 6 + 3] = transformedNormal.x;
			bufferPtr[i * 6 + 4] = transformedNormal.y;
			bufferPtr[i * 6 + 5] = transformedNormal.z;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER); // unmap buffer after editing
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// apply transformations to each vertex of the model directly to VBO memory; with respect to normals
void VBO::transform(float t_scale, float t_rotationXdegrees, float t_rotationYdegrees, float t_rotationZdegrees, glm::vec3 t_position,
	bool t_withNormals) {
	glm::mat4 vertexTransformation = glm::mat4(1.f);
	glm::mat4 normalTransformation = glm::mat4(1.f);

	// vertices transformation matrix
	vertexTransformation = glm::translate(vertexTransformation, t_position);
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(t_rotationXdegrees), glm::vec3(1.f, 0.f, 0.f)); // rotation around X-axis
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(t_rotationYdegrees), glm::vec3(0.f, 1.f, 0.f)); // rotation around Y-axis
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(t_rotationZdegrees), glm::vec3(0.f, 0.f, 1.f)); // rotation around Z-axis
	vertexTransformation = glm::scale(vertexTransformation, glm::vec3(t_scale));
	

	// to transform the normals we will only use scaling and rotation (no translation)
	normalTransformation = glm::rotate(normalTransformation, glm::radians(t_rotationXdegrees), glm::vec3(1.f, 0.f, 0.f)); // rotation around X-axis
	normalTransformation = glm::rotate(normalTransformation, glm::radians(t_rotationYdegrees), glm::vec3(0.f, 1.f, 0.f)); // rotation around Y-axis
	normalTransformation = glm::rotate(normalTransformation, glm::radians(t_rotationZdegrees), glm::vec3(0.f, 0.f, 1.f)); // rotation around Z-axis
	normalTransformation = glm::scale(normalTransformation, glm::vec3(t_scale));

	if (t_withNormals)
		this->transform(vertexTransformation, normalTransformation);
	else
		this->transform(vertexTransformation);
}
