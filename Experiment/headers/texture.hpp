#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>
class Texture
{
    public:
        Texture(
            const char* path,
            bool fipiAxiosYOnLoad,
            int wrapModeS,
            int wrapModeT,
            int minFilter,
            int magFilter,
            int channel
        );
        unsigned int texture;

};
#endif