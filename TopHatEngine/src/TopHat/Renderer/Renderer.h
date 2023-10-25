#pragma once

#include "glm.hpp"
#include "VertexArray.h"

namespace TopHat
{
	class RenderContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

	class RenderAPI
	{
	public:
		enum class API { None = 0, OpenGL = 1 };

		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) =0;

		inline static API GetAPI() { return s_API; }
	private:

		static API s_API;

	};

	class Renderer
	{
	public:
		static void Init();
		static void BeginScene();
		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	private:
		//TODO: implement Scene Data here
	};

	class RenderCommand
	{
	public:
		inline static void Init() { s_RenderAPi->Init(); }
		inline static void SetClearColor(const glm::vec4& color) { s_RenderAPi->SetClearColor(color); }
		inline static void Clear() { s_RenderAPi->Clear(); }
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { s_RenderAPi->DrawIndexed(vertexArray); }
	private:
		static RenderAPI* s_RenderAPi;

	};

	
}