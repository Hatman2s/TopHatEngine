#include "THPrecomp.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/RenderAPI/OpenGL/OpenGLBuffer.h"

namespace TopHat
{
	VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: TH_FRAMEWORK_ASSERTS(false, "Render API Not Set/Supported!"); return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGLVertexBuffer(verticies, size);

		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None: TH_FRAMEWORK_ASSERTS(false, "Render API Not Set/Supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

	}
}
