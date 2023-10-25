#pragma once

#include "glm.hpp"
#include "gtx/compatibility.hpp"
#include "gtx/type_aligned.hpp"
#include "TopHat/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace TopHat
{
	class OpenGLShader: public Shader
	{
	public:

		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformInt2(const std::string& name, glm::int2& values);
		void UploadUniformInt3(const std::string& name, glm::int3& values);
		void UploadUniformInt4(const std::string& name, glm::int4& values);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, glm::vec4& values);

		void UploadUniformMat3(const std::string& name, glm::mat3& value);
		void UploadUniformMat4(const std::string& name, glm::mat4& value);

		void UploadUniformBool(const std::string& name, bool value);

	private:
		uint32_t m_RenderID;

		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shader);

	};
}
