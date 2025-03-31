#include "Player.h"

Player::Player(SDL_FRect _rect, const char* _path, int _health)
	: Entity(_rect, _path)
{
	m_position = {_rect.x, _rect.y};
}

void Player::Update (const Utils::TimeInter& _time)
{
	velocityUpdate(_time);
	incrementPosition(m_velocity.x, m_velocity.y);
	if (m_mouse.button == SDL_BUTTON_LEFT) doAtack();
}

void Player::Draw(SDL_Renderer* _renderer)
{
	m_rect.x = m_position.x;
	m_rect.y = m_position.y;
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_RenderFillRectF(_renderer, &m_rect);
}

void Player::velocityUpdate(const Utils::TimeInter& _time) 
{
	// aceleration when the key is pressed
	Utils::Vec2 direction = {
		(-((int)(*this->m_keys)[SDLK_a]) + (int)(*this->m_keys)[SDLK_d]),
		(-((int)(*this->m_keys)[SDLK_w]) + (int)(*this->m_keys)[SDLK_s])
	};

	// deceleration when the key is not pressed
	if (direction.x == 0 && m_velocity.x != 0) m_aceleration.x = -1.2f * (m_velocity.x > 0 ? 1 : -1);
	else m_aceleration.x = 3.7f * direction.x;

	if (direction.y == 0 && m_velocity.y != 0) m_aceleration.y = -1.2f * (m_velocity.y > 0 ? 1 : -1);
	else m_aceleration.y = 3.7f * direction.y;

	m_velocity.y += _time.deltaTime * m_aceleration.y;
	m_velocity.x += _time.deltaTime * m_aceleration.x;
}

void Player::incrementPosition(int _x, int _y) 
{
	m_position = {
		m_position.x + m_velocity.x,
		m_position.y + m_velocity.y 
	};
}

void Player::doAtack() 
{
	std::cout << m_mouse.pos.x << " | " << m_mouse.pos.y << std::endl;
}