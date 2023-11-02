#pragma once
#include "Buffer.h"

namespace TopHat
{
	class VertexArray
	{
	public:

		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuf(const Ref<VertexBuffer>& vb) = 0;
		virtual void AddIndexBuf(const Ref<IndexBuffer>& ib) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();

	};
}
