#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ostream>
  

class Shader
{
    public:
        // the program ID
        unsigned int ID;
        // constructor reads and builds the shader
        Shader(const char* vertexPath, const char* fragmentPath);
        // use/activate the shader
        void use();
        void deleteShader();
        // utility uniform functions
        void setBool(const std::string &name, bool value);  
        void setInt(const std::string &name, int value);   
        void setFloat(const std::string &name, float value);

};
  
#endif