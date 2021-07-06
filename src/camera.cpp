#include "headers/camera.hpp"
#include "headers/game.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(Game *game) : game(game)
{
	transform = glm::ortho(0.0f,static_cast<float>(game->width)/static_cast<float>(game->height), 0.0f, 1.0f, -1.0f, 1.0f);
	pos = glm::vec2(0);
	vel = glm::vec2(0);
	acc = glm::vec2(0);
	scale = game->scale;

	auto map_dims = game->getMapDims();
	scaling_matrix = glm::scale(transform, {scale, scale, 0.0});
	translation_matrix = glm::mat4(1.0f);

	view_matrix = translation_matrix * scaling_matrix;
}

void Camera::update()
{
	auto map_dims = game->getMapDims();
	vel += acc;
	translation_matrix = glm::translate(translation_matrix, glm::vec3(vel.x / (static_cast<float>(game->width) / 2.0f), vel.y / static_cast<float>(game->height) / 2.0f, 0.0f));
	view_matrix = scaling_matrix * translation_matrix;
	
	pos += vel;
	vel *= 0.9;
	acc *= 0.3;
}

void Camera::move(glm::vec2 motion)
{
	vel += motion;
}

glm::mat4 Camera::getTransform()
{
	return view_matrix;
}