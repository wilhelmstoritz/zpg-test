#include "ZPGVBO.h"

// include GLM
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// --- public ------------------------------------------------------------------
ZPGVBO::ZPGVBO(const size_t t_size, const float* t_data) {
	glGenBuffers(1, &this->m_VBOID);
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, t_size, t_data, GL_STATIC_DRAW);
}

ZPGVBO::ZPGVBO(const std::vector<float>& t_data)
	: ZPGVBO(t_data.size() * sizeof(float), t_data.data()) { }

ZPGVBO::~ZPGVBO() {
	glDeleteBuffers(1, &this->m_VBOID);
}
void ZPGVBO::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOID);
}

void ZPGVBO::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// apply transformations to each vertex of the model directly to VBO memory; with respect to normals
void ZPGVBO::transform(glm::vec3 t_position, float t_scale, float t_rotationAngle, bool t_withNormals) {
	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 normalTransform = glm::mat4(1.0f);

	// apply transformation
	transform = glm::translate(transform, t_position);
	transform = glm::rotate(transform, glm::radians(t_rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(t_scale));

	// to transform the normals we will only use rotation and scaling (no translation)
	normalTransform = glm::rotate(normalTransform, glm::radians(t_rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	normalTransform = glm::scale(normalTransform, glm::vec3(t_scale));

	// get buffer size directly from VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOID);
	int bufferSize = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

	// the number of vertices
	size_t vertexCount = bufferSize / (3 * sizeof(float)); // each vertex has 3 float values: position only
	if (t_withNormals)
		vertexCount = bufferSize / (6 * sizeof(float)); // each vertex has 6 float values: position + normal

	// buffer mapping to memory
	float* bufferPtr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (bufferPtr) {
		for (size_t i = 0; i < vertexCount; ++i) {
			if (t_withNormals) {
				// load the original coordinates of the vertex directly from the VBO memory; apply the transformation
				glm::vec4 originalVertex(bufferPtr[i * 6], bufferPtr[i * 6 + 1], bufferPtr[i * 6 + 2], 1.0f);
				glm::vec4 transformedVertex = transform * originalVertex;

				// load the normal directly from the VBO memory; apply the transformation
				glm::vec4 originalNormal(bufferPtr[i * 6 + 3], bufferPtr[i * 6 + 4], bufferPtr[i * 6 + 5], 0.0f);
				glm::vec4 transformedNormal = normalTransform * originalNormal;

				// write the transformed vertex back to VBO memory; position and normal
				bufferPtr[i * 6] = transformedVertex.x;
				bufferPtr[i * 6 + 1] = transformedVertex.y;
				bufferPtr[i * 6 + 2] = transformedVertex.z;

				bufferPtr[i * 6 + 3] = transformedNormal.x;
				bufferPtr[i * 6 + 4] = transformedNormal.y;
				bufferPtr[i * 6 + 5] = transformedNormal.z;
			} else {
				// load the original coordinates of the vertex directly from the VBO memory; apply the transformation
				glm::vec4 originalVertex(bufferPtr[i * 3], bufferPtr[i * 3 + 1], bufferPtr[i * 3 + 2], 1.0f);
				glm::vec4 transformedVertex = transform * originalVertex;

				// write the transformed vertex back to VBO memory; position
				bufferPtr[i * 3] = transformedVertex.x;
				bufferPtr[i * 3 + 1] = transformedVertex.y;
				bufferPtr[i * 3 + 2] = transformedVertex.z;
			}
		}
		glUnmapBuffer(GL_ARRAY_BUFFER); // unmap buffer after editing
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
