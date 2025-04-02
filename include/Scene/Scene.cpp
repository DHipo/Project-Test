#include "Scene.h"

void Scene::Init() {
    // Initialize scene properties, load resources, etc.
    SDL_Log("Scene initialized.");
    m_viewport = {0, 0, Game::settings->winSize.x, Game::settings->winSize.y};
}

void Scene::Update() {
    // Update scene logic, entities, etc.
    SDL_Log("Scene updated.");
}

void Scene::Render() {
    // Render scene elements
    SDL_SetRenderDrawColor(Game::renderer, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
    SDL_RenderFillRect(Game::renderer, &m_viewport); // Fill the viewport with the background color

    Game::displayText("DEFAULT SCENE", {0, 0, 200, 50}, {255, 255, 255, 255}); // Example text rendering

    SDL_Log("Scene rendered.");
}