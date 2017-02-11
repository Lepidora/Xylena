#include "stdafx.h"
#include "Window.h"

//Local includes
#include "Input.h"
#include "Mouse.h"
#include "WindowHandler.h"

void error_callback(int error, const char* description) {
    printf("Code: %i, Description: %s", error, description);
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    Xylena::WindowHandler::getMainWindow()->setPreferredSize(width, height);
}

namespace Xylena {

	void Window::DeleteWindow(GLFWwindow * window) {
		glfwDestroyWindow(window);
	}

	void Window::initNewWindow(const char* windowTitle, int width, int height, WindowType windowType) {
	
		//Attempts to initiate GLFW. If it doesn't, it returns immediately
		/*if (!glfwInit()) {
			fprintf(stderr, "Failed to initialize GLFW\n");
			return;
		}*/

        glfwSetErrorCallback(error_callback);
        
		//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
		
        GLFWmonitor *monitor = NULL;

        if (window.get() != nullptr) {
            monitor = glfwGetWindowMonitor(window.get());
        }

		window = GLFWwindowPtr();

        switch (windowType) {
        case WINDOWED: {
            monitor = NULL;
            break;
        }

        case WINDOWED_FULLSCREEN: {
            
            if (monitor == NULL) {
                monitor = glfwGetPrimaryMonitor();
            }

            const GLFWvidmode *mode = glfwGetVideoMode(monitor);

            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            width = mode->width;
            height = mode->height;

            break;
        }

        case FULLSCREEN: {

            if (monitor == NULL) {
                monitor = glfwGetPrimaryMonitor();
            }

            break;
        }

        default:
            break;

        }

		window.reset(glfwCreateWindow(width, height, windowTitle, monitor, NULL), DeleteWindow);

        currentType = windowType;

		if (window.get() == nullptr) {
			fprintf(stderr, "Failed to open GLFW window\n");
			glfwTerminate();
			return;
		}

		setGLContext();

        //Unlock FPS(?)
        glfwSwapInterval(0);

        //printf("INIT");

#ifndef __APPLE__
        glewExperimental = GL_TRUE; // Needed in core profile
        int errorCode = glewInit();
        if (errorCode) {
            printf("%i", errorCode);
            fprintf(stderr, "Failed to initialize GLEW\n");
            return;
        }
#endif

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window.get());

        Input::registerWindow(this);
        Mouse::registerWindow(this);
        
        glfwSetWindowSizeCallback(window.get(), &window_size_callback);

        prefwidth = width;
        prefheight = height;
	
	}

	void Window::setGLContext() {

		//Set the glfw context to the current Window's context
		glfwMakeContextCurrent(window.get());
	}

    void Window::setWindowType(WindowType windowType) {
        
        if (windowType == currentType) {
            return;
        } else {

            GLFWwindow *currentWindow = window.get();
            GLFWmonitor *monitor = glfwGetWindowMonitor(currentWindow);

            if (monitor == NULL) {
                monitor = glfwGetPrimaryMonitor();
            }

            int width, height;
            glfwGetWindowSize(currentWindow, &width, &height);

            if (width == 0) {
                width = prefwidth;
            }

            if (height == 0) {
                height = prefheight;
            }

            char *title = "";
            glfwSetWindowTitle(currentWindow, title);

            switch (windowType) {
            case WINDOWED: {

                window.reset(glfwCreateWindow(width, height, title, NULL, currentWindow), DeleteWindow);
                break;
            }

            case WINDOWED_FULLSCREEN: {

                const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);

                if (vidmode == NULL) {
                    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                }

                glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
                glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
                glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
                glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

                int vidwidth = vidmode->width;
                int vidheight = vidmode->height;

                window.reset(glfwCreateWindow(vidwidth, vidheight, title, monitor, currentWindow), DeleteWindow);

                break;
            }
                
            case FULLSCREEN: {

                window.reset(glfwCreateWindow(width, height, title, monitor, currentWindow), DeleteWindow);
                break;
            }
                
            default:
                break;
            }

            setGLContext();
        }

    }

    void Window::lockFPS(int refreshes) {
        glfwSwapInterval(refreshes);
    }

    void Window::vsync(bool enable) {
        if (enable) {
            lockFPS(1);
        } else {
            lockFPS(0);
        }
    }

    void Window::setWindowSize(int width, int height) {
        
        glfwSetWindowSize(window.get(), width, height);
        
        prefwidth = width;
        prefheight = height;

    }
    
    void Window::setPreferredSize(int width, int height) {
        prefwidth = width;
        prefheight = height;
    }

    Coordinate Window::getWindowSize() {
        return Coordinate(prefwidth, prefheight, 0.0);
    }

}