#include "THPrecomp.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/RenderAPI/OpenGL/OpenGLShader.h"
namespace TopHat
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: TH_FRAMEWORK_ASSERTS(false, "Render API Not set or doesn't exist"); return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGLShader(filepath);
		}
		
	}

}
