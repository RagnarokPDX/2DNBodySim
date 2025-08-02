#ifndef SIMULATION_H
#define SIMULATION_H

#include <glm/vec2.hpp>
#include <vector>

// Assume that all circles are same size for now
//
//
//
struct Body {
  glm::vec2 pos;
  glm::vec2 vel;
  glm::vec2 acc;
  float mass;

  void update(float dt) {
    pos += vel * dt;
    vel += acc * dt;
    acc = glm::vec2(0, 0);
  }
};

class Simulation {
public:
  std::vector<Body> bodies;

  // brute force approach of solving, cacluate force of all other ojbects
  // then sum and apply accordinglyy
  void update();
  void generateRandomPositions(int nrolls);

private:
};

#endif // !SIMULATION_H
