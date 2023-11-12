#include "THPrecomp.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/RenderAPI/OpenGL/OpenGLShader.h"
namespace TopHat
{
	Ref<Shader>Shader::Create(const std::string& filepath)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: TH_FRAMEWORK_ASSERTS(false, "Render API Not set or doesn't exist"); return nullptr;
			case RenderAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}
		
	}

	 

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		m_Shaders[name] = Shader::Create(filepath);
		return m_Shaders[name];
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		std::string name = filepath.substr(lastSlash, count);

		m_Shaders[name] = Shader::Create(filepath);
		return m_Shaders[name];
	}
	Ref<Shader> ShaderLibrary::GetShader(const std::string& name)
	{
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name)
	{
		if(m_Shaders[name] != NULL)
		{
			return true;
		}
		return false;
	}

}
