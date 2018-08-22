#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "World.hpp"
#include "Model.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "Particle.hpp"

#define N 128

//#include "./CUDA/kernel.hpp"

const uint32_t WINDOW_HEIGHT = 1080; //1080
const uint32_t WINDOW_WIDTH = 1920;  //1920
//const uint32_t WINDOW_HEIGHT  = 600;
//const uint32_t WINDOW_WIDTH = 800;
const float WINDOW_FPS = 60;
const char *WINDOW_TITLE = "OpenGL Renderer";
World *world;

static float gCurerntTime = 0;
static float gDeltaTime = 0;
static float gLastTime = 0;
static float gCurrentFPS = 0;

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	world->cam->resize(width, height);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	world->cam->updateDolly(yoffset);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			world->cam->startRotation(xpos, ypos);
		}
		else if (action == GLFW_RELEASE)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			world->cam->endRotation(xpos, ypos);
		}
	}
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	world->cam->updateMousePos(xpos, ypos);
}

int main()
{

	//cudaFunc();

	// GLEW, GLFW init...
	if (!glfwInit())
	{
		cerr << "Failed to initialize GLFW" << endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (window == NULL)
	{
		cerr << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// callback here
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// glfwSetKeyCallback(window, key_callback);

	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;

	glClearColor(156 / 255.0f, 167 / 255.0f, 186 / 255.0f, 1);



	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); 
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); 
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	//glDisable(GL_COLOR_MATERIAL);
	glLoadIdentity();
	// Init end.

	ParticleSystem* ps = new ParticleSystem{};
	
	vector<Particle> particles;
	for (int i = -N/2; i< N/2; i++) {
		for (int j = -N/2; j<N/2; j++) {
			for (int k = -N/2 ; k < N/2 ; k++) {
				particles.push_back(Particle{glm::vec3(i,j,k)});
			}
			
		}
	}
	ps->initParticles(particles);

	Shader *shader = new Shader{"vert.glsl", "frag.glsl"};

	world = new World{};
	world->worldShader.push_back(shader);
	world->particleSystem = ps;
	
	world->initPhysics();
	gCurerntTime = glfwGetTime();
	gDeltaTime = gCurerntTime - gLastTime;
	gLastTime = gCurerntTime;
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world->updatePyhsics(gDeltaTime);
		world->drawModel();
		world->drawParticle();

		glfwSwapBuffers(window);
		glfwPollEvents();

		// frame control
		gCurerntTime = glfwGetTime();
		gDeltaTime = gCurerntTime - gLastTime;
		gLastTime = gCurerntTime;

		if (gDeltaTime <= (1 / WINDOW_FPS))
		{
			this_thread::sleep_for(chrono::duration<float>(1 / WINDOW_FPS));
		}
		gCurrentFPS = 1 / gDeltaTime;

		//cout << "Current FPS : " << gCurrentFPS << endl;
	}

	glfwTerminate();
	return 0;
}
