#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferlayout.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Texture.h"
#include "FPScounter.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Planet.h"
#include "vector2f.h"

void enableBlend()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

typedef Planet Sun;
typedef vector2f ScreenSpace;
int main()
{
	GLFWwindow* window;
	const float WIDTH = 1920.0f;
	const float HEIGHT = 1080.0f;
	const int NUM_PLANETS = 6;
	std::string f_paths[] = {
		"res/textures/mercury.png",
		"res/textures/venus.png",
		"res/textures/earth.png",
		"res/textures/mars.png",
		"res/textures/jupiter.png",
		"res/textures/saturn.png" };

	float radii[] = {
		520.0f, 720.0f, 1000.0f, 1230.0f, 1640.0f, 2170.0f
	};

	float speeds[] = {
		0.25f, 0.17f, 0.125f, 0.085f, 0.045f, 0.030f
	};

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	// add to the preprocessor GLEW_STATIC
	if (glewInit() != GLEW_OK)
		std::cout << "Glew not ok" << std::endl;
	else std::cout << "Glew Ok!" << std::endl;

	vector2f planetSizes[NUM_PLANETS] = { { 20.0f, 20.0f }, { 35.0f, 35.0f }, { 35.0f, 35.0f }, { 24.0f, 24.0f }, { 140.0f, 140.0f }, { 100.0f, 100.0f } };
	struct vertexData
	{
		float data[16];
		float* getData()
		{
			return data;
		}
	};
	float sunData[] = {
		-200.0f,  200.0f, 0.0f, 1.0f,
		 200.0f,  200.0f, 1.0f, 1.0f,
		 200.0f, -200.0f, 1.0f, 0.0f,
	    -200.0f, -200.0f, 0.0f, 0.0f
	};
	
	vertexData v_buffer_info[NUM_PLANETS];
	
	for (int i = 0; i < NUM_PLANETS; i++)
		v_buffer_info[i] = { -planetSizes[i].x, planetSizes[i].y, 0.0f, 1.0f, planetSizes[i].x, planetSizes[i].y, 1.0f, 1.0f, planetSizes[i].x, -planetSizes[i].y, 1.0f, 0.0f, -planetSizes[i].x, -planetSizes[i].y };

	unsigned int i_buffer_data[] = {
		0, 1, 3,
		3, 1, 2
	};
	
	Sun sun("res/textures/sun.png", 5, 0.3, sunData, sizeof(float) * 16);
	std::array<Planet*, NUM_PLANETS> planets;

	for (int i = 0; i < planets.size(); i++)
		planets[i] = new Planet(f_paths[i].c_str(), radii[i], speeds[i], v_buffer_info[i].getData(), sizeof(float) * 16);
	
	ScreenSpace viewPos = {WIDTH/2.0f, HEIGHT/2.0f};
	glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);	
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(viewPos.x, viewPos.y, 0.0f));
	glm::mat4 mvp; // end result of the model view projection matrix will be updated later

	IndexBuffer i_buffer(i_buffer_data, sizeof(unsigned int) * 6, 6);
	
	VertexBufferLayout mainlayout;
	// vertex positions
	mainlayout.push<float>(2);
	// texture coords
	mainlayout.push<float>(2);
	VertexArray v_array;
	ShaderProgram shader("res/shaders/VertexShader.shader", "res/shaders/FragmentShader.shader");
	Renderer render;
	enableBlend();
	v_array.unbind();
	i_buffer.unbind();
	shader.unbind();
	FPScounter fps;
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		fps.drawFPS(window);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			viewPos.x += 1.0f;
			view = glm::translate(glm::mat4(1.0f), glm::vec3(viewPos.x, viewPos.y, 1.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			viewPos.x -= 1.0f;
			view = glm::translate(glm::mat4(1.0f), glm::vec3(viewPos.x, viewPos.y, 1.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			viewPos.y -= 1.0f;
			view = glm::translate(glm::mat4(1.0f), glm::vec3(viewPos.x, viewPos.y, 1.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			viewPos.y += 1.0f;
			view = glm::translate(glm::mat4(1.0f), glm::vec3(viewPos.x, viewPos.y, 1.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			sun.scaleUp(0.001);
			for (auto& p : planets)
				p->scaleUp(0.001);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			sun.scaleDown(0.001);
			for (auto& p : planets)
				p->scaleDown(0.001);
		}
		
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);	
		
		v_array.addBuffer(sun.retrieveVertexBuffer(), mainlayout);
		sun.bind();
		sun.calcPosition();
		shader.setUniform1i("u_Texture", 0);
		mvp = projection * view * sun.getModel();
		shader.setUniformMat4("u_MVP", mvp);
		render.draw(v_array, i_buffer, shader);
		
		for (auto& p : planets)
		{
			v_array.addBuffer(p->retrieveVertexBuffer(), mainlayout);
			p->bind();
			p->calcPosition();
			mvp = projection * view * p->getModel();
			shader.setUniform1i("u_Texture", 0);
			shader.setUniformMat4("u_MVP", mvp);
			render.draw(v_array, i_buffer, shader);
		}
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	for (auto& p : planets)
		delete p;

	glfwTerminate();
	return 0;
}