#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "globals.h"
class Window
{
    public:
        GLFWwindow* window;
        int width;
        int height;
        const char* title;
        
        Window(int width, int height, const char* title);
        //methods
        void handle_input();
};
#endif