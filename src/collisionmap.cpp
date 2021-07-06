#include "headers/collisionmap.hpp"
#include "headers/sprite.hpp"
CollisionMap::CollisionMap(GLubyte *imageData, int imgWidth, int imgHeight, std::vector<std::shared_ptr<SceneObject>> &objects, Game *game)
{
	width = imgWidth;
	height = imgHeight;
	for (int y = imgHeight; y > 0; y--)
	{
		for (int x = 0; x < imgWidth; x++)
		{
			size_t base = (x + imgWidth * y);
			if (imageData[base])
			{
				colliders.insert({{x, y }, (bool)imageData[base]});
			}
		}
	}
	int a = 1;
}

CollisionDirection CollisionMap::checkCollision(glm::vec2 oldPos, glm::vec2 newPos)
{
	bool collided = false;
	for (auto &&it : colliders)
	{
		// AABB collision detection
		if
		(newPos.x < it.first.first + 1 &&
		 newPos.x + 1 > it.first.first &&
		 newPos.y < it.first.second + 0.75 &&
		 newPos.y + 0.75 > it.first.second)
		{
			collided = true;
			break;
		}
	}
	if (collided)
	{
		glm::vec2 posDiff = oldPos - newPos;
		if (posDiff.x > 0) return CollisionDirection::Left;
		if (posDiff.y > 0) return CollisionDirection::Down;
		if (posDiff.x < 0) return CollisionDirection::Right;
		if (posDiff.y < 0) return CollisionDirection::Up;
	}
	return CollisionDirection::None;
}