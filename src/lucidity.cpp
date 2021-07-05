#include <iostream>

#include "headers/gl.hpp"
#include "headers/globals.hpp"
#include "headers/game.hpp"

void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}
void tick()
{
	game->tick();
}
int main()
{
	game = new Game(720, 720, "Lucidity");
	glfwSetErrorCallback(error_callback);
	
	// emscripten_set_main_loop(tick, -1, 1);
	while (!game->closed())
	{
		game->tick();
	}
	glfwTerminate();
	exit(EXIT_SUCCESS);
}