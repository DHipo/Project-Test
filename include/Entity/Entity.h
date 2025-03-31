#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Utils.h"

class Entity
{
public:
	Entity(SDL_FRect, const char *);
	~Entity();

	virtual void Draw(SDL_Renderer*);
	virtual void Update(const Utils::TimeInter&);
	
	SDL_FRect* getPointerOfRect() { return &m_rect; };
	void setPosition();

protected:
	SDL_FRect m_rect;
	Utils::FVec2 m_position;
	SDL_Surface * m_image;
};

