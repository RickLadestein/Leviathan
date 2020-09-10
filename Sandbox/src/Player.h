#pragma once
#include "Leviathan.h"
#include "glm/glm.hpp"
#include <memory>

#define MAX_HORIZONTAL_PLAYER_VELOCITY 50
#define MAX_VERTICAL_PLAYER_VELOCITY 100

class Player;

enum class PlayerStateIdentifier {
	NONE,
	FLYING,
	WALKING,
	FALLING,
	SWIMMING
};

class PlayerState {
public:
	PlayerState() { this->player = nullptr; this->identifier = PlayerStateIdentifier::NONE; this->horizontal_movement_speed = 1.0; this->vertical_movement_speed = 1.0f; };
	PlayerStateIdentifier GetPlayerState() { return this->identifier; }
	virtual void MoveForeward(float frametime) { return; }
	virtual void MoveBackward(float frametime) { return; }
	virtual void MoveLeft(float frametime) { return; }
	virtual void MoveRight(float frametime) { return; }
	virtual void MoveUp(float frametime) { return; }
	virtual void MoveDown(float frametime) { return; }


protected:
	inline void Move(glm::vec3 move) { if (player) { player->Translate(move); } }
	double horizontal_movement_speed;
	double vertical_movement_speed;
	PlayerStateIdentifier identifier;
	Player* player;
};


class FlyingState : public PlayerState {
public:
	FlyingState(Player* p) { this->player = p; this->identifier = PlayerStateIdentifier::FLYING; }
	void MoveForeward(float frametime);
	void MoveBackward(float frametime);
	void MoveLeft(float frametime);
	void MoveRight(float frametime);
	void MoveUp(float frametime);
	void MoveDown(float frametime);
};

class FallingState : public PlayerState {
public:
	FallingState(Player* p) { this->player = p; this->identifier = PlayerStateIdentifier::FALLING; }
	void MoveForeward(float frametime);
	void MoveBackward(float frametime);
	void MoveLeft(float frametime);
	void MoveRight(float frametime);
	void MoveUp(float frametime);
	void MoveDown(float frametime);
};

class WalkingState : public PlayerState {
public:
	WalkingState(Player* p) { this->player = p; this->identifier = PlayerStateIdentifier::WALKING; }
	void MoveForeward(float frametime);
	void MoveBackward(float frametime);
	void MoveLeft(float frametime);
	void MoveRight(float frametime);
	void MoveUp(float frametime);
	void MoveDown(float frametime);
};

class SwimmingState : public PlayerState {
public:
	SwimmingState(Player* p) { this->player = p; this->identifier = PlayerStateIdentifier::SWIMMING; }
	void MoveForeward(float frametime);
	void MoveBackward(float frametime);
	void MoveLeft(float frametime);
	void MoveRight(float frametime);
	void MoveUp(float frametime);
	void MoveDown(float frametime);
};

class Player {
	friend class PlayerState;
private:
	glm::vec3 position;
	glm::vec3 velocity;

	std::shared_ptr<Camera>camera;
	PlayerState state;

	void CheckVelocity();
public:
	Player();
	Player(glm::vec3 position);
	Player(glm::vec3 position, glm::vec3 looking);
	

	void SetState(PlayerState& state);
	PlayerStateIdentifier GetState();
	void Translate(glm::vec3& move);
	void Rotate(glm::vec3& rotation);
	void AddVelocity(glm::vec3& velocity);

};