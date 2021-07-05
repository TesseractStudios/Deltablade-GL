#pragma once

#include "gl.hpp"
#include "shader.hpp"
#include "sceneobject.hpp"
class Game;

class Map : public SceneObject
{
public:
	Map(int mapWidth, int mapHeight, int tilesetWidth, int tilesetHeight, int mapIndex, Game *game, const char *vertexPath, const char *fragmentPath);
	Map(int mapWidth, int mapHeight, int tilesetWidth, int tilesetHeight, int mapIndex, Game *game, Shader shader);
	void render() override;
	void update() override;
	void setTransform(glm::mat4 transform) override;
	void setTextureAtlas(GLuint atlasID) override;

private:
	void initBuffers();
	void initTextures();

private:
	int mapWidth, tilesetWidth;
	int mapHeight, tilesetHeight;
	int tileSize;
	int mapIndex;
	Shader shader;
	GLuint VAO;
};