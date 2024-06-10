#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
struct Camera {
    glm::vec3 Pos;
    glm::vec3 Front;
    glm::vec3 Up;
    float deltaTime;
};
#endif