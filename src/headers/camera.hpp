#pragma once

#include "globals.hpp"
class Game;
// typedef glm::mat4 Camera;
class Camera
{
public:
	Camera(Game *game);
	Camera() = default;
	void update();
	void move(glm::vec2 motion);
	glm::mat4 getTransform();

public:
	glm::mat4 transform = glm::mat4(1.0f);
	// glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;
	glm::vec2 pos;

private:
	Game *game;
	glm::mat4 translation_matrix;
	glm::mat4 scaling_matrix;
	glm::mat4 view_matrix;
	float scale;
};