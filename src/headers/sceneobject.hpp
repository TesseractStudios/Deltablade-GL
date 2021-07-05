#pragma once
class Game;
class SceneObject
{
public:
	virtual void render(){}
	virtual void update(){}
	virtual void setTransform(glm::mat4 transform){}
	virtual void setTextureAtlas(GLuint atlasID){}

public:
	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;

protected:
	// glm::mat4 originalTransform = glm::mat4(1.0f);
	glm::mat4 transform = glm::mat4(1.0f);
	// glm::mat4 position = glm::mat4(1.0f);
	GLuint textureAtlas;
	Game* game;
};