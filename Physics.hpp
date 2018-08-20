#pragma once
#include "Particle.hpp"
#include "Model.hpp"
#include <vector>

//ground
class PhysicsSimulator {
public:
    
    vector<Model*> models;
    ParticleSystem* particleSystem;
    PhysicsSimulator() {};
    

    void update(float deltaTime) {
        inverseDt = 1.0f/deltaTime;
        float dy = speedFactor*gravity*inverseDt*inverseDt;
        for (auto &itr:particleSystem->mParticles) {
            itr.pos += glm::vec3(0, dy ,0);
        }

        particleSystem->updateParticles();
    }


private:
    float speedFactor = 0.0000001;
    float gravity = -9.8f;
    float inverseDt = 0.0f;

};