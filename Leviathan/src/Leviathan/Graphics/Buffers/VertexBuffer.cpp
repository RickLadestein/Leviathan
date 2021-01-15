#include "VertexBuffer.h"
#include <iostream>

#define HANDLE_DEFAULT_VALUE 0

namespace Leviathan::Graphics::Buffers {
	VertexBuffer* bound_vao;

	VertexBuffer::VertexBuffer(Mesh& mesh)
	{
		this->vao_handle = 0;
		this->vbo_handle = 0;
		this->element_count = 0;
		this->current_vao_attrib = 0;
		this->buffers_ready = false;
		this->SetPimitiveType(mesh.primitive_type);
		this->BufferData(mesh);
	}

	VertexBuffer::VertexBuffer()
	{
		this->vao_handle = 0;
		this->vbo_handle = 0;
		this->element_count = 0;
		this->current_vao_attrib = 0;
		this->buffers_ready = false;
		this->SetPimitiveType(PrimitiveType::TRIANGLES);
	}

	VertexBuffer::~VertexBuffer()
	{
		this->DestroyBuffers();
	}

	void VertexBuffer::Bind()
	{
		if (bound_vao == nullptr) {
			glBindVertexArray(this->vao_handle);
			bound_vao = this;
		}
		else {
			std::cout << "Could not bind VertexBuffer: another VertexBuffer was still bound" << std::endl;
		}
	}

	void VertexBuffer::Unbind()
	{
		if (bound_vao == this) {
			glBindVertexArray(0);
			bound_vao = nullptr;
		}
		else {
			std::cout << "Could not unbind VertexBuffer: currently bound buffer is not the same as calling buffer" << std::endl;
		}
	}

	void VertexBuffer::BufferData(std::vector<Primitive>& primitives)
	{
		if (this->vao_handle != HANDLE_DEFAULT_VALUE || this->vbo_handle != HANDLE_DEFAULT_VALUE) {
			this->DestroyBuffers();
		}
		this->element_count = primitives.size() * GetVertexCountFromPrimitive();
		glGenBuffers(1, &this->vbo_handle);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_handle);
		glBufferData(GL_ARRAY_BUFFER, (primitives.size() * sizeof(Primitive)), primitives.data(), GL_STATIC_DRAW);

		glGenVertexArrays(1, &this->vao_handle);
		glBindVertexArray(this->vao_handle);

		//Position data
		glVertexAttribPointer(this->current_vao_attrib, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(GLfloat)), 0);
		glEnableVertexAttribArray(this->current_vao_attrib);
		this->current_vao_attrib += 1;
		//Normal data
		glVertexAttribPointer(this->current_vao_attrib, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(GLfloat)), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(this->current_vao_attrib);
		this->current_vao_attrib += 1;

		//Texture data
		glVertexAttribPointer(this->current_vao_attrib, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(GLfloat)), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(this->current_vao_attrib);
		this->current_vao_attrib += 1;

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		this->buffers_ready = true;
		this->instance_buffer = false;

	}

	void VertexBuffer::BufferData(Mesh& mesh) {
		if (this->vao_handle != HANDLE_DEFAULT_VALUE || this->vbo_handle != HANDLE_DEFAULT_VALUE) {
			this->DestroyBuffers();
		}
		std::vector<byte>* byte_vector = &mesh.primitive_data;
		this->element_count = mesh.primitive_count * GetVertexCountFromPrimitive();
		glGenBuffers(1, &this->vbo_handle);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_handle);
		glBufferData(GL_ARRAY_BUFFER, byte_vector->size(), byte_vector->data(), GL_STATIC_DRAW);

		glGenVertexArrays(1, &this->vao_handle);
		glBindVertexArray(this->vao_handle);

		//Position data
		glVertexAttribPointer(this->current_vao_attrib, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(GLfloat)), 0);
		glEnableVertexAttribArray(this->current_vao_attrib);
		this->current_vao_attrib += 1;
		//Normal data
		glVertexAttribPointer(this->current_vao_attrib, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(GLfloat)), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(this->current_vao_attrib);
		this->current_vao_attrib += 1;

		//Texture data
		glVertexAttribPointer(this->current_vao_attrib, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(GLfloat)), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(this->current_vao_attrib);
		this->current_vao_attrib += 1;

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		this->buffers_ready = true;
		this->instance_buffer = false;
	}

	void VertexBuffer::BufferData(std::shared_ptr<Mesh> mesh) {
		if (this->vao_handle != HANDLE_DEFAULT_VALUE || this->vbo_handle != HANDLE_DEFAULT_VALUE) {
			this->DestroyBuffers();
		}
		std::vector<byte>* byte_vector = &mesh->primitive_data;
		this->element_count = mesh->primitive_count * GetVertexCountFromPrimitive();
		glGenBuffers(1, &this->vbo_handle);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_handle);
		glBufferData(GL_ARRAY_BUFFER, byte_vector->size(), byte_vector->data(), GL_STATIC_DRAW);

		glGenVertexArrays(1, &this->vao_handle);
		glBindVertexArray(this->vao_handle);

		//Position data
		glVertexAttribPointer(this->current_vao_attrib, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(GLfloat)), 0);
		glEnableVertexAttribArray(this->current_vao_attrib);
		this->current_vao_attrib += 1;
		//Normal data
		glVertexAttribPointer(this->current_vao_attrib, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(GLfloat)), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(this->current_vao_attrib);
		this->current_vao_attrib += 1;

		//Texture data
		glVertexAttribPointer(this->current_vao_attrib, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(GLfloat)), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(this->current_vao_attrib);
		this->current_vao_attrib += 1;

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		this->buffers_ready = true;
		this->instance_buffer = false;
	}

	void VertexBuffer::DestroyBuffers()
	{
		this->Unbind(); //Unbind buffers just in case the buffer was bound
		if (this->vbo_handle != HANDLE_DEFAULT_VALUE) {
			glDeleteBuffers(1, &this->vbo_handle);
			this->vbo_handle = HANDLE_DEFAULT_VALUE;
		}
		if(this->vao_handle != HANDLE_DEFAULT_VALUE){
			glDeleteVertexArrays(1, &this->vao_handle);
			this->vao_handle = HANDLE_DEFAULT_VALUE;
		}

		this->element_count = 0;
		this->current_vao_attrib = 0;
		this->buffers_ready = false;

	}
}

