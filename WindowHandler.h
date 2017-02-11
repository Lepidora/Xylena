#pragma once

//System includes
#include <memory>

//Local includes
#include "Window.h"
#include "Profiler.h"

namespace Xylena {

	class WindowHandler {
	private:
		static WindowPtr mainWindow;
	public:
		WindowHandler() {};
		~WindowHandler() {};

		///Creation method for the main window
		static void openMainWindow(const char* title, int width, int height, WindowType type);

		///Getter for main window
		static WindowPtr getMainWindow();

		///Getter for raw GLFW window pointer of main window
		static GLFWwindow* getMainWindowGLPointer() { return getMainWindow().get()->getGLFWwindowPtr().get(); };

	};

}