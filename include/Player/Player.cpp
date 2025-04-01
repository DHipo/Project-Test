#include "Player.h"

Player::Player(SDL_FRect _rect, const char* _path, int _health)
	: Entity(_rect, _path)
{
	m_position = {_rect.x, _rect.y};
	m_rect = _rect;
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
	if (direction.x == 0 && m_velocity.x != 0.f && m_aceleration.x != 0) m_aceleration.x = -.5f * (m_velocity.x > 0 ? 1 : -1);
	else m_aceleration.x = 3.7f * direction.x;

	if (direction.y == 0 && m_velocity.y != 0.f && m_aceleration.y != 0) m_aceleration.y = -.5f * (m_velocity.y > 0 ? 1 : -1);
	else m_aceleration.y = 3.7f * direction.y;

	m_velocity.y += _time.deltaTime * m_aceleration.y;
	m_velocity.x += _time.deltaTime * m_aceleration.x;

	// deceleration when the key is not pressed and the velocity is low
	if (direction.x == 0 && Utils::absolute(m_velocity.x) < 0.04f) m_velocity.x = 0;
	if (direction.y == 0 && Utils::absolute(m_velocity.y) < 0.04f) m_velocity.y = 0;

}

void Player::incrementPosition(float _x, float _y) 
{
	int width = 0, height = 0;
	SDL_GetWindowSize(Game::GetWindow(), &width, &height);
	// Check if the player is out of the screen
	if (m_position.x + _x < 0 || m_position.x + m_rect.w + _x > width) {
		m_position.x = 0 * (m_position.x + _x < 0) + (width - m_rect.w) * (m_position.x + m_rect.w + _x > width);
		m_velocity.x = 0; m_aceleration.x = 0;
	}
	if (m_position.y + _y < 0 || m_position.y + m_rect.h + _y > height) {
		m_position.y = 0 * (m_position.y + _y < 0) + (height - m_rect.h) * (m_position.y + m_rect.h + _y > height);
		m_velocity.y = 0; m_aceleration.y = 0;
	}

	m_position = {
		m_position.x + _x,
		m_position.y + _y 
	};
}

void Player::doAtack() 
{
	std::cout << m_mouse.pos.x << " | " << m_mouse.pos.y << std::endl;
}