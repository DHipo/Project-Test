#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"

struct Camera {
    Utils::FVec2 position;
    Utils::FVec2 direction;
    Utils::FVec2 up;
    Utils::FVec2 right;
    float fov; // Field of view in degrees
    float nearPlane; // Near clipping plane distance
    float farPlane; // Far clipping plane distance
};

#endif