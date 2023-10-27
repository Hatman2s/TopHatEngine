#pragma once
#include "VertexArray.h"
#include "TopHat/Camera.h"
#include "Shader.h"
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
		static void BeginScene(Camera& cam);
		static void EndScene();
		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
		static void Submit(std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray);
	private:
		 struct SceneData
		 {
			 glm::mat4 m_ProjectionViewMatrix;
		 };
		 static SceneData* m_SD;
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