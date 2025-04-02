#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "..\Game\Game.h"
#include "..\Utils.h"

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void Init();
    void Update();
    void Render();
    void HandleEvents();

private:
    // Add any common properties or methods for all scenes here
    // For example, a scene name, background color, etc.
    std::string m_name;
    SDL_Color m_backgroundColor = {0, 0, 0, 255}; // Default to black
    SDL_Rect m_viewport; // Viewport for the scene
};

#endif