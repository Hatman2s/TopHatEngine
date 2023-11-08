#pragma once

#include <string>

namespace TopHat
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& name, const std::string& filepath);

	};

	class ShaderLibrary
	{
	public:
		/*void Add(const std::string& name, const std::string& filepath);
		void Add(const std::string& filepath);
		void Add(Ref<Shader> shader);*/

		Ref<Shader>Load(const std::string& name, const std::string& filepath);
		Ref<Shader>Load(const std::string& filepath);

		Ref<Shader>GetShader(const std::string& name);
		bool Exists(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Shader>>m_Shaders;
	};
}
