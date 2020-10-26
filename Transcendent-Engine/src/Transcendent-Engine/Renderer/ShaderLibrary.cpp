#include "tepch.h"
#include "Transcendent-Engine/Renderer/ShaderLibrary.h"

namespace TE {

	std::unordered_map<std::string, uint32_t>    ShaderLibrary::m_IDs;
	std::unordered_map<uint32_t, std::string>    ShaderLibrary::m_Names;
	std::unordered_map<std::string, Ref<Shader>> ShaderLibrary::m_Shaders;

	void ShaderLibrary::Init() {

		const char* Default1Vertex =   "#version 410\n\n"
		                                          "layout(location = 0) in vec4 VertexPosition;\n\n"
		                                          "void main() {\n\n"
		                                          "gl_Position = VertexPosition;\n"
		                                          "}\n";
						   
		const char* Default1Fragment = "#version 410\n\n"
		                                         "layout(location = 0) out vec4 color;\n\n"
		                                         "void main() {\n\n"
		                                         "color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		                                         "}\n";
						   
		const char* Default2Vertex =   "#version 410\n\n"
		                                         "layout(location = 0) in vec4 VertexPosition;\n\n"
		                                         "uniform mat4 u_ViewProjection;\n"
		                                         "uniform mat4 u_Transform;\n\n"
		                                         "void main() {\n\n"
		                                         "gl_Position = u_ViewProjection * u_Transform * VertexPosition;\n"
		                                         "}\n";

		const char* Default2Fragment = "#version 410\n\n"
		                                         "layout(location = 0) out vec4 color;\n\n"
		                                         "uniform vec4 u_Colour;\n\n"
		                                         "void main() {\n\n"
		                                         "color = u_Colour;\n"
		                                         "}\n";

		const char* Default3Vertex =   "#version 410\n\n"
		                                         "layout(location = 0) in vec3 VertexPosition;\n"
		                                         "layout(location = 1) in vec2 TexCoords;\n\n"
		                                         "uniform mat4 u_Transform;\n"
		                                         "uniform mat4 u_ViewProjection;\n"
		                                         "out vec2 v_TexCoord;\n\n"
		                                         "void main() {\n\n"
		                                         "gl_Position = u_ViewProjection * u_Transform * vec4(VertexPosition, 1.0);\n"
		                                         "v_TexCoord = TexCoords;\n"	
		                                         "}\n";

		const char* Default3Fragment = "#version 410\n\n"
		                                         "layout(location = 0) out vec4 color;\n\n"
		                                         "in vec2 v_TexCoord;\n\n"
		                                         "uniform vec4 u_Colour;\n"
		                                         "uniform sampler2D u_Texture;\n\n"
		                                         "void main() {\n\n"
		                                         "color = texture(u_Texture, v_TexCoord * 10.0) * u_Colour;\n"
		                                         "}\n";
		
		Add(ShaderSource(Default1Vertex, Default1Fragment), "White");
		Add(ShaderSource(Default2Vertex, Default2Fragment), "Colour");
		Add(ShaderSource(Default3Vertex, Default3Fragment), "Texture");
	}

	void ShaderLibrary::Shutdown() {


	}

	void ShaderLibrary::BindShader(const std::string& Name) {

		GetShader(Name)->Bind();
	}

	void ShaderLibrary::BindShader(uint32_t ID) {

		GetShader(m_Names[ID])->Bind();
	}

	void ShaderLibrary::UnbindShader(const std::string& Name) {

		GetShader(Name)->Unbind();
	}

	void ShaderLibrary::UnbindShader(uint32_t ID) {

		GetShader(m_Names[ID])->Unbind();
	}

	void ShaderLibrary::Add(const std::string& Filepath, const std::string& Name) {

		if (m_Shaders.find(Name) != m_Shaders.end()) {
			if (m_Shaders[Name] != nullptr)
				TE_CORE_WARN("Shader {0} already exists!", Name);
		}
		else {
		m_Shaders[Name] = Shader::Create(Filepath, Name);
		m_IDs[Name] = m_Shaders[Name]->GetID();
		m_Names[m_IDs[Name]] = Name;
		}
	}

	void ShaderLibrary::Add(const ShaderSource& Source, const std::string& Name) {

		if (m_Shaders.find(Name) != m_Shaders.end()) {
			if (m_Shaders[Name] != nullptr)
				TE_CORE_WARN("Shader {0} already exists!", Name);
		}
		else {
			m_Shaders[Name] = Shader::Create(Source, Name);
			m_IDs[Name] = m_Shaders[Name]->GetID();
			m_Names[m_IDs[Name]] = Name;
		}
	}

	void ShaderLibrary::Remove(std::string& Name) {

		if (m_Shaders.find(Name) != m_Shaders.end()) {
			m_Shaders[Name] = nullptr;
			m_Names[m_IDs[Name]] = "\n";
			m_IDs[Name] = (uint32_t)-1;
		} else
			TE_CORE_WARN("Shader {0} doesn't exist!", Name);
	}

	void ShaderLibrary::Remove(uint32_t ID) {

		if (m_Shaders.find(GetName(ID)) != m_Shaders.end()) {
			m_Shaders[m_Names[ID]] = nullptr;
			m_IDs[m_Names[ID]] = (uint32_t)-1;
			m_Names[ID] = "\n";
		} else
			TE_CORE_WARN("Shader {0} doesn't exist!", m_Names[ID]);
	}

	std::string ShaderLibrary::GetName(uint32_t ID) {

		if (m_Names.find(ID) != m_Names.end())
			if (m_Shaders[m_Names[ID]] != nullptr)
				return m_Names[ID];
		else
			TE_CORE_WARN("Shader {0} doesn't exist!", m_Names[ID]);
	}

	uint32_t ShaderLibrary::GetID(std::string& Name) {

		if (m_IDs.find(Name) != m_IDs.end())
			if (m_Shaders[Name] != nullptr)
				return m_IDs[Name];
		else
			TE_CORE_WARN("Shader \"{0}\" doesn't exist!", Name);
	}

	Ref<Shader> ShaderLibrary::GetShader(const std::string& Name) {

		if (m_Shaders.find(Name) != m_Shaders.end())
			return m_Shaders[Name];
		else
			TE_CORE_WARN("Shader \"{0}\" doesn't exist!", Name);

		return nullptr;
	}

	Ref<Shader> ShaderLibrary::GetShader(uint32_t ID) {

		if (m_Shaders.find(m_Names[ID]) != m_Shaders.end())
			if (m_Shaders[m_Names[ID]] != nullptr)
				return m_Shaders[m_Names[ID]];
			else
				TE_CORE_WARN("Shader \"{0}\" doesn't exist!", m_Names[ID]);

		return nullptr;
	}
}
