#pragma once
#include "Leviathan/Core.h"
#include "glm/glm.hpp"
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

enum class LEVIATHAN_API ShaderType{
	VERTEX,
	GEOMETRY,
	FRAGMENT
};

class LEVIATHAN_API Shader {
public:
	inline GLuint getHandle() { return handle; }
	std::string GetInfoLog(GLuint handle, ShaderType type);
protected:
	GLuint handle;
};

class LEVIATHAN_API VertexShader : public Shader {
public:
	VertexShader(std::string folder_id, std::string file);
	~VertexShader();
private:
	bool rtg;
	friend class ShaderProgram;
};

class LEVIATHAN_API FragmentShader : public Shader {
	FragmentShader(std::string folder_id, std::string file);
	~FragmentShader();
private:
	bool rtg;
	friend class ShaderProgram;
};

class LEVIATHAN_API GeometryShader : public Shader {
	GeometryShader(std::string folder_id, std::string file);
	~GeometryShader();
private:
	bool rtg;
	friend class ShaderProgram;
};

class LEVIATHAN_API ShaderProgram {
public:
	ShaderProgram(VertexShader& v_shader, FragmentShader& f_shader);
	ShaderProgram(VertexShader& v_shader, GeometryShader& g_shader, FragmentShader& f_shader);
	~ShaderProgram();

	GLuint id;
	void bind();

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	void setUniform(const char* name, const glm::vec2& value);
	void setUniform(const char* name, const glm::vec3& value);
	void setUniform(const char* name, const glm::vec4& value);
	void setUniform(const char* name, const glm::mat4& value);

private:
	std::string GetInfoLog();
};

