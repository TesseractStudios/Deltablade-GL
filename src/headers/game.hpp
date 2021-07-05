#pragma once

#include <string>
#include <vector>
#include <memory>

#include "gl.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "sceneobject.hpp"
#include "sprite.hpp"
#include "collisionmap.hpp"

class Game
{

public:
	Game(int width, int height, std::string title);

public:
	void init(int width, int height, std::string title);
	void tick();

	void draw();
	void update();
	void input();
	glm::ivec2 getMapDims();

	bool closed();
	std::tuple<bool, bool, bool, bool> checkCollision(glm::vec2 position, float radius);

public:
	int width;
	int height;

	GLuint spriteSheet;
	GLuint playerImg;
	GLuint tileset;
	Camera camera;
	std::shared_ptr<Sprite> player;
	float scale;

private:
	GLuint loadTexture(GLubyte *data, int imgWidth, int imgHeight);

private:
	GLFWwindow *window;
	double lastTime = 0.0;
	int textureCount = 0;
	std::vector<std::shared_ptr<SceneObject>> renderObjects;
	CollisionMap collision_map;
};