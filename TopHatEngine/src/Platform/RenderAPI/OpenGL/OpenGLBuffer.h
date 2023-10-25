#pragma once

#include "TopHat/Renderer/Buffer.h"

namespace TopHat
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		const BufferLayout& GetBufferLayout()  const override { return m_Layout; }
		void SetBufferLayout(const BufferLayout& bl) override { m_Layout = bl; };

	private:
		uint32_t m_RenderID;
		BufferLayout m_Layout;

	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:

		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RenderID;
		uint32_t m_Count;

	};
	//Todo: rewatch the videos as see if you can identify bug

}
