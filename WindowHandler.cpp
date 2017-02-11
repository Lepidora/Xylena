#include "stdafx.h"
#include "WindowHandler.h"

//System includes
#include <stdio.h>

//Local includes
#include "Window.h"

namespace Xylena {

	//Static variable initialisation
	WindowPtr WindowHandler::mainWindow = nullptr;

	void WindowHandler::openMainWindow(const char* title, int width, int height, WindowType type) {

		//Initialises a new window with the specified height, width and title
		WindowPtr window(new Window);
		window.get()->initNewWindow(title, width, height, type);

		mainWindow = window;

	}
	WindowPtr WindowHandler::getMainWindow() {
		return mainWindow;
	}
}