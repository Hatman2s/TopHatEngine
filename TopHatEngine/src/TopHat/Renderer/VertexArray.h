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

		virtual void AddVertexBuf(const std::shared_ptr<VertexBuffer>& vb) = 0;
		virtual void AddIndexBuf(const std::shared_ptr<IndexBuffer>& ib) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();

	};
}
