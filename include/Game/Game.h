#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "..\Utils.h"
#include "..\Entity\Entity.h"
#include "..\Global.h"

struct Settings {
	Utils::Vec2 winSize = {WINDOW_SIZE_W, WINDOW_SIZE_H};
	int maxFPS = 60;
	
	int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
};

class Game
{
public:
	Game();
	~Game();

	bool Init(const char* title, int xpos, int ypos, int w, int h, int maxframerate,uint32_t flags);

	void HandleEvents();
	void Run();
	void Update();
	void Clear();
	void Renderer();

	
	static void displayText(const std::string _text, const SDL_Rect _dest, const SDL_Color _color);
	
	void changeScene(Scene& scene) { currentScene = &scene; }
	void clearScene() { currentScene = nullptr; }
	inline bool GetRunningState() {return m_running;}
	static inline SDL_Window* GetWindow() {return m_window;}

	static Settings* settings;
	static SDL_Renderer* renderer;
private:
	bool m_running;
	Uint32 m_flags;
	float m_framerate;

	SDL_Surface* m_surface;
	static TTF_Font* m_font;
	
	// deberian ser estaticos para poder tener un acceso libre a ellos desde cualquier parte del programa
	static SDL_Window* m_window;
	static SDL_Event* m_event;
	static Utils::MouseInfo m_mouse;
	static std::map<SDL_Keycode, bool> m_keys;
	static Utils::TimeInter m_time;
	static Scene* currentScene;
};