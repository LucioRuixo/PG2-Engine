#include"window.h"

Window::Window()
{
	setWidth(1280);
	setHeight(720);
	window = glfwCreateWindow(width, height, "Unreal Engine 6", NULL, NULL);
}

Window::Window(int _width, int _height)
{
	setWidth(_width);
	setHeight(_height);
	window = glfwCreateWindow(width, height, "Unreal Engine 6", NULL, NULL);
}

GLFWwindow* Window::getWindow() { return window; }

void Window::setWidth(int _width) { width = _width; }
int Window::getWigth() { return width; }

void Window::setHeight(int _height) { height = _height; }
int Window::getHeight() { return height; }

void Window::setWindowShouldClose(bool state) { glfwSetWindowShouldClose(window, state); }
bool Window::getWindowShouldClose() { return glfwWindowShouldClose(window); }

int Window::validateWindow()
{
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
}

void Window::makeContextCurrent() { glfwMakeContextCurrent(window); }

void Window::initializeGLEW()
{
	glewInit();
	
	std::cout << glGetString(GL_VERSION) << std::endl << std::endl;
}

void Window::swapBuffers() { glfwSwapBuffers(window); }

void Window::pollEvents() { glfwPollEvents(); }

void Window::terminateGLFW() { glfwTerminate(); }