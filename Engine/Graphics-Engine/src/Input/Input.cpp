#include "Input.h"

Input::Input(Window* _window)
{
	window = _window;
}

Input::~Input()
{
	if (window) delete window;
}

bool Input::getKeyPress(PrintableKey key)
{
	return glfwGetKey(window->getWin(), key) == GLFW_PRESS;
}

bool Input::getKeyPress(FunctionKey key)
{
	return glfwGetKey(window->getWin(), key) == GLFW_PRESS;
}

bool Input::getKeyRelease(PrintableKey key)
{
	return glfwGetKey(window->getWin(), key) == GLFW_RELEASE;
}

bool Input::getKeyRelease(FunctionKey key)
{
	return glfwGetKey(window->getWin(), key) == GLFW_RELEASE;
}