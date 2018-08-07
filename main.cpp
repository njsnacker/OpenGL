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

#include "./CUDA/kernel.hpp"

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

	cudaFunc();

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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	//glDisable(GL_COLOR_MATERIAL);
	glLoadIdentity();
	// Init end.

	Model *cube = new Model{};
	cube->setVertices(vector<Vertex>{
		Vertex{glm::vec3(0.5, 0.5, 0.5), glm::vec2(0, 0)},
		Vertex{glm::vec3(-0.5, 0.5, 0.5), glm::vec2(0, 0)},
		Vertex{glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0, 0)},
		Vertex{glm::vec3(0.5, -0.5, 0.5), glm::vec2(0, 0)},
		Vertex{glm::vec3(0.5, 0.5, -0.5), glm::vec2(0, 0)},
		Vertex{glm::vec3(-0.5, 0.5, -0.5), glm::vec2(0, 0)},
		Vertex{glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0, 0)},
		Vertex{glm::vec3(0.5, -0.5, -0.5), glm::vec2(0, 0)}});

	cube->setIndices(vector<uint32_t>{
		0, 1, 2,
		0, 2, 3,
		4, 0, 3,
		4, 3, 7,
		5, 1, 0,
		5, 0, 4,
		6, 7, 3,
		6, 3, 2,
		1, 5, 6,
		1, 6, 2,
		6, 5, 4,
		6, 4, 7});
		
	cube->setupModel();
	//cube->addInstance(vector<glm::vec3>{glm::vec3(0,0,0)});

	Shader *shader = new Shader{"vert.glsl", "frag.glsl"};

	world = new World{};
	world->worldShader.push_back(shader);
	world->models.push_back(cube);
	

	{
		// /************* Asset loading Start... ****************************/
		// // set gun
		// world.m_fixed.push_back(Model("../Assets/wapon.dae"));
		// world.m_fixed[0].scale(0.2f);
		// world.m_fixed[0].rotate(glm::radians(-100.0f), glm::vec3(1, 0, 0));
		// world.m_fixed[0].rotate(glm::radians(190.0f), glm::vec3(0, 1, 0));
		// world.m_fixed[0].rotate(glm::radians(-10.0f), glm::vec3(0, 0, 1));
		// world.m_fixed[0].translate(glm::vec3(0.3f, -0.4f, -0.5f));
		// for (auto &itr : world.m_fixed) {
		// 	itr.update_meshes();
		// }

		// // main object
		// world.m_objects.push_back(Model("../Assets/monster.dae"));
		// world.m_objects[0].rotate(glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// world.m_objects.push_back(Model("../Assets/bullet.dae"));
		// world.m_objects[1].rotate(glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// world.m_objects.push_back(Model("../Assets/particle.dae"));
		// for (auto &itr : world.m_objects) {
		// 	itr.update_meshes();
		// }

		// // set terrarians
		// world.m_terrarians.push_back(Model("../Assets/plane.dae"));
		// world.m_terrarians.push_back(Model("../Assets/ship.dae"));
		// world.m_terrarians[1].scale(2.0f);
		// world.m_terrarians[1].rotate(glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// world.m_terrarians[1].translate(glm::vec3(0,30,0));
		// world.m_terrarians.push_back(Model("../Assets/sky.dae"));
		// for (auto &itr : world.m_terrarians) {
		// 	itr.update_meshes();
		// }

		// cout << "Asseets load end " << endl;
		// /********* Asset loading End... **********************************/

		//world.init_physics();
		//GL_btDebugDraw bulletDebugugger;
		//bulletDebugugger.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
		//world.m_dynamicsWorld->setDebugDrawer(&bulletDebugugger);
		//world.m_dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	}

	while (!glfwWindowShouldClose(window))
	{
		//cube->rotate(glm::vec3(1,1,1), 0.03);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// world.update_physics(g_delta_time);
		world->draw();

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
