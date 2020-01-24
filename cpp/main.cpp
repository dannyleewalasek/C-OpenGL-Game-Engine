#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <vector>
#include "../libraries/GLEW/include/GL/glew.h"
#include "../libraries/GLFW/include/GLFW/glfw3.h"
#include "../headers/Game.h"


GLint WIDTH = 1280, HEIGHT = 720;
globals global;
Game game;
float globals::height = 720;
float globals::width = 1280;
float globals::mousePosX = 0.0f;
float globals::mousePosY = 0.0f;
float globals::lastTime = 0.0f;
float globals::deltaTime = 0.0f;
float globals::currentTime = 0.0f;

/**
 * Handle the mouse movement through glfw.
 *
 * @param window A pointer to the GLFW window object used to display the game.
 * @param game A pointer to the running Game object.
 */
void mouseInput(GLFWwindow *window, Game *game)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	global.SetMousePosX(xpos);
	global.SetMousePosY(ypos);
}

/**
 * Handle the keyboard input through glfw.
 *
 * @param window A pointer to the GLFW window object used to display the game.
 * @param key The GLFW code for the key which has been pressed.
 * @param scancode 
 * @param mods
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		game.Keys[key] = 1;
	if (action == GLFW_RELEASE)
		game.Keys[key] = 0;
}

/**
 * Handle the mouse clicks through glfw.
 *
 * @param window A pointer to the GLFW window object used to display the game.
 * @param key The GLFW code for the button which has been pressed.
 * @param scancode
 * @param mods
 */
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		game.Keys[0] = 1;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		game.Keys[0] = 0;
}

/**
 * main entry point for the software.
 *
 */
int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		printf("Error during initilaization");
		glfwTerminate();
		return 1;
	}

	global.SetlastTime(glfwGetTime());

	// Setup properties for GLFW window
	// Set openGL version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Pool Game", NULL, NULL);

	if (!window)
	{
		printf("Window creation failed");
		glfwTerminate();
		return 1;
	}

	// Set GLEW context to current window
	glfwMakeContextCurrent(window);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	//Enable alpha for textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Check for initialization errors
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	// Initalize the game
	game.init(window);

	// Loop until window closed
	while (!glfwWindowShouldClose(window))
	{
		//update deltatime
		global.SetDeltaTime(glfwGetTime());

		// Get user input events and handle using mouse and key functions
		glfwPollEvents();
		mouseInput(window, &game);
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// First run the update loop to handle all user input and update state
		game.Update();

		// secondly run the render loop to render all correct visuals
		game.Render();

		glfwSwapBuffers(window);
	}

	return 0;
}
