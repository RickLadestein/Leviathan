#pragma once
#include "Leviathan/Data/Structures.h"
#include "glad/glad.h"
#include "Leviathan/Graphics/Mesh.h"
#include <vector>

namespace Leviathan::Graphics::Buffers {
	enum class VertexBufferLayout {
		PNT_SERIAL,
		PNT_INTERLEAVED,
	};

	

	class VertexBuffer {
	public:
		//Construct a normal vbo
		VertexBuffer(Mesh& mesh);
		//Just initialize the buffers
		VertexBuffer();

		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		void Bind();
		void Unbind();

		void SetPimitiveType(PrimitiveType type) { primitive_type = static_cast<GLenum>(type); }
		PrimitiveType GetPrimitiveType() { return static_cast<PrimitiveType>(primitive_type); }

		void BufferData(std::vector<Primitive>& primitives);
		void BufferData(Mesh& mesh);
		void BufferData(std::shared_ptr<Mesh> mesh);

		void DestroyBuffers();

		bool buffers_ready = false;
		bool instance_buffer = false;
		GLuint element_count;
	private:
		std::vector<Attribute> attribs;
		Handle vbo_handle;
		Handle vao_handle;
		GLenum primitive_type;
		size_t current_vao_attrib;

		size_t GetVertexCountFromPrimitive() {
			switch (this->GetPrimitiveType()) {
			case PrimitiveType::POINT:
				return 1;
			case PrimitiveType::LINE:
				return 2;
			case PrimitiveType::TRIANGLES:
				return 3;
			default:
				return 0;
			}
		}
	};
}