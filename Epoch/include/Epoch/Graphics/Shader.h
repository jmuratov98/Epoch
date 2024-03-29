#pragma once

namespace Epoch {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::string& getName() const = 0;

		static Ref<Shader> create(const std::string& filepath);
		static Ref<Shader> create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);;
	};

	class ShaderLibrary
	{
	public:
		void add(const std::string& name, const Ref<Shader>& shader);
		void add(const Ref<Shader>& shader);

		Ref<Shader> load(const std::string& name, const std::string& filepath);
		Ref<Shader> load(const std::string& filepath);

		Ref<Shader> get(const std::string& name);

		bool exisits(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}