#pragma once

#include <glm/glm.hpp>
#include "stb_image.h"

class Game;
extern Game *game;

enum CollisionDirection
{
    None,
    Up,
    Down,
    Left,
    Right
};
