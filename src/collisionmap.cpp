#include "headers/collisionmap.hpp"
#include "headers/sprite.hpp"
CollisionMap::CollisionMap(GLubyte *imageData, int imgWidth, int imgHeight, std::vector<std::shared_ptr<SceneObject>> &objects, Game *game)
{
	width = imgWidth;
	height = imgHeight;
	// for (int i = 3; i < imgWidth * imgHeight * 4; i+=4)
	// {
	// 	colliders.insert({{i % imgWidth, i / imgWidth}, imageData[i]});
	// // 	if(i < 50000 && i > 0 && imageData[i])
	// // 	{
	// // std::shared_ptr sprite = std::make_shared<Sprite>(60, 60, 0, game, "../shaders/sprite.vert", "../shaders/sprite.frag");
	// // 	sprite->pos = {i % imgWidth, i / imgWidth};
	// // 	// printf
	// 	printf("%i, %i\n", i % imgWidth, i / imgWidth);
	// // 	objects.push_back(sprite);
	// // 	}
	// }
	// for (int y = 0; y < imgHeight; y++)
	// {
	// 	for (int x = 0; x < imgWidth * 1; x+=1)
	// 	{
	// 		if (imageData[x + width * 1 * y])
	// 		{
	// 			printf("#");
	// 		}
	// 		else
	// 		{
	// 			printf(" ");
	// 		}
	// 	}
	// 	printf("\n");
	// }
	for (int y = imgHeight; y > 0; y--)
	{
		for (int x = 0; x < imgWidth; x++)
		{
			size_t base = (x + imgWidth * y);
			if (imageData[base])
			{
				colliders.insert({{x, y}, imageData[base]});
			}
			// printf("#");}
			// else{
			// 	printf(" ");
			// }
		}
		// printf("\n");
	}
	int a = 1;
}

bool CollisionMap::checkCollision(glm::ivec2 position)
{
	return colliders[{position.x, position.y}];
}