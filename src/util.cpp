#include "util.h"
#include <cmath>

std::pair<std::vector<float>, std::vector<unsigned int>>
genereteCirleVerticiesAndIndicies(Circle circle) {
  // each verticies is determined by trig, z position will be zero
  // for each triangle in ibo it will be first center, then prev point, and
  // current point stopping at resoultion which should represnet total
  // revolution

  std::vector<float> verticies;
  // 1 vec3 for center, and circle.resolution size verticies for other
  // verticies.reserve(1 + circle.resolution);
  //
  std::vector<unsigned int> indicies;
  // indicies.reserve(3 * circle.resolution);
  verticies.push_back(0.0f);
  verticies.push_back(0.0f);

  for (int i = 0; i < circle.resolution; i++) {
    float angle = (2.0f * PI * (float(i))) / float(circle.resolution);
    // do some rounding so that things that should be 0 are 0
    float vertexX = circle.radius * std::cosf(angle);
    float vertexY = circle.radius * std::sinf(angle);

    verticies.push_back(std::abs(vertexX) < 0.0000001 ? 0 : vertexX);
    verticies.push_back(std::abs(vertexY) < 0.0000001 ? 0 : vertexY);

    if (i == circle.resolution - 1) {
      indicies.push_back(0);
      indicies.push_back(i + 1);
      indicies.push_back(1); // wrap back around to first indicies
    } else {

      indicies.push_back(0);
      indicies.push_back(i + 1);
      indicies.push_back(i + 2);
    }
  }

  return std::make_pair(verticies, indicies);
}
