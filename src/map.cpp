#include "headers/map.hpp"
#include "headers/game.hpp"

Map::Map(int mapWidth, int mapHeight, int tilesetWidth, int tilesetHeight, int mapIndex, Game *game, Shader shader) : mapIndex(mapIndex), shader(shader), mapWidth(mapWidth), mapHeight(mapHeight), tilesetWidth(tilesetWidth), tilesetHeight(tilesetHeight)
{
	initBuffers();
	this->game = game;
	textureAtlas = 0;
	tileSize = 16;
}

Map::Map(int mapWidth, int mapHeight, int tilesetWidth, int tilesetHeight, int mapIndex, Game *game, const char *vertexPath, const char *fragmentPath) : mapIndex(mapIndex), mapWidth(mapWidth), mapHeight(mapHeight), tilesetWidth(tilesetWidth), tilesetHeight(tilesetHeight)
{
	initBuffers();
	this->game = game;
	shader.Compile(vertexPath, fragmentPath);
	textureAtlas = 0;
	tileSize = 16;
}

void Map::initBuffers()
{
	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f};

	GLuint VBO;

	glGenBuffers(1, &VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
}

void Map::setTransform(glm::mat4 transform)
{
	transform = glm::scale(transform, glm::vec3((static_cast<float>(mapWidth) / static_cast<float>(game->width)), (static_cast<float>(mapHeight) / static_cast<float>(game->height)), 1));
	transform = glm::translate(transform, {1.0, 1.0, 0.0});
	this->transform = transform;
}

void Map::setTextureAtlas(GLuint atlasID)
{
	textureAtlas = atlasID;
}

void Map::update()
{
	shader.SetMatrix4("transform", transform, true);
	shader.SetInteger("tileset", textureAtlas);
	shader.SetInteger("tiles", textureAtlas + 1);
	shader.SetVector2f("imgDims", {mapWidth, mapHeight});
	shader.SetVector2f("tilesetDims", {tilesetWidth / tileSize, tilesetHeight / tileSize});
}

void Map::render()
{
	glBindVertexArray(VAO);
	shader.Use();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}