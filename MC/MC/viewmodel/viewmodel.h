#pragma once
#ifndef VM_H_
#define VM_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"../view/Camera.h"
#include"Chunk.h"
#include"../view/stb_image.h"
#include"../model/Block.h"
#include<time.h>
#include<vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Map.h"
#include "../model/Player.h"
#include "../view/Text.h"

class ViewModel
{
private:
	static Camera* myCamera;
	static Map* myMap;
	static operateBlock changeBlock;
	static Player* myPlayer;
	static GLFWwindow* window;
	static int state;

	// settings
	static double deltaTime; // 当前帧与上一帧的时间差
	static double lastFrame; // 上一帧的时间
	static double lastX, lastY;
	static bool firstMouse;
public:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);
	static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	static GLFWwindow* createViewModel();
	static int run();
};

#endif