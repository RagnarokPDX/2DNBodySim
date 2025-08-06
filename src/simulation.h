#ifndef SIMULATION_H
#define SIMULATION_H

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <vector>
// Assume that all circles are same size for now
// the current approach is array of strucutres
// considering i only really care about position data
// it moving to strucutres of arrays would be a lot better
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

struct BodyArray {
  std::vector<glm::vec2> pos;
  std::vector<glm::vec2> vel;
  std::vector<glm::vec2> acc;
  std::vector<float> mass;

  void update(float dt) {
    for (int i = 0; i < pos.size(); i++) {
      pos[i] += vel[i] * dt;
      vel[i] += acc[i] * dt;
      acc[i] = glm::vec2(0);
    }
  }
};

class Simulation {
public:
  std::vector<Body> bodies;
  BodyArray bodiesArray;
  // brute force approach of solving, cacluate force of all other ojbects
  // then sum and apply accordinglyy
  void updateBodies();
  void updateBodiesArray();
  void generateRandomBodies(int npositions);
  void generateRandomBodiesArray(int npositions);
  std::vector<glm::vec2> getBodiesPositions();
  std::vector<glm::vec2> getBodiesArrayPositions();

  void printPositions(std::vector<glm::vec2> &positions);

private:
};

#endif // !SIMULATION_H
