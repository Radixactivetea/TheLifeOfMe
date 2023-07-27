#pragma once

#include "src/libs.h"



class Animation
{
private:
//Variable
    //Window
    GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Camera
	Camera *camera;
	float lastX;
	float lastY;
	bool firstMouse;

	//Shaders
	Shader *shader;

	//Lighting
	glm::vec3 lightDirection;
	glm::vec3 lightColor;

	//Timing
	float currentFrame;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	glm::mat4 modelcharacter = glm::mat4(1.0f);
	glm::mat4 modelbox = glm::mat4(1.0f);
	glm::mat4 modelbubble = glm::mat4(1.0f);
	glm::mat4 modelcar = glm::mat4(1.0f);
	glm::mat4 modelmoney = glm::mat4(1.0f);
	glm::mat4 modelmonsta = glm::mat4(1.0f);
	glm::mat4 modelcat = glm::mat4(1.0f);

	bool bubbleOn = false;
	bool zoomBubble = false;
	bool zoomBox = false;
	bool zoom = false;
	int inside = 1;
	int catUp = 0;

//Function
    void initGLFW();
    void initWindow(const char* title, bool resizable);
    void initGlEW();
    void initOpenGL();
	
	void initShaders();

	void initModel();

	void initCamera();

	void initLighting();

	void initCharacter();
	void initBox();
	void initThinkingBubble();
	void initImagination();
	void initCat();

public:
//Contructor and Destructor
    Animation(
		const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable
	);
	virtual ~Animation();

//Accessors
    int getWindowShouldClose();

//Modifier
    void setWindowShouldClose();
    
//Functions
	//Updates
	void updateKeyboardInput();
	void updateCamera();
	void updateCharacter();
	void updateCat();
	
	//Render
	void renderCharacter();
	void renderBox();
	void renderBubble();
	void renderImagine();
	void renderCat();
    
	
	void update();
    void render();
	
    static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
};