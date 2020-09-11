#include "Player.h"
#include <iostream>


#pragma region Player

Player::Player()
{
	this->velocity = glm::vec3(0.0f);
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->camera = std::make_shared<Camera>();
	this->state = FlyingState();
}

Player::Player(glm::vec3 position)
{
	this->velocity = glm::vec3(0.0f);
	this->position = position;
	this->camera = std::make_shared<Camera>(position, glm::vec3(0.0f));
	this->state = FlyingState();
}

Player::Player(glm::vec3 position, glm::vec3 looking)
{
	this->velocity = glm::vec3(0.0f);
	this->position = position;
	this->camera = std::make_shared<Camera>(position, glm::vec3(0.0f));
	this->camera->Rotate(looking);
	this->state = FlyingState();
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

std::weak_ptr<Camera> Player::GetCamera()
{
	if (this->camera) {
		return this->camera;
	}
	return std::weak_ptr<Camera>();
}

void Player::MoveForeward(float frametime)
{
	glm::vec3 move = this->camera->GetForewardVector() * this->state.GetMovementModifiers();
	move *= frametime;
	move.y = 0;
	this->Translate(move);
}

void Player::MoveBackward(float frametime)
{
	glm::vec3 move = (-this->camera->GetForewardVector()) * this->state.GetMovementModifiers();
	move *= frametime;
	move.y = 0;
	this->Translate(move);
}

void Player::MoveLeft(float frametime)
{
	glm::vec3 move = (-this->camera->GetRightVector()) * this->state.GetMovementModifiers();
	move *= frametime;
	move.y = 0;
	this->Translate(move);
}

void Player::MoveRight(float frametime)
{
	glm::vec3 move = (this->camera->GetRightVector()) * this->state.GetMovementModifiers();
	move *= frametime;
	this->Translate(move);
}

void Player::MoveUp(float frametime)
{
	glm::vec3 move = glm::vec3(0.0f, 1.0f, 0.0f) * this->state.GetMovementModifiers();
	move *= frametime;
	this->Translate(move);
}

void Player::MoveDown(float frametime)
{
	glm::vec3 move = glm::vec3(0.0f, -1.0f, 0.0f) * this->state.GetMovementModifiers();
	move *= frametime;
	this->Translate(move);
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
