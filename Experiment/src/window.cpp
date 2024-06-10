#include "window.hpp"
#include "globals.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void setup_GLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
    
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; 
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cam->Front  = glm::normalize(direction);
}

int setup_window_config(GLFWwindow *window, int width, int height)
{
    
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }    
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    gladLoadGL();
    return EXIT_SUCCESS;
}


Window::Window(int width, int height, const char* title)
{
    width = width;
    height = height;
    title = title;
    setup_GLFW();
    GLFWwindow* mwindow = glfwCreateWindow(width, height,title, nullptr, nullptr);
    if (mwindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        glfwTerminate();
    }
    int err=setup_window_config(mwindow,width,height);
    if (err==EXIT_FAILURE)
    {
        fprintf(stderr, "Failed to Initialize GLAD");
        glfwTerminate();
    }
    window=mwindow;
}

void Window::handle_input()
{
    //keyboard
    const float cameraSpeed = 2.5f * cam->deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->Pos += cameraSpeed * cam->Front;
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->Pos -= cameraSpeed * cam->Front;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->Pos -= glm::normalize(glm::cross(cam->Front, cam->Up)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->Pos += glm::normalize(glm::cross(cam->Front, cam->Up)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}