#pragma once
#include "Leviathan/Data/Structures.h"
#include "glad/glad.h"

#include <vector>

namespace Leviathan::Graphics::Buffers {
	struct Buffer {
		GLuint vbo_id = 0;
		GLuint size = 0;
		GLuint components = 0;
	};

	enum class VertexBufferLayout {
		PNT_SERIAL,
		PNT_INTERLEAVED,
	};



	class VertexBuffer {
	public:
		//Construct a normal vbo
		VertexBuffer(std::vector<Primitive>& primitives);

		//Just initialize the buffers
		VertexBuffer();

		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		void Bind();
		void Unbind();

		void BufferData(std::vector<Primitive>& primitives);
		void BufferData(std::vector<GLint> data, size_t components = 1);
		void BufferData(std::vector<GLfloat> data, size_t components = 1);

		void BufferData(std::vector<glm::vec2> data);
		void BufferData(std::vector<glm::vec3> data);
		void BufferData(std::vector<glm::vec4> data);

		void DestroyBuffers();

		bool buffers_ready = false;
		bool instance_buffer = false;
		GLuint element_count;
	private:
		void BufferGeneralData(void* data, size_t buffer_size, size_t type_size, size_t components);

		//TODO change to custom list
		std::vector<Buffer> buffers;

		size_t current_vao_attrib;
		GLuint vao;
	};
}