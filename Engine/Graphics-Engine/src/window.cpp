#include"window.h"

GLFWwindow* win;

Window::Window() {
	setWidth(1280);
	setHeight(720);
	win = glfwCreateWindow(width, height, "Unreal Engine 6", NULL, NULL);
}

GLFWwindow* Window::getWin() {
	return win;
}

void Window::setWidth(int _width) {
	width = _width;
}

void Window::setHeight(int _height) {
	height = _height;
}

int Window::getWigth() {
	return width;
}

int Window::getHeight() {
	return height;
}

int Window::createWindowValidate() {
	if (!win) {
		glfwTerminate();
		return -1;
	}
}

void Window::createContexCurrent() {
	glfwMakeContextCurrent(win);
}

void Window::initGLEW() {
	glewInit();
}

bool Window::detecWindowShouldClose() {
	return glfwWindowShouldClose(win);
}

void Window::setWindowShouldClose(bool state) {
	glfwSetWindowShouldClose(win, state);
}

void Window::swapBuffers() {
	glfwSwapBuffers(win);
}

void Window::pollEvents() {
	glfwPollEvents();
}

void Window::glfwTerminate() {
	glfwTerminate();
}