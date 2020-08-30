#include "VertexBuffer.h"
#include <iostream>
VertexBuffer::VertexBuffer(std::vector<Primitive>& primitives)
{
	this->vao = 0;
	this->element_count = 0;
	this->buffers_ready = false;
	this->current_vao_attrib = 0;
	this->BufferData(primitives);
}

VertexBuffer::VertexBuffer()
{
	this->vao = 0;
	this->element_count = 0;
	this->current_vao_attrib = 0;
	this->buffers_ready = false;
}

VertexBuffer::~VertexBuffer()
{
	this->DestroyBuffers();
}

void VertexBuffer::Bind()
{
	//glBindBuffer(GL_ARRAY_BUFFER, this->primitive_vbo);
	glBindVertexArray(this->vao);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexBuffer::BufferData(std::vector<Primitive>& primitives)
{
	this->DestroyBuffers();

	if (this->buffers.size() == 0) {
		//This buffer is the first buffer created
		glGenVertexArrays(1, &this->vao);
		this->element_count = primitives.size() * 3;
	}

	if (this->element_count == (primitives.size() * 3)) {
		Buffer primary = Buffer();
		primary.components = this->element_count;
		primary.size = primitives.size() * 3;

		glGenBuffers(1, &primary.vbo_id);
		glBindBuffer(GL_ARRAY_BUFFER, primary.vbo_id);
		glBufferData(GL_ARRAY_BUFFER, (primitives.size() * sizeof(Primitive)), primitives.data(), GL_STATIC_DRAW);
		this->buffers.push_back(primary);

		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);

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
	else {
		//Buffer does not match existing element size;
		std::cout << "Could not load int buffer: buffer did not match existing buffer element count" << std::endl;
		return;
	}
	
}

void VertexBuffer::BufferData(std::vector<GLint> data, size_t components)
{
	if (this->buffers.size() == 0) {
		//This buffer is the first buffer created
		glGenVertexArrays(1, &this->vao);
		this->element_count = data.size() / components;
	}

	if (this->element_count == (data.size() / components)) {
		Buffer primary = Buffer();
		primary.size = data.size();
		primary.components = components;

		glGenBuffers(1, &primary.vbo_id);
		glBindBuffer(GL_ARRAY_BUFFER, primary.vbo_id);
		glBufferData(GL_ARRAY_BUFFER, (data.size() * sizeof(int)), data.data(), GL_STATIC_DRAW);
		this->buffers.push_back(primary);

		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, primary.vbo_id);

		glVertexAttribPointer(this->current_vao_attrib, components, GL_INT, GL_FALSE, (components * sizeof(GLint)), 0);
		glEnableVertexAttribArray(this->current_vao_attrib);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		this->buffers_ready = true;
		this->current_vao_attrib += 1;
	}
	else {
		//Buffer does not match existing element size;
		std::cout << "Could not load int buffer: buffer did not match existing buffer element count" << std::endl;
		return;
	}
	
}

void VertexBuffer::BufferData(std::vector<GLfloat> data, size_t components)
{
	if (this->buffers.size() == 0) {
		//This buffer is the first buffer created
		glGenVertexArrays(1, &this->vao);
		this->element_count = data.size() / components;
	}

	if (this->element_count == (data.size() / components)) {
		Buffer primary = Buffer();
		primary.size = data.size();
		primary.components = components;

		glGenBuffers(1, &primary.vbo_id);
		glBindBuffer(GL_ARRAY_BUFFER, primary.vbo_id);
		glBufferData(GL_ARRAY_BUFFER, (data.size() * sizeof(int)), data.data(), GL_STATIC_DRAW);
		this->buffers.push_back(primary);

		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, primary.vbo_id);

		glVertexAttribPointer(this->current_vao_attrib, components, GL_FLOAT, GL_FALSE, (components * sizeof(GLfloat)), 0);
		glEnableVertexAttribArray(this->current_vao_attrib);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		this->buffers_ready = true;
		this->current_vao_attrib += 1;
	}
	else {
		//Buffer does not match existing element size;
		std::cout << "Could not load float buffer: buffer did not match existing buffer element count" << std::endl;
		return;
	}
}

void VertexBuffer::DestroyBuffers()
{
	this->Unbind(); //Unbind buffers just in case the buffer was bound
	for (size_t i = 0; i < buffers.size(); i++) {
		if (this->buffers[i].vbo_id != GLuint(0)) {
			glDeleteBuffers(1, &this->buffers[i].vbo_id);
		}
	}
	this->buffers.clear();

	if (this->vao) {
		glDeleteVertexArrays(1, &this->vao);
		this->vao = 0;
	}
	this->element_count = 0;
	this->current_vao_attrib = 0;
	this->buffers_ready = false;

}
