#include "simulation.h"
#include <algorithm>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <random>

void Simulation::update() {
  for (int i = 0; i < bodies.size(); i++) {
    glm::vec2 p1 = bodies[i].pos;
    float m1 = bodies[i].mass;
    for (int j = 0; j < bodies.size(); j++) {
      glm::vec2 p2 = bodies[i].pos;
      float m2 = bodies[i].mass;

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
      bodies[i].acc = a1;
    }
  }

  for (int i = 0; i < bodies.size(); i++) {
    bodies[i].update(0.00001); // dt
  }
}

// for now asumme all circles are the same size
void Simulation::generateRandomPositions(int nrolls) {

  std::default_random_engine generator;
  std::normal_distribution<float> distrib(500.0f, 200.0f);
}
