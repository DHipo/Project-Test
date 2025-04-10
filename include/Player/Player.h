#pragma once
#include <SDL2/SDL.h>
#include "..\Entity\Entity.h"
#include "..\Utils.h"
#include "..\Game\Game.h"
#include "..\Global.h"

class Player : public Entity
{
private:
	std::map<SDL_Keycode, bool> * m_keys;
	unsigned int m_health;
	double m_attackRange = 200.f;
	Utils::FVec2 m_aceleration = {3.7, 3.7}, m_velocity = {0, 0};
	Utils::MouseInfo m_mouse = { {1,1} ,0 };

public: 
	Player(SDL_FRect,const char * , int );
	~Player();

	void Update(const Utils::TimeInter&) override;
	void Draw(SDL_Renderer*) override;

  	// This functions can be changed
	void velocityUpdate(const Utils::TimeInter&);
	void doAtack();
	void incrementPosition(float, float);

	// This functions give you access to the data of each elements like mouse and keyboard state
	void setKeys(std::map<SDL_Keycode, bool>& _keys) { m_keys = &_keys; };
	void setMousePosition(Utils::MouseInfo& _data) { m_mouse = _data; };
};

