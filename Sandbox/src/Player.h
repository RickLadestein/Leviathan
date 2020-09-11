#pragma once
#include "Leviathan.h"
#include "glm/glm.hpp"
#include <memory>

#define MAX_HORIZONTAL_PLAYER_VELOCITY 50
#define MAX_VERTICAL_PLAYER_VELOCITY 100

enum class PlayerStateIdentifier {
	NONE,
	FLYING,
	WALKING,
	FALLING,
	SWIMMING
};

class PlayerState {
public:
	PlayerState() { this->identifier = PlayerStateIdentifier::NONE; this->horizontal_movement_speed = 100.0f; this->vertical_movement_speed = 100.0f; };
	inline glm::vec3 GetMovementModifiers() { return glm::vec3(horizontal_movement_speed, vertical_movement_speed, horizontal_movement_speed); }
	PlayerStateIdentifier GetPlayerState() { return this->identifier; }
	float horizontal_movement_speed;
	float vertical_movement_speed;

protected:
	PlayerStateIdentifier identifier;
};


class FlyingState : public PlayerState {
public:
	FlyingState() { 
		this->identifier = PlayerStateIdentifier::FLYING;
	}
};

class FallingState : public PlayerState {
public:
	FallingState() { 
		this->identifier = PlayerStateIdentifier::FALLING; 
	}
};

class WalkingState : public PlayerState {
public:
	WalkingState() { 
		this->identifier = PlayerStateIdentifier::WALKING; 
	}
};

class SwimmingState : public PlayerState {
public:
	SwimmingState() { 
		this->identifier = PlayerStateIdentifier::SWIMMING; 
	}
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
	std::weak_ptr<Camera> GetCamera();
	inline glm::vec3 GetPosition() { return this->position; }


	void MoveForeward(float frametime);
	void MoveBackward(float frametime);
	void MoveLeft(float frametime);
	void MoveRight(float frametime);
	void MoveUp(float frametime);
	void MoveDown(float frametime);


};