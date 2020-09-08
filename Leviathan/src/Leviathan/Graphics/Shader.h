#pragma once
#include "Leviathan/Core.h"
#include "glm/glm.hpp"
#include <string>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

enum class ShaderType{
	VERTEX,
	GEOMETRY,
	FRAGMENT
};

class Shader {
public:
	inline GLuint getHandle() { return handle; }
	std::string GetInfoLog(GLuint handle, ShaderType type);
protected:
	GLuint handle;
};

class VertexShader : public Shader {
public:
	VertexShader(std::string folder_id, std::string file);
	~VertexShader();
private:
	bool rtg;
	friend class ShaderProgram;
};

class FragmentShader : public Shader {
	FragmentShader(std::string folder_id, std::string file);
	~FragmentShader();
private:
	bool rtg;
	friend class ShaderProgram;
};

class GeometryShader : public Shader {
	GeometryShader(std::string folder_id, std::string file);
	~GeometryShader();
private:
	bool rtg;
	friend class ShaderProgram;
};

class ShaderProgram {
public:
	ShaderProgram(VertexShader& v_shader, FragmentShader& f_shader);
	ShaderProgram(VertexShader& v_shader, GeometryShader& g_shader, FragmentShader& f_shader);
	~ShaderProgram();

	GLuint id;
	bool rtg;
	void bind();

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	void setUniform(const char* name, const glm::vec2& value);
	void setUniform(const char* name, const glm::vec3& value);
	void setUniform(const char* name, const glm::vec4& value);
	void setUniform(const char* name, const glm::mat4& value);

	static bool AddShader(std::string shader_id, std::string folder_id, std::string frag_file, std::string vert_file);
	static bool AddShader(std::string shader_id, std::string folder_id, std::string frag_file, std::string vert_file, std::string geo_file);
	static std::weak_ptr<ShaderProgram> GetShader(std::string id);
	static bool DeleteShader(std::string id);

private:
	std::string GetInfoLog();
	
};

