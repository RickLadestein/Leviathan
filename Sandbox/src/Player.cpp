#include "Player.h"



#pragma region Player

Player::Player()
{
	this->velocity = glm::vec3(0.0f);
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->camera = std::make_shared<Camera>();
	this->state = FlyingState(this);
}

Player::Player(glm::vec3 position)
{
	this->velocity = glm::vec3(0.0f);
	this->position = position;
	this->camera = std::make_shared<Camera>();
	this->state = FlyingState(this);
}

Player::Player(glm::vec3 position, glm::vec3 looking)
{
	this->velocity = glm::vec3(0.0f);
	this->position = position;
	this->camera = std::make_shared<Camera>();
	this->camera->Rotate(looking);
	this->state = FlyingState(this);
}

void Player::SetState(PlayerState& state)
{
	this->state = state;
}

PlayerStateIdentifier Player::GetState()
{
	return this->state.GetPlayerState();
}

void Player::Translate(glm::vec3& move)
{
	this->position += move;
	this->camera->SetPosition(this->position);
}
void Player::Rotate(glm::vec3& rotation)
{
	this->camera->Rotate(rotation);
}
void Player::AddVelocity(glm::vec3& velocity)
{
	this->velocity += velocity;
	this->CheckVelocity();
}

void Player::CheckVelocity()
{
	if (this->velocity.x > MAX_HORIZONTAL_PLAYER_VELOCITY) {
		this->velocity.x = MAX_HORIZONTAL_PLAYER_VELOCITY;
	}
	else if (this->velocity.x < -MAX_HORIZONTAL_PLAYER_VELOCITY) {
		this->velocity.x = -MAX_HORIZONTAL_PLAYER_VELOCITY;
	}

	if (this->velocity.z > MAX_HORIZONTAL_PLAYER_VELOCITY) {
		this->velocity.z = MAX_HORIZONTAL_PLAYER_VELOCITY;
	}
	else if (this->velocity.z < -MAX_HORIZONTAL_PLAYER_VELOCITY) {
		this->velocity.z = -MAX_HORIZONTAL_PLAYER_VELOCITY;
	}

	if (this->velocity.y > MAX_VERTICAL_PLAYER_VELOCITY) {
		this->velocity.y = MAX_VERTICAL_PLAYER_VELOCITY;
	}
	else if (this->velocity.y < -MAX_VERTICAL_PLAYER_VELOCITY) {
		this->velocity.y = -MAX_VERTICAL_PLAYER_VELOCITY;
	}
}
#pragma endregion
