#include "THPrecomp.h"
#include "Texture.h"
#include "Platform/RenderAPI/OpenGL/OpenGLTexture.h"
namespace TopHat
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		return std::make_shared<OpenGLTexture>(path);
	}

}
