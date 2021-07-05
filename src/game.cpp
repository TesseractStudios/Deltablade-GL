#include "headers/sprite.hpp"
#include "headers/map.hpp"
#include "headers/game.hpp"
#include "headers/stb_image.h"
#include "headers/globals.hpp"
bool left = 0, right = 0, up = 0;
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT)
	{
		left = action;
	}
	if (key == GLFW_KEY_RIGHT)
	{
		right = action;
	}
	if (key == GLFW_KEY_UP)
	{
		up = action;
	}
}

Game::Game(int width, int height, std::string title) : camera()
{
	init(width, height, title);
	glfwSetKeyCallback(window, key_callback);
	scale = 16.0f;
	camera = Camera(this);
}

void Game::init(int width, int height, std::string title)
{
	// Try to initialize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// Try to create a window
	glfwWindowHint(GLFW_SAMPLES, 4);
	// glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GL_MAJOR_VERSION, 3);
	glfwWindowHint(GL_MINOR_VERSION, 1);
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
		exit(EXIT_FAILURE);

	// Load GL
	glfwMakeContextCurrent(window);
	gladLoadGL();

	// Set viewport
	glfwGetFramebufferSize(window, &this->width, &this->height);
	
	// Alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glClearColor(0.176, 0.204, 0.212, 1.0);

	stbi_set_flip_vertically_on_load(true);

	int imgWidth, imgHeight, tilesetWidth, tilesetHeight, nrChannels;
	GLubyte *data;

	// Load tileset
	data = stbi_load("../src/images/basic_tiles_big.png", &imgWidth, &imgHeight, &nrChannels, 0);
	tileset = loadTexture(data, imgWidth, imgHeight);
	stbi_image_free(data);
	tilesetWidth = imgWidth;
	tilesetHeight = imgHeight;

	// Load level map
	data = stbi_load("../src/images/another_map4.png", &imgWidth, &imgHeight, &nrChannels, 0);
	spriteSheet = loadTexture(data, imgWidth, imgHeight);
	stbi_image_free(data);
	// Generate collision map from level
	std::shared_ptr map = std::make_shared<Map>(imgWidth, imgHeight, tilesetWidth, tilesetHeight, 0, this, "../shaders/tilemap.vert", "../shaders/tilemap.frag");
	renderObjects.push_back(map);
	// Load collider map
	data = stbi_load("../src/images/another_map4B.png", &imgWidth, &imgHeight, &nrChannels, 1);
	collision_map = CollisionMap(data, imgWidth, imgHeight, renderObjects, this);

	// Load player texture
	data = stbi_load("../src/images/Blob.png", &imgWidth, &imgHeight, &nrChannels, 0);
	playerImg = loadTexture(data, imgWidth, imgHeight);
	stbi_image_free(data);
	// Create sprite for player
	std::shared_ptr sprite = std::make_shared<Sprite>(imgWidth, imgHeight, 0, this, "../shaders/sprite.vert", "../shaders/sprite.frag");
	renderObjects.push_back(sprite);
	player = sprite;

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	glfwSwapInterval(1);
}

GLuint Game::loadTexture(GLubyte *data, int imgWidth, int imgHeight)
{
	GLuint texture;
	glActiveTexture(GL_TEXTURE0 + textureCount++);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	return texture;
}

bool Game::closed()
{
	return glfwWindowShouldClose(window);
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int const rotation = glfwGetTime() * 100;


	for (auto &&i : renderObjects)
	{
		i->render();
	}

	glfwSwapBuffers(window);
}

void Game::update()
{
	// Follow player
	if(player->pos.x + (camera.pos.x) < 2.0f)
	{
		if(camera.pos.x + 0.1f <= 0.0f)
			camera.move({0.1f, 0.0});
	}
	else if(abs(player->pos.x + (camera.pos.x)) > ((static_cast<float>(width) / 2.0f)/ scale) - 2.0f)
	{
		if(camera.pos.x - 0.1f >= -(game->getMapDims().x))
			camera.move({-0.1f, 0.0});
	}

	// printf("%f, %f\n", player->pos.x, camera.pos.x);

	// glfwGetFramebufferSize(window, &this->width, &this->height);
	camera.update();
	for (auto &&i : renderObjects)
	{
		i->setTransform(camera.getTransform());
		i->update();
	}
}

void Game::input()
{
	glfwPollEvents();
	if (left)
	{
		game->player->move(-0.093);
	}
	if (right)
	{
		game->player->move(0.093);
	}
	if (up)
	{
		game->player->jump(0.5);
	}
}

void Game::tick()
{
	double time = glfwGetTime();
	double deltaTime = time - lastTime;
	if (deltaTime >= 1.0 / 60.0)
	{
		lastTime = time;
		draw();
		update();
		input();
	}
}

std::tuple<bool, bool, bool, bool> Game::checkCollision(glm::vec2 position, float radius)
{
	auto intPos = glm::ivec2(position);
	bool up = collision_map.checkCollision({position.x + radius, position.y});
	bool down = collision_map.checkCollision({position.x - radius, position.y});
	bool left = collision_map.checkCollision({position.x, position.y - radius});
	bool right = collision_map.checkCollision({position.x, position.y + radius});
	return {up, down, left, right};
}

glm::ivec2 Game::getMapDims()
{
	return {collision_map.width, collision_map.height};
}