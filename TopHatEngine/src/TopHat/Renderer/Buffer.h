#pragma once

namespace TopHat
{
	enum class ShaderVarType{ None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool};

	static uint8_t ShaderVarSize(ShaderVarType type) 
	{
		switch (type)
		{
			case ShaderVarType::Float:	 return  4;
			case ShaderVarType::Float2:  return  4 * 2;
			case ShaderVarType::Float3:  return  4 * 3;
			case ShaderVarType::Float4:  return  4 * 4;
			case ShaderVarType::Mat3:    return  4 * 3 * 3;
			case ShaderVarType::Mat4:    return  4 * 4 * 4;
			case ShaderVarType::Int:	 return  4;
			case ShaderVarType::Int2:    return  4 * 2;
			case ShaderVarType::Int3:    return  4 * 3;
			case ShaderVarType::Int4:    return  4 * 4;
			case ShaderVarType::Bool:	 return  1;
		}

		TH_FRAMEWORK_ASSERTS(false, "Unknown Shader Variable Type")
			return 0;

	}

	struct BufferElement
	{
		std::string name;
		ShaderVarType type;
		//might change to be smaller value
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement(ShaderVarType type, const std::string& name, bool normalized = false):type(type), name(name), normalized(normalized),
		size(ShaderVarSize(type)), offset(0) {}

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
			case ShaderVarType::Float:	 return  1;
			case ShaderVarType::Float2:  return  2;
			case ShaderVarType::Float3:  return  3;
			case ShaderVarType::Float4:  return  4;
			case ShaderVarType::Mat3:    return  4 * 3;
			case ShaderVarType::Mat4:    return  4 * 4;
			case ShaderVarType::Int:	 return  1;
			case ShaderVarType::Int2:    return  2;
			case ShaderVarType::Int3:    return  3;
			case ShaderVarType::Int4:    return  4;
			case ShaderVarType::Bool:	 return  1;
			}

			TH_FRAMEWORK_ASSERTS(false, "Unknown Shader Variable Type")
				return 0;

		}
	};

	class BufferLayout
	{
	public:

		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements) :m_Elements(elements) { CalculateOffsetAndStride(); }

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetBufferElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.begin(); }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for(auto& e : m_Elements)
			{
				e.offset = offset;
				offset += e.size;
				m_Stride += e.size;

			}

		}
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetBufferLayout() const = 0;
		virtual  void SetBufferLayout(const BufferLayout& bl) = 0;

		static VertexBuffer* Create(float* verticies, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indicies, uint32_t size);
	};
}
