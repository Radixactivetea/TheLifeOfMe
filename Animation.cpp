#include "Animation.h"
#include "src/Model.h"

Model *background, *character, *car, *cat, *gold, *monsta, *box, *thinkBubble;

void Animation::initGLFW()
{
    	//INIT GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Animation::initWindow(const char *title, bool resizable)
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);

    this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

    if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

    glfwMakeContextCurrent(this->window);
    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(this->window, Animation::framebuffer_resize_callback);
}

void Animation::initGlEW()
{
    //INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Animation::initOpenGL()
{
    glEnable(GL_DEPTH_TEST);  

    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
}

void Animation::initShaders()
{
    this->shader = new Shader("src/vertex_core.glsl", "src/fragment_core.glsl");
}

void Animation::initModel()
{

    stbi_set_flip_vertically_on_load(true);
    background = new Model ("Model/Background/Background.obj");
    character = new Model ("Model/Character/Character.obj");
    car = new Model ("Model/Car/Car.obj");
    cat = new Model ("Model/Cat/Cat.obj");
    gold = new Model ("Model/Money/Gold.obj");
    monsta = new Model ("Model/Monsta/Monsta.obj");
    box = new Model ("Model/Box/Box.obj");
    thinkBubble = new Model ("Model/Thinking Bubble/Thinking.obj");
}

void Animation::initCamera()
{
    this->camera = new Camera (glm::vec3(0.0f, 0.0f, 3.0f));
    this->lastX = this->WINDOW_WIDTH / 2.0f;
    this->lastY = this->WINDOW_HEIGHT / 2.0f;
    this->firstMouse = true;
}
void Animation::initLighting()
{
    this->shader->use();
    this->lightDirection = glm::vec3(0.5f, -0.8f, -1.0f);
    this->shader->setVec3("lightDirection", lightDirection);
    this->lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // Set the light color
    this->shader->setVec3("lightColor", lightColor);
}

void Animation::initCharacter()
{
    this->modelcharacter = glm::translate(this->modelcharacter, glm::vec3(-6.0f, -2.8f, 0.0f));
    this->modelcharacter = glm::scale(this->modelcharacter, glm::vec3(1.0f, 1.0f, 1.0f));
}


void Animation::initBox()
{
    this->modelbox = glm::translate(this->modelbox, glm::vec3(8.0f, -3.0f, 4.5f));
    this->modelbox = glm::scale(this->modelbox, glm::vec3(0.5f, 0.5f, 0.5f));
    this->modelbox = glm::rotate(this->modelbox, 35.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Animation::initThinkingBubble()
{
    this->modelbubble = glm::translate(this->modelbubble, glm::vec3(7.0f, 3.0f, 4.5f));
    this->modelbubble = glm::scale(this->modelbubble, glm::vec3(0.4f, 0.4f, 0.4f));
}

void Animation::initImagination()
{
    this->modelcar = glm::translate(this->modelcar, glm::vec3(0.0f, 0.0f, 0.0f));
    this->modelcar = glm::scale(this->modelcar, glm::vec3(0.2f, 0.2f, 0.2f));

    this->modelmoney = glm::translate(this->modelmoney, glm::vec3(0.0f, 0.0f, 0.0f));
    this->modelmoney = glm::scale(this->modelmoney, glm::vec3(0.5f, 0.5f, 0.5f));

    this->modelmonsta = glm::translate(this->modelmonsta, glm::vec3(0.0f, -0.5f, 0.0f));
    this->modelmonsta = glm::scale(this->modelmonsta, glm::vec3(0.5f, 0.5f, 0.5f));
}

void Animation::initCat()
{
    this->modelcat = glm::translate(this->modelcat, glm::vec3(8.0f, -6.0f, 5.5f));
    this->modelcat = glm::scale(this->modelcat, glm::vec3(1.5f, 1.5f, 1.5f));
}


//Constructor and Destructormodel
Animation::Animation(const char *title,
                     const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
                     const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
                     bool resizable)
    : WINDOW_WIDTH(WINDOW_WIDTH),
      WINDOW_HEIGHT(WINDOW_HEIGHT),
      GL_VERSION_MAJOR(GL_VERSION_MAJOR),
      GL_VERSION_MINOR(GL_VERSION_MINOR)
{
    this->window = nullptr;
    this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;



    this->initGLFW();
    this->initWindow(title, resizable);
    this->initGlEW();
    this->initOpenGL();
	this->initShaders();
    this->initModel();
    this->initCamera();
    this->initLighting();
    
    this->initCharacter();
    this->initBox();
    this->initThinkingBubble();
    this->initImagination();
    this->initCat();
}


Animation::~Animation()
{
    glfwDestroyWindow(this->window);
	glfwTerminate();

    delete this->shader;
}

int Animation::getWindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

void Animation::setWindowShouldClose()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

void Animation::updateCamera()
{
}

void Animation::updateKeyboardInput()
{
	//Window
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

    //Camera
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
        this->camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
        this->camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
        this->camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
        this->camera->ProcessKeyboard(RIGHT, deltaTime);

    //Thinking Bubble
    if (glfwGetKey(this->window, GLFW_KEY_0) == GLFW_PRESS)
    {
        this->bubbleOn = true;
        this->zoom = true;
    }
    if (glfwGetKey(this->window, GLFW_KEY_8) == GLFW_PRESS)
        this->zoomBubble = true;
    if (glfwGetKey(this->window, GLFW_KEY_9) == GLFW_PRESS)
    {
        this->zoomBubble = false;
        this->zoomBox = true;
    }
        
    
    //What inside the box
    if (glfwGetKey(this->window, GLFW_KEY_1) == GLFW_PRESS)
        this->inside = 1;
    if (glfwGetKey(this->window, GLFW_KEY_2) == GLFW_PRESS)
        this->inside = 2;
    if (glfwGetKey(this->window, GLFW_KEY_3) == GLFW_PRESS)
        this->inside = 3;
    if (glfwGetKey(this->window, GLFW_KEY_4) == GLFW_PRESS)
        this->inside = 4;

    //Stop the cat
    if (glfwGetKey(this->window, GLFW_KEY_P) == GLFW_PRESS)
        this->catUp = 1;
}

void Animation::updateCharacter()
{
    if (glfwGetKey(this->window, GLFW_KEY_K) == GLFW_PRESS)
        this->modelcharacter = glm::translate(this->modelcharacter, glm::vec3(0.0f, 0.0f, 0.006f));
    if (glfwGetKey(this->window, GLFW_KEY_L) == GLFW_PRESS)
        this->modelcharacter = glm::translate(this->modelcharacter, glm::vec3(0.006f, 0.0f, 0.0f));
}

void Animation::updateCat()
{
    if(this->catUp != 1)
        this->modelcat = glm::translate(this->modelcat, glm::vec3(0.0f, 0.0001f * currentFrame, 0.0f));  
}


void Animation::renderCharacter()
{
    this->shader->setMat4("model", this->modelcharacter);
    character->Draw(*shader);
}

void Animation::renderBox()
{
    this->shader->setMat4("model", this->modelbox);
    box->Draw(*shader);
}

void Animation::renderBubble()
{
    if (this->bubbleOn == true)
    {
        this->shader->setMat4("model", modelbubble);
        thinkBubble->Draw(*shader);
    }   
}

void Animation::renderImagine()
{
    //car
    if (this->inside == 1)
    {
        this->modelcar = glm::rotate(this->modelcar, -0.007f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->shader->setMat4("model", this->modelcar);
        car->Draw(*shader);
    }
    //money
    if (this->inside == 2)
    {
        this->modelmoney = glm::rotate(this->modelmoney, -0.007f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->shader->setMat4("model", this->modelmoney);
        gold->Draw(*shader);    
    }
    //monster
    if (this->inside == 3)
    {
        this->modelmonsta = glm::rotate(this->modelmonsta, -0.007f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->shader->setMat4("model", this->modelmonsta);
        monsta->Draw(*shader);
    }  
}

void Animation::renderCat()
{
    this->shader->setMat4("model", this->modelcat);
    cat->Draw(*shader);
}


void Animation::update()
{
    // per-frame time logic
    // --------------------
    this->currentFrame = static_cast<float>(glfwGetTime());
    this->deltaTime = currentFrame - lastFrame;
    this->lastFrame = currentFrame;

    glfwPollEvents();
	this->updateKeyboardInput(); 

    this->updateCharacter();
}

void Animation::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->shader->use();

    if(this->zoomBox == true && this->zoomBubble == false)
    {
        glm::mat4 projection = glm::perspective(glm::radians(this->camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        this->shader->setMat4("projection", projection);
        glm::mat4 view2 = glm::lookAt(glm::vec3(8.0f, -1.9f, 9.0f), glm::vec3(8.0f, -1.9f, 4.5f), glm::vec3(0.0f, 1.0f, 0.0f));
        this->shader->setMat4("view", view2);

        this->updateCat();
        this->renderCat();
    }else if(this->zoom == true)
    {
        glm::mat4 view3 = this->camera->GetViewMatrix3();
        this->shader->setMat4("view", view3);
    }
    else
    {
        glm::mat4 projection = glm::perspective(glm::radians(this->camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = this->camera->GetViewMatrix();
        this->shader->setMat4("projection", projection);
        this->shader->setMat4("view", view);
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f)); // Translate it to the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));     // Scale it if necessary
    this->shader->setMat4("model", model);
    background->Draw(*shader);

    this->renderCharacter();

    this->renderBox();

    this->renderBubble();


    if(this->zoomBubble == true)
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 projection = glm::perspective(glm::radians(this->camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = this->camera->GetViewMatrix2();
        this->shader->setMat4("projection", projection);
        this->shader->setMat4("view", view);
        
        this->renderImagine();
    }

    

    

	//End Draw
	glfwSwapBuffers(this->window);
}

void Animation::framebuffer_resize_callback(GLFWwindow *window, int fbW, int fbH)
{
    glViewport(0, 0, fbW, fbH);
}
