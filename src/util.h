#ifndef UTIL_H
#define UTIL_H
#include <glm/fwd.hpp>
#include <iostream>
#include <utility>
#include <vector>

#define PI 3.14159265359
struct Circle {
  float centerX;
  float centerY;
  float radius; // might need to cap radius to 1 due to how we transform it to
                // circles
  int resolution;
  // maybe optional param that decides the "resolution" of
  // the cirle, or could calculate off raidus
};

template <typename T> void printVector(std::vector<T> vec) {
  for (auto i : vec) {
    std::cout << i << ", ";
  }
  std::cout << "\n";
}
// i think you can techincally make squares with this lol
std::pair<std::vector<float>, std::vector<unsigned int>>
genereteCirleVerticiesAndIndicies(Circle circle);

// circle needs vbo, ibo

#endif
