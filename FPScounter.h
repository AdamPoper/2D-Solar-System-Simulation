#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
class FPScounter
{
public:
	FPScounter()
	{		
		numFrames = 0;
		lastTime = glfwGetTime();
	}
	void drawFPS(GLFWwindow* window)
	{
		double currentTime = glfwGetTime();
		numFrames++;
		if (currentTime - lastTime >= 1.0f)
		{
			fps = (double)numFrames / (currentTime - lastTime);
			std::cout << fps << std::endl;
			numFrames = 0;
			lastTime += 1.0;
			std::string s_fps("Current FPS: ");
			s_fps += std::to_string(fps);
			glfwSetWindowTitle(window, s_fps.c_str());
		}
	}
private:
	double lastTime, fps;
	unsigned int numFrames;
	std::string title;
};