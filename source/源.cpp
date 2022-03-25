#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <direct.h>
#include <queue>

#include "../include/shader_m.h"
#include "../include/Role.h"
#include "../include/model.h"
#include "../include/parameter.h"
#include "../include/Scene.h"
#include "../include/mySound.h"

#include <iostream>

void init_glfw_glad(GLFWwindow *&window_);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

mySoundEngline Sound;

// camera
Role camera(glm::vec3(1, 1.3, -5));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//spotlight
Scene *globalScene;
int spotTime=0;

int main()
{
     

    GLFWwindow *window = NULL;
    init_glfw_glad(window);
    if (!window) //创建窗口失败
    {
        cout << "init glfw and glad failed";
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    //stbi_set_flip_vertically_on_load(true);
    cout << "start load models..." << endl;
    straight_model1 = new Model(string("resources/objects/straight/straight1.obj"));
    straight_model = new Model(string("resources/objects/straight/straight.obj"));
    cornerL_model = new Model(string("resources/objects/cornerL/corner.obj"));
    cornerR_model = new Model(string("resources/objects/cornerR/corner.obj"));
    stairU_model = new Model(string("resources/objects/stairU/stair.obj"));
    stairD_model = new Model(string("resources/objects/stairD/stair.obj"));
    cout << "corridor done!" << endl;
    lamp_model = new Model(string("resources/objects/lamp/lamp.obj"));
    cout << "lamp done!" << endl;
    paint_model = new Model(string("resources/objects/paint/paint.obj"));
    paint_model1 = new Model(string("resources/objects/paint1/paint1.obj"));
    paint_model2 = new Model(string("resources/objects/paint2/paint2.obj"));
    paint_model3 = new Model(string("resources/objects/paint3/paint3.obj"));
    paint_model4 = new Model(string("resources/objects/paint4/paint4.obj"));
    paint_model5 = new Model(string("resources/objects/paint5/paint5.obj"));
    cout << "paint done!" << endl;
    table_model = new Model(string("resources/objects/table/table.obj"));
    cout << "table done!" << endl;
    horse_model = new Model(string("resources/objects/horse/horse.obj"));
    cout << "horse done!" << endl;
    ghost_model= new Model(string("resources/objects/ghost/ghost.obj"));
    cout << "ghost done!" << endl;
    //bookcase_model = new Model(string("resources/objects/bookcase/bookcase.obj"));

    corridor_shader = new Shader("./source/shaders/corridor.vs", "./source/shaders/corridor.fs");
    lamp_shader = new Shader("./source/shaders/lamp.vs", "./source/shaders/lamp.fs");
    paint_shader = new Shader("./source/shaders/paint.vs", "./source/shaders/paint.fs");

    paintList.push_back(paint_model1);
    paintList.push_back(paint_model2);
    paintList.push_back(paint_model3);
    paintList.push_back(paint_model4);
    paintList.push_back(paint_model5);
    paintList.push_back(paint_model);

	Scene scene(&camera);
    globalScene = &scene;

    Sound.play2D("resources/musics/background.mp3", 1);

    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*
        cameraPos.push(camera.Position);
        if (ghostPos != cameraPos.front())
        {
            ghost.model = glm::translate(ghost_model, cameraPos.front());
            cameraPos.pop();
        }
        */

        scene.render(); //渲染整个场景
        scene.updateCorridor();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Sound.playFewSecond("resources/musics/footstep.mp3", 0.5);
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Sound.playFewSecond("resources/musics/footstep.mp3", 0.5);
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Sound.playFewSecond("resources/musics/footstep.mp3", 0.5);
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Sound.playFewSecond("resources/musics/footstep.mp3", 0.5);
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (spotTime > 50)
			spotTime = 0;
		if (!spotTime)
		{
			extern bool spotLightOff;
			spotLightOff = 1 - spotLightOff;
			Sound.play2D("resources/musics/spotlight.mp3", 0);
		}
	}
	spotTime++;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void init_glfw_glad(GLFWwindow *&window_)
{
    /*打印当前路径
    char buffer[256];
    char* val = _getcwd(buffer, sizeof(buffer));
    if (val) {
        std::cout << buffer << std::endl;
    }
    */
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Horror Corridor", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        window_ = NULL;
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        window_ = NULL;
        return;
    }
    window_ = window;
}
