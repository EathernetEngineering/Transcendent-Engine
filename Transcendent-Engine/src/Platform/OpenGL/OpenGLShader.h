#pragma once

#include <glm/glm.hpp>
#include "Transcendent-Engine/Renderer/Shader.h"

namespace TE {

	/*!
	 * Class for shaders written in glsl for OpenGL.
	 */
	class OpenGLShader : public Shader
	{
	public:
		/*!
		 * Consructor for OpenGL Shader class.
		 * @param Filepath Path to be used.
		 * @param Name Name of shader.
		 */
		OpenGLShader(const std::string& Filepath, const std::string& Name);
		/*!
		 * Consructor for OpenGL Shader class.
		 * @param VertexSource Soure code for vertex shader.
		 * @param FragmnetSource Soure code for fragmetn/pixel shader.
		 * @param Name Name of shader.
		 */
		OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource, const std::string& Name);

		/*!
		 * Desructor for OpenGL Shader class.
		 * Deletes the shader
		 */
		~OpenGLShader();

		/*!
		 * Binds the shader.
		 */
		void Bind()   override;
		
		/*!
		 * Unbinds the shader.
		 */
		void Unbind() override;


		/*!
		 * Cretes the shafer program from the inputs of the constructor.
		 * @see OpenGLShader()
		 */
		void Create() override;

		/*!
		 * Returns the name of the shader.
		 * @return std::string that contains the name of the shader.
		 */
		std::string GetName() { return m_Name; }

		/*!
		 * Returns the OpenGL renderer ID of the shader.
		 * @return unsigned int that contains the OpenGL renderer ID of the shader program.
		 */
		unsigned int GetID() { return m_ID; }

		/*!
		 * Sets a uniform within the shader.
		 */
		void SetUniform() override;
		/*!
		 * Sets a uniform within the shader.
		 * Type: single integer.
		 * @param Name Name of the uniform wihin the shader.
		 * @param i0 First integer.
		 */
		void SetUniform(const std::string& Name, int i0) override;
		/*!
		 * Sets a uniform within the shader.
		 * Type: single float.
		 * @param Name Name of the uniform wihin the shader.
		 * @param i0 First float.
		 */
		void SetUniform    (const std::string& Name, float i0) override;
		/*!														   
		 * Sets a uniform within the shader.					   
		 * Type: 4x4 matrix.									   
		 * @param Name Name of the uniform wihin the shader.	   
		 * @param i0 matrix.										   
		 */														   
		void SetUniform    (const std::string& Name, glm::mat4 i0) override;
		/*!															
		 * Sets a uniform within the shader.						
		 * Type: 2 integers.										
		 * @param Name Name of the uniform wihin the shader.		
		 * @param i0 First integer.
		 * @param i1 Second integer.
		 */															
		void SetUniform    (const std::string& Name, int i0, int i1) override;
		/*!																
		 * Sets a uniform within the shader.							
		 * Type: two floats.											
		 * @param Name Name of the uniform wihin the shader.			
		 * @param i0 First float.
		 * @param i1 Second float.
		 */																
		void SetUniform    (const std::string& Name, float i0, float i1) override;
		/*!																	
		 * Sets a uniform within the shader.								
		 * Type: three integers.											
		 * @param Name Name of the uniform wihin the shader.				
		 * @param i0 First integer.
		 * @param i1 Second integer.
		 * @param i2 Third integer.
		 */																	
		void SetUniform    (const std::string& Name, int i0, int i1, int i2) override;
		/*!																		
		 * Sets a uniform within the shader.									
		 * Type: three floats.													
		 * @param Name Name of the uniform wihin the shader.					
		 * @param i0 Fisrt float.
		 * @param i1 Second float.
		 * @param i2 Third float.
		 */																		
		void SetUniform    (const std::string& Name, float i0, float i1, float i2) override;
		/*!
		 * Sets a uniform within the shader.
		 * Type: three integers.
		 * @param Name Name of the uniform wihin the shader.
		 * @param i0 First integer.
		 * @param i1 Second integer.
		 * @param i2 Third integer.
		 * @param i3 fourth integer.
		 */
		void SetUniform    (const std::string& Name, int i0, int i1, int i2, int i3) override;
		/*!
		 * Sets a uniform within the shader.
		 * Type: three floats.
		 * @param Name Name of the uniform wihin the shader.
		 * @param i0 Fisrt float.
		 * @param i1 Second float.
		 * @param i2 Third float.
		 * @param i3 Fourth float.
		 */
		void SetUniform    (const std::string& Name, float i0, float i1, float i2, float i3) override;


	private:
		/*!
		 * Pases the file given. 
		 * For glsl shaders.
		 * @param Filepath The file to be parsed.
		 * @return The source for the shader(s).
		 */
		ShaderSource ParseShader(const std::string& Filepath) override;
		/*!
		 * retuns the location of the unifrom.
		 * Used by SetUniform().
		 * @param Name The name of the uniform in the shader program.
		 * @return unsigned integer that contains the location of the uniform
		 */
		GLuint GetUniformLocation(const std::string& Name);
		/*!
		 * Compiles Shader with given source code.
		 * @param VertexShader Source code for the vertex shader.
		 * @param FragmentShader Source code for the fragment shader.
		 * @return The OpenGL renderer ID of the shader program. 
		 */
		GLuint CompileShader(const std::string& VertexShader, const std::string& FragmentShader) override;
		/*!
		 * Compiles Shader with given source code.
		 * @param Source Source code for the shader(s).
		 * @return The OpenGL renderer ID of the shader program.
		 */
		GLuint CompileShader(const ShaderSource& Source) override;

	private:
		/*!
		 * Cache for unifrom loactions.
		 */
		std::unordered_map<std::string, GLuint> m_UniformLocations;
		/*!
		 * OpenGL renderer ID of the shader program.
		 */
		unsigned int m_ID;
		/*!
		 * File path of the shader, name of the shdaer, source for vertex program, source for fragment program.
		 */
		std::string m_Filepath, m_Name, m_VertexSource, m_FragmentSource;
		/*!
		 * Instace of this class.
		 */
		Shader* m_Instance;
	};
}
