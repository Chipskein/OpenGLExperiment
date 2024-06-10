#include "texture.hpp"
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
Texture::Texture(
    const char* path,
    bool flipYOnLoad,
    int wrapModeS,
    int wrapModeT,
    int minFilter,
    int magFilter,
    int channel
)
{
    unsigned int t;
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flipYOnLoad);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    
    if (!data)
        std::cout << "Failed to load texture" << std::endl;

    glTexImage2D(GL_TEXTURE_2D, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    texture=t;
}