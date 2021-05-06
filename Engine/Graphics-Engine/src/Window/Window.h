#ifndef WINDOW_H
#define WINDOW_H

#include "Tools/Includes.h"

class GENGINE_API Window
{
	int width;
	int height;

	GLFWwindow* window;
public:
	Window();
	Window(int _width, int _height);

	GLFWwindow* getWindow();
	void setWidth(int _width);
	int getWigth();
	void setHeight(int _height);
	int getHeight();
	bool getWindowShouldClose();
	void setWindowShouldClose(bool state);

	int validateWindow();
	void makeContextCurrent();
	void initializeGLEW();
	void swapBuffers();
	void pollEvents();
	void terminateGLFW();
};

#endif // !WINDOW_H