#include "THPrecomp.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"
 

namespace TopHat
{
	static GLenum ShaderTypeToGLType(ShaderVarType type)
	{
		switch (type)
		{
			case ShaderVarType::Int:	return GL_INT;
			case ShaderVarType::Int2:	return GL_INT;
			case ShaderVarType::Int3:	return GL_INT;
			case ShaderVarType::Int4:	return GL_INT;
			case ShaderVarType::Float:	return GL_FLOAT;
			case ShaderVarType::Float2: return GL_FLOAT;
			case ShaderVarType::Float3: return GL_FLOAT;
			case ShaderVarType::Float4: return GL_FLOAT;
			case ShaderVarType::Mat3:	return GL_FLOAT;
			case ShaderVarType::Mat4:	return GL_FLOAT;
			case ShaderVarType::Bool:	return GL_BOOL;
		}

		TH_FRAMEWORK_ASSERTS(false, "Unknown shader type!");
		return 0;

	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RenderID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuf(const std::shared_ptr<VertexBuffer>& vb)
	{
		TH_FRAMEWORK_ASSERTS(vb->GetBufferLayout().GetBufferElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RenderID);

		vb->Bind();

		uint32_t index = 0;
		const auto& layout = vb->GetBufferLayout();
		for(const auto& e : layout.GetBufferElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, e.GetComponentCount(), ShaderTypeToGLType(e.type), e.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)e.offset);
			index++;
		}
		m_VertexBuffers.push_back(vb);
	}
	void OpenGLVertexArray::AddIndexBuf(const std::shared_ptr<IndexBuffer>& ib)
	{
		glBindVertexArray(m_RenderID);
		ib->Bind();
		m_IndexBuffer = ib;
	}





}
