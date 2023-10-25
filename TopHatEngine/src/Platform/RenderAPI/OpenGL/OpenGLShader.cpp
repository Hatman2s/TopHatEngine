#include "THPrecomp.h"
#include "OpenGLShader.h"
#include "glad/glad.h"
#include "gtc/type_ptr.hpp"
#include <fstream>

namespace TopHat
{
	static GLenum ShaderType(const std::string& type)
	{
		if(type == "vertex")
		{
			return GL_VERTEX_SHADER;

		}
		if(type == "fragment")
		{
			return GL_FRAGMENT_SHADER;
		}
		TH_FRAMEWORK_ASSERTS(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSRC = PreProcess(source);
		Compile(shaderSRC);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RenderID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RenderID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_RenderID, name.c_str()), value);
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, glm::int2& values)
	{
		glUniform2i(glGetUniformLocation(m_RenderID, name.c_str()), values.x, values.y);
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, glm::int3& values)
	{
		glUniform3i(glGetUniformLocation(m_RenderID, name.c_str()), values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, glm::int4& values)
	{
		glUniform4i(glGetUniformLocation(m_RenderID, name.c_str()), values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_RenderID, name.c_str()), value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, glm::vec2& values)
	{
		glUniform2f(glGetUniformLocation(m_RenderID, name.c_str()), values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, glm::vec3& values)
	{
		glUniform3f(glGetUniformLocation(m_RenderID, name.c_str()), values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, glm::vec4& values)
	{
		glUniform4f(glGetUniformLocation(m_RenderID, name.c_str()), values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, glm::mat3& value)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_RenderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_RenderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(m_RenderID, name.c_str()), value);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if(in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			TH_FRAMEWORK_ASSERTS(false, "FAILED TO READ SHADER FILE");
		}

		 
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSRC;

		const char* token = "#type";
		size_t tokenLength = strlen(token);
		size_t pos = source.find(token, 0);
		while(pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			TH_FRAMEWORK_ASSERTS(eol != std::string::npos, "SYNTAX ERROR!");
			size_t begin = pos + tokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			TH_FRAMEWORK_ASSERTS(ShaderType(type), "NO KNOWN SHADER TYPE SPECIFIED!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(token, nextLinePos);
			shaderSRC[ShaderType(type)] = source.substr(nextLinePos, 
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));

		}

		return shaderSRC;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shader)
	{
		
		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shader.size());

		for(auto& kv : shader)
		{
			GLenum type = kv.first;
			const std::string& src = kv.second;
			GLuint shader = glCreateShader(type);
			const GLchar* sourceCStr = src.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if(isCompiled == GL_FALSE)
			{

				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				TH_ENGINE_ERROR("{0}", infoLog.data());
				TH_FRAMEWORK_ASSERTS(false, "Shader Compilation Faliure!");

				break;

			}
			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);

		}
		m_RenderID = program;

		glLinkProgram(program);
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if(isLinked == GL_FALSE)
		{

			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glad_glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for(auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}
			TH_ENGINE_ERROR("{0}", infoLog.data());
			TH_FRAMEWORK_ASSERTS(false, "Program Linking Failed");
			return;
		}
		for (auto id : glShaderIDs)
		{
			glDetachShader(program,id);
		}
	}

















}
