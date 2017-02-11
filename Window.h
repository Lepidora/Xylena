#pragma once

//System includes
#include <memory>
#include <string>

//OpenGL include
#include "OpenGL.h"

//Local includes
#include "Coordinate.h"

namespace Xylena {

    enum WindowType {
        WINDOWED, WINDOWED_FULLSCREEN, FULLSCREEN
    };

	//Typedefs
	typedef std::shared_ptr<GLFWwindow> GLFWwindowPtr;

	class Window {
    private:
        //void error_callback(int error, const char* description);
        void lockFPS(int fps);
	protected:
		GLFWwindowPtr window;
		static void DeleteWindow(GLFWwindow *window);
        WindowType currentType;
        GLFWmonitor *currentMonitor;

        int prefwidth, prefheight;

	public:
        Window() { currentMonitor = NULL; };
		~Window() {};

		///Window creation
		void initNewWindow(const char* windowTitle, int width, int height, WindowType windowType);

		///Sets the OpenGL context to this window
		void setGLContext();

		///Get GLFW window pointer
		GLFWwindowPtr getGLFWwindowPtr() { return window; };

        ///Fullscreen get/set
        WindowType getWindowType() { return currentType; };
        void setWindowType(WindowType windowType);

        ///Change monitors
        GLFWmonitor *getCurrentMonitor() { return glfwGetWindowMonitor(window.get()); };
        void setCurrentMonitor(GLFWmonitor *monitor) { currentMonitor = monitor; };

        ///Set Vsync
        void vsync(bool enable);

        ///Change window size
        void setWindowSize(int width, int height);
        ///Change prefererred window size
        void setPreferredSize(int width, int height);
        ///Get window size
        Coordinate getWindowSize();

	};

	//Typedefs
	typedef std::shared_ptr<Window> WindowPtr;
}
