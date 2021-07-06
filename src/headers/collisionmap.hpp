#include <map>
#include <utility>
#include "gl.hpp"
#include <glm/glm.hpp>
#include <vector>
#include "sceneobject.hpp"
#include <memory>
#include "globals.hpp"

class CollisionMap
{
public:
    CollisionMap() = default;
    CollisionMap(GLubyte *imageData, int imgWidth, int imgHeight, std::vector<std::shared_ptr<SceneObject>> &objects, Game *game);
    CollisionDirection checkCollision(glm::vec2 oldPos, glm::vec2 newPos);

    int width;
    int height;

private:
    std::map<std::pair<int, int>, bool> colliders;
};