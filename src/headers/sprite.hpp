#pragma once

#include "gl.hpp"
#include "shader.hpp"
#include "sceneobject.hpp"
#include "globals.hpp"

class Game;

class Sprite : public SceneObject
{
public:
	Sprite(int width, int height, int mapIndex, Game *game, const char *vertexPath, const char *fragmentPath);
	Sprite(int width, int height, int mapIndex, Game *game, Shader shader);
	void render() override;
	void update() override;
	void collide();
	void move(float mag);
	void jump(float mag);
	void setTransform(glm::mat4 transform) override;
	void setTextureAtlas(GLuint atlasID) override;

private:
	void initBuffers();
	void initTextures();
	CollisionDirection checkCollision(glm::vec2 oldPos, glm::vec2 newPos);

private:
	int width;
	int height;
	int mapIndex;
	glm::vec2 facing;
	Shader shader;
	GLuint VAO;
};