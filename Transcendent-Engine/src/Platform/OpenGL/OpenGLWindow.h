#pragma once

#include "Transcendent-Engine/core/Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TE {

	/*!
	 * OpenGL implementation of windows.
	 */
	class OpenGLWindow : public Window
	{
	public:

		/*!
		 * Constuctor of OpenGL window class.
		 * @param props The properties of the window.
		 * @see WindowProps.
		 */
		OpenGLWindow(const WindowProps& props);
		/*!
	     * Destructor of OpenGL window class.
		 * Deletes window.
	     */
		virtual ~OpenGLWindow();

		/*!
		 * Function to be called every frame.
		 */
		void OnUpdate() override;

		/*!
		 * Get the width of the window.
		 * @return an unsigned int containing the width of the window.
		 */
		inline unsigned int GetWidth(void) const override { return m_Data.Width; }
		/*!
		 * Get the height of the window.
		 * @return an unsigned int containing the height of the window.
		 */
		inline unsigned int GetHeight(void) const override { return m_Data.Height; }

		/*!
		 * Set the window event callback.
		 * @param callback Function to be used.
		 */
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		/*!
		 * Set VSync bool.
		 * @param enabled Bool consaining desired state of VSync.
		 */
		void SetVSync(bool enabled) override;
		/*!
		 * check VSync bool.
		 * @return Bool consaining state of VSync.
		 */
		bool IsVSync(void) const override;

		/*!
		 * get the native window pointer.
		 * GLFWwindow
		 * @return void pointer to window pointer location. MUST be cast to GLFWwindow*
		 */
		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		/*!
		 * Initialize the window.
		 * Called by OpenGLWindow().
		 * @param props The properties of the window.
		 */
		virtual void Init(const WindowProps& props);
		/*!
		 * delete the window.
		 * Called by ~OpenGLWindow()
		 */
		virtual void Shutdown();
	
	private:
		GLFWwindow* m_Window;

		/*!
		 * Properties for window creataion.
		 */
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
