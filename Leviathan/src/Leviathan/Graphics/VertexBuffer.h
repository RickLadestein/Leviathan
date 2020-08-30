#pragma once
#include "Leviathan/Core.h"
#include "Leviathan/Data/Structures.h"
#include <cstdarg>
#include <vector>
#include "glad/glad.h"

struct LEVIATHAN_API Buffer {
	GLuint vbo_id = 0;
	GLuint size = 0;
	GLuint components = 0;
};

enum class LEVIATHAN_API VertexBufferLayout {
	PNT_SERIAL,
	PNT_INTERLEAVED,

};



class LEVIATHAN_API VertexBuffer {
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
	
	void DestroyBuffers();

	bool buffers_ready = false;
	bool instance_buffer = false;
	GLuint element_count;
private:
	

	//TODO change to custom list
	std::vector<Buffer> buffers;
	
	size_t current_vao_attrib;
	GLuint vao;
};