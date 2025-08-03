#include "simulation.h"
#include <algorithm>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <random>

void Simulation::update() {
  for (int i = 0; i < bodies.size(); i++) {
    glm::vec2 p1 = bodies[i].pos;
    float m1 = bodies[i].mass;
    for (int j = 0; j < bodies.size(); j++) {
      glm::vec2 p2 = bodies[j].pos;
      float m2 = bodies[j].mass;

      // assume g is 1 to simply calculations
      // F = G (m_1 * m_2) / |r|^2
      // simplyying  we obtain F = r (m_1 * m_2) / |r|^3

      glm::vec2 r = p2 - p1;

      float r_mag = glm::length(r);
      // the value we are trying to obtain here is a1,
      // where a1 = r m_2 / r^3
      // where r^3 = r sqrt(r)
      // alternitively r^3 = sqrt(r) * sqrt(r)*sqrt(r)
      // also need to specify min to not get divide by 0
      glm::vec2 a1 = r * (m2 / std::max(r_mag * r_mag * r_mag, 0.000001f));

      // clamp down acceleration to mimic contact
      if (r_mag < 0.3) {
        a1 = glm::vec2(0);
      }

      bodies[i].acc += a1 * 3.0f; // speed up effects
    }
  }

  for (int i = 0; i < bodies.size(); i++) {
    bodies[i].update(0.001); // dt
  }
}

// for now asumme all circles are the same size
// npositions will gen n nubmer npositions so 2 * n floats
void Simulation::generateRandomPositions(int npositions) {

  std::default_random_engine generator;
  std::normal_distribution<float> distrib(0.0f, 50.0f);

  for (int i = 0; i < npositions; i++) {
    float randX = distrib(generator);
    float randY = distrib(generator);
    Body newBody;
    newBody.acc = glm::vec2(0);
    newBody.mass = 500;
    newBody.pos.x = randX;
    newBody.pos.y = randY;

    newBody.vel = glm::vec2(0);
    if (randX > 0 && randY > 0) {
      newBody.vel = glm::vec2(randY / 2, -randX / 2) * 1.0f;
    }
    if (randX < 0 && randY > 0) {
      newBody.vel = glm::vec2(randY / 2, -randX / 2) * 1.0f;
    }
    if (randX > 0 && randY < 0) {
      newBody.vel = glm::vec2(randY / 2, -randX / 2) * 1.0f;
    }
    if (randX < 0 && randY < 0) {
      newBody.vel = glm::vec2(randY / 2, -randX / 2) * 1.0f;
    }
    bodies.push_back(newBody);
  }

  Body sun;
  sun.pos = glm::vec2(0, 0);
  sun.acc = glm::vec2(0, 0);
  sun.vel = glm::vec2(0, 0);
  sun.mass = 100000.0f;
  // bodies.push_back(sun);
}

std::vector<glm::vec2> Simulation::getPositions() {
  std::vector<glm::vec2> positions;
  for (auto i : bodies) {
    positions.push_back(i.pos);
  }
  return positions;
}

void Simulation::printPositions() {
  for (int i = 0; i < bodies.size(); i++) {
    std::cout << "Body - " << i << "\n";
    std::cout << "xpos - " << bodies[i].pos.x << "\n";
    std::cout << "ypos - " << bodies[i].pos.y << "\n";
  }
}
