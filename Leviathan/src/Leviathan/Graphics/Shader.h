#pragma once
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>
#include <memory>


namespace Leviathan::Graphics {
	
	enum class ShaderType {
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
		void unbind();

		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		void setUniform(const char* name, const int value);
		void setUniform(const char* name, const unsigned int value);
		void setUniform(const char* name, const float value);
		void setUniform(const char* name, const double value);
		
		void setUniform(const char* name, const glm::vec2& value);
		void setUniform(const char* name, const glm::vec3& value);
		void setUniform(const char* name, const glm::vec4& value);

		void setUniform(const char* name, const glm::ivec2& value);
		void setUniform(const char* name, const glm::ivec3& value);
		void setUniform(const char* name, const glm::ivec4& value);

		void setUniform(const char* name, const glm::dvec2& value);
		void setUniform(const char* name, const glm::dvec3& value);
		void setUniform(const char* name, const glm::dvec4& value);
		
		void setUniform(const char* name, const glm::mat4& value);

		static bool AddShader(std::string shader_id, std::string folder_id, std::string frag_file, std::string vert_file);
		static bool AddShader(std::string shader_id, std::string folder_id, std::string frag_file, std::string vert_file, std::string geo_file);
		static std::weak_ptr<ShaderProgram> GetShader(std::string id);
		static bool DeleteShader(std::string id);

	private:
		std::string GetInfoLog();

	};

	typedef std::shared_ptr<ShaderProgram> ShaderReference;
	typedef std::weak_ptr<ShaderProgram> WeakShaderReference;

}

