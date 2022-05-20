#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "API/VertexBuffer.h"
#include "API/IndexBuffer.h"
#include "API/VertexArray.h"
#include "API/Shader.h"
#include "API/Renderer.h"

#include "GameFiles/Obstacle.h"
#include "GameFiles/Player.h"

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

float vy = 30.0f;
float gravity = 1.0f;
float jump_speed = 20.0f;

int frame = 500;

void space(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        vy = jump_speed;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(900, 700, "Grocery run", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, space);


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initializing glew */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "[Error]: Failed to initialize glew" << std::endl;
    }

    glm::mat4 proj = glm::ortho(0.0f, 900.0f, 0.0f, 700.0f);

    const char* backgrounds[] = {
        "Images/backgrounds/background1.jpg",
        "Images/backgrounds/background2.jpg",
        "Images/backgrounds/background3.jpg",
        "Images/backgrounds/background4.jpg",
    };

    int background_count = 4;
    int current_background = 0;

    GameObject* background = new GameObject(900.0f, 700.0f, backgrounds[current_background]);
    background->position = glm::vec3(450.0f, 350.0f, 0.0f);

    Player player(100.0f, 100.0f, "Images/tomato.jpg");
    Obstacles obstacles("Images/cucumber.jpg", 100.0f, 350.0f);

    player.position = glm::vec3(200.0f, 100.0f, 0.0f);


    srand(static_cast<unsigned int>(time(nullptr)));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Calculations here */
        if (player.CheckForCollision(obstacles))
        {
            frame = 500;
            vy = 30.0f;
            player.position = glm::vec3(200.0f, 100.0f, 0.0f);

            {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(500ms);
            }

            delete background;
            current_background++;

            if(current_background >= background_count)
                current_background = 0;

            background = new GameObject(900.0f, 700.0f, backgrounds[current_background]);
            background->position = glm::vec3(450.0f, 350.0f, 0.0f);
            obstacles.Reset();
        }

        if (frame >= 90)
        {
            obstacles.AddObstacle((float)(rand() % 300));
            frame = 0;
        }

        frame++;

        vy -= gravity;
        player.position.y += vy;

        /* Render here */
        Renderer::Clear();
        background->Render(proj);
        player.Render(proj);
        obstacles.Render(proj);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
