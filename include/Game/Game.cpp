#include "Game.h"
#include "..\Scene\Scene.h"

Game::Game() { std::cout << "Game object created. Now you must initialize it with the init method." << std::endl; }
Game::~Game() { std::cout << "Game object destruct" << std::endl; }

bool Game::Init(const char *title, int xpos, int ypos, int w, int h, int _FrameRate, uint32_t flags)
{
	bool status = true;
	std::cout << "Initializing sub-systems" << std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		LOG_ERROR(SDL_GetError());
		status = false;
	}

	std::cout << "Creating window..." << std::endl;
	m_window = SDL_CreateWindow(title, xpos, ypos, w, h, flags);
	if (!m_window){
		status = false;
		LOG_ERROR("Failed creating window...");
	}

	std::cout << "Creating renderer..." << std::endl;
	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED); 
	if (!renderer){
		status = false;
		LOG_ERROR("Failed creating renderer...");
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	std::cout << "Creating surface..." << std::endl;
	m_surface = SDL_GetWindowSurface(m_window);
	if (!m_surface){
		status = false;
		LOG_ERROR( "Failed creating surface...");
	}

	std::cout << "Intializing text system..." << std::endl;
	if (TTF_Init() < 0){
		status = false;
		LOG_ERROR("TTF initialization failed. ");
	}

	m_font = TTF_OpenFont("./res/fonts/HackRegularNerdFontCompleteMono.ttf", 24);
	if (!m_font)
		LOG_ERROR("Failed to open font.");

	// All passed
	std::cout << "----------- ALL DONE -----------" << std::endl;
	m_event = new SDL_Event();
    SDL_GetWindowSize(m_window, &Game::settings->winSize.x, &Game::settings->winSize.y);
	m_framerate = 1000.0f / _FrameRate;
	m_running = status;
	return status;
};

// Manejador de eventos
void Game::HandleEvents()
{
	SDL_PollEvent(m_event);

	switch (m_event->type)
	{
	case SDL_QUIT:
		m_running = false;
		break;
	case SDL_KEYDOWN:
		m_keys[m_event->key.keysym.sym] = true;
		break;
	case SDL_KEYUP:
		m_keys[m_event->key.keysym.sym] = false;
		break;
	case SDL_MOUSEMOTION:
		m_mouse.pos = {m_event->motion.x, m_event->motion.y};
		break;
	case SDL_MOUSEBUTTONDOWN:
		m_mouse.button = m_event->button.button;
		break;
	case SDL_MOUSEBUTTONUP:
		m_mouse.button = 0;
		break;
	default:
		break;
	}
}

/// @brief Display objects on the screen
/// @param none
/// @returns nothing
void Game::Renderer()
{
	SDL_RenderClear(renderer);

	if (Game::currentScene != nullptr) Game::currentScene->Render();

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderPresent(renderer);
}

/// @brief Clear the main objects and quit the program with a output message.
/// @param none
/// @returns nothing
void Game::Clear()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_window);
	TTF_CloseFont(m_font);
	TTF_Quit();
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

/// @brief  Function to update the all things that must update.
/// @param none
/// @returns nothing
void Game::Update()
{
	if (Game::currentScene == nullptr) {
		SDL_Log("No scene loaded, cannot update.");
		return; // No scene loaded
	}
	Game::currentScene->Update();
}

///	Main while of the game
/// @param none
/// @returns nothing
void Game::Run()
{
	
	while (m_running)
	{
		m_time.p_start = SDL_GetPerformanceCounter();
		m_time.t_start = SDL_GetTicks();

		this->HandleEvents();
		m_time.deltaTime = double(m_time.t_start - m_time.t_end) / 1000.f;

		this->Update();
		this->Renderer();
		m_time.p_end = SDL_GetPerformanceCounter();
		m_time.p_elapsed = m_time.p_end - m_time.p_start;

		m_time.t_end = SDL_GetTicks();
		m_time.t_elapsed = m_time.t_end - m_time.t_start;
		m_time.deltaTime = float(m_time.t_elapsed) / 1000.f;

		if (m_framerate > m_time.t_elapsed)
		{
			SDL_Delay(floor(m_framerate - m_time.t_elapsed));
		}

		//SDL_Log("DELTA TIME: %f", m_time.deltaTime);
	}

	this->Clear();
}

void Game::displayText(const std::string _text, const SDL_Rect _dest, const SDL_Color _color = {0,0,0, 255})
{
	SDL_Surface *text = TTF_RenderText_Solid(m_font, _text.c_str(), _color);
	if (!text)
		return;

	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text);

	SDL_RenderCopy(renderer, text_texture, NULL,  &_dest);
}