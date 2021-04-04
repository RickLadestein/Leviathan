#include "Shader.h"
#include "Leviathan/Util/FileManager.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <sstream>

#include <unordered_map>
#include "Leviathan/Data/Dictionary.h"

#define GL_UNIFORM_NOT_FOUND -1

namespace Leviathan::Graphics {
	int current_bound_program = 0;
	ShaderProgram::ShaderProgram(VertexShader& v_shader, FragmentShader& f_shader)
	{
		this->id = 0;
		if (!v_shader.rtg || !f_shader.rtg) {
			this->rtg = false;
			return;
		}
		this->id = glCreateProgram();
		glAttachShader(this->id, v_shader.handle);
		glAttachShader(this->id, f_shader.handle);

		glLinkProgram(this->id);
		if (!this->GetInfoLog().empty()) {
			this->rtg = false;
			return;
		}
		this->rtg = true;
	}

	ShaderProgram::ShaderProgram(VertexShader& v_shader, GeometryShader& g_shader, FragmentShader& f_shader)
	{
		this->id = 0;
		if (!v_shader.rtg || !f_shader.rtg || !g_shader.rtg) {
			this->rtg = false;
			return;
		}
		this->id = glCreateProgram();
		glAttachShader(this->id, v_shader.handle);
		glAttachShader(this->id, f_shader.handle);
		glAttachShader(this->id, g_shader.handle);
		glLinkProgram(this->id);
		if (!this->GetInfoLog().empty()) {
			this->rtg = false;
			return;
		}
		this->rtg = true;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(this->id);
	}

	void ShaderProgram::bind()
	{
		if (current_bound_program != this->id && this->id != 0) {
			glUseProgram(this->id);
			current_bound_program = this->id;
		}
	}

	void ShaderProgram::unbind()
	{
		if (current_bound_program != this->id) {
			glUseProgram(0);
			current_bound_program = 0;
		}
	}

	void ShaderProgram::setUniform(const char* name, const int value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != -1) {
			glUniform1i(loc, value);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const unsigned int value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != -1) {
			glUniform1ui(loc, value);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const float value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != -1) {
			glUniform1f(loc, value);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}
	
	void ShaderProgram::setUniform(const char* name, const double value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != -1) {
			glUniform1d(loc, value);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::vec2& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != -1) {
			glUniform2f(loc, value.x, value.y);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::ivec2& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != -1) {
			glUniform2i(loc, value.x, value.y);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::dvec2& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != -1) {
			glUniform2d(loc, value.x, value.y);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::vec3& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != GL_UNIFORM_NOT_FOUND) {
			glUniform3f(loc, value.x, value.y, value.z);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::ivec3& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != GL_UNIFORM_NOT_FOUND) {
			glUniform3i(loc, value.x, value.y, value.z);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::dvec3& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != GL_UNIFORM_NOT_FOUND) {
			glUniform3d(loc, value.x, value.y, value.z);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::vec4& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != GL_UNIFORM_NOT_FOUND) {
			glUniform4f(loc, value.x, value.y, value.z, value.w);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::ivec4& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != GL_UNIFORM_NOT_FOUND) {
			glUniform4i(loc, value.x, value.y, value.z, value.w);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::dvec4& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != GL_UNIFORM_NOT_FOUND) {
			glUniform4d(loc, value.x, value.y, value.z, value.w);
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	void ShaderProgram::setUniform(const char* name, const glm::mat4& value)
	{
		GLint loc = glGetUniformLocation(this->id, name);
		if (loc != GL_UNIFORM_NOT_FOUND) {
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
		}
		else {
#ifdef LEVIATHAN_DEBUG_SHADER
			std::cout << "Uniform" << name << " does not exist" << std::endl;
#endif
		}
	}

	Leviathan::Dictionary<std::string, ShaderReference> programs;
	bool ShaderProgram::AddShader(std::string shader_id, std::string folder_id, std::string frag_file, std::string vert_file)
	{
		VertexShader v_shader(folder_id, vert_file);
		FragmentShader f_shader(folder_id, frag_file);
		
		ShaderReference shader;
		bool succes = programs.try_get_value(shader_id, shader);
		bool output = false;
		if (!succes) {
			std::shared_ptr<ShaderProgram> prg = std::make_shared<ShaderProgram>(v_shader, f_shader);
			if (prg->rtg) {
				programs[shader_id] = prg;
				output = true;
			}
		}
		return output;
	}

	bool ShaderProgram::AddShader(std::string shader_id, std::string folder_id, std::string frag_file, std::string vert_file, std::string geo_file)
	{
		VertexShader v_shader(folder_id, vert_file);
		FragmentShader f_shader(folder_id, frag_file);
		GeometryShader g_shader(folder_id, geo_file);

		ShaderReference shader;
		bool succes = programs.try_get_value(shader_id, shader);
		bool output = false;
		if (!succes) {
			std::shared_ptr<ShaderProgram> prg = std::make_shared<ShaderProgram>(v_shader, g_shader, f_shader);
			if (prg->rtg) {
				programs[shader_id] = prg;
				output = true;
			}
		}
		return output;
	}

	std::weak_ptr<ShaderProgram> ShaderProgram::GetShader(std::string id)
	{
		ShaderReference program;
		bool succes = programs.try_get_value(id, program);
		if (succes) {
			return program;
		}
		else {
			return WeakShaderReference();
		}
	}

	bool ShaderProgram::DeleteShader(std::string id)
	{
		ShaderReference program;
		bool succes = programs.try_get_value(id, program);
		if (succes) {
			program->unbind();
			programs.erase(id);
		}
		return succes;
	}

	std::string ShaderProgram::GetInfoLog()
	{
		int success;
		char infoLog[512];
		std::stringstream ss;
		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (success == GL_FALSE) {
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::stringstream ss;
			ss << "ERROR::PROGRAM::LINKING_FAILED: \n";
			ss << infoLog;
			return ss.str();
		}
		return std::string();
	}


	VertexShader::VertexShader(std::string folder_id, std::string file)
	{
		std::string result = FileManager::ReadTextFile(folder_id, file);
		if (result.empty()) {
			this->rtg = false;
		}
		this->handle = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* src = result.c_str();
		glShaderSource(this->handle, 1, &src, NULL);
		glCompileShader(this->handle);
		std::string error = this->GetInfoLog(this->handle, ShaderType::VERTEX);
		this->rtg = error.empty();
	}

	VertexShader::~VertexShader()
	{
		glDeleteShader(this->handle);
	}

	FragmentShader::FragmentShader(std::string folder_id, std::string file)
	{
		std::string result = FileManager::ReadTextFile(folder_id, file);
		if (result.empty()) {
			this->rtg = false;
		}
		this->handle = glCreateShader(GL_FRAGMENT_SHADER);
		const char* src = result.c_str();
		glShaderSource(this->handle, 1, &src, NULL);
		glCompileShader(this->handle);
		std::string error = this->GetInfoLog(this->handle, ShaderType::FRAGMENT);
		this->rtg = error.empty();
	}

	FragmentShader::~FragmentShader()
	{
		glDeleteShader(this->handle);
	}

	GeometryShader::GeometryShader(std::string folder_id, std::string file)
	{
		std::string result = FileManager::ReadTextFile(folder_id, file);
		if (result.empty()) {
			this->rtg = false;
		}
		this->handle = glCreateShader(GL_GEOMETRY_SHADER);
		const char* src = result.c_str();
		glShaderSource(this->handle, 1, &src, NULL);
		glCompileShader(this->handle);
		std::string error = this->GetInfoLog(this->handle, ShaderType::GEOMETRY);
		this->rtg = error.empty();
	}

	GeometryShader::~GeometryShader()
	{
		glDeleteShader(this->handle);
	}

	std::string Shader::GetInfoLog(GLuint handle, ShaderType type)
	{
		int success = GL_FALSE;
		char infoLog[512];
		std::stringstream ss;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(handle, 512, NULL, infoLog);
			std::string s_type = std::string();
			switch (type) {
			case ShaderType::FRAGMENT:
				s_type = "FRAGMENT";
				break;
			case ShaderType::VERTEX:
				s_type = "VERTEX";
				break;
			case ShaderType::GEOMETRY:
				s_type = "GEOMETRY";
				break;
			}
			ss << "ERROR::SHADER::" << s_type << "::COMPILATION_FAILED: \n";
			ss << infoLog;
			std::cout << infoLog << std::endl;
			return ss.str();
		};
		return std::string();
	}
}
