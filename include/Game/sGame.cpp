#include "Game.h"

Scene* Game::currentScene = nullptr;

SDL_Window* Game::m_window = nullptr;

SDL_Event* Game::m_event = nullptr;
std::map<SDL_Keycode, bool> Game::m_keys;

Settings* Game::settings = new Settings();

TTF_Font* Game::m_font = nullptr;
SDL_Renderer* Game::renderer = nullptr;

Utils::MouseInfo Game::m_mouse = { 0,0, 0, 0 };
Utils::TimeInter Game::m_time = { 0,0,0,	0,0,0,	0};