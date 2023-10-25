#include "THPrecomp.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/RenderAPI/OpenGL/OpenGLVertexArray.h"
namespace TopHat
{
	VertexArray* VertexArray::Create()
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None: TH_FRAMEWORK_ASSERTS(false, "Render API Not set or doesn't exist"); return nullptr;
		case RenderAPI::API::OpenGL: return new OpenGLVertexArray();
		}
	}

}
