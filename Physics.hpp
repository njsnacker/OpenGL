#pragma once
#include "Particle.hpp"
#include "Model.hpp"
#include <vector>

const static float H = 16.f; // kernel radius
const static float POLY6 = 315.f*(64.f*M_PI*pow(H,9));
const static float MU = 1; //viscosity effecient





//ground
class PhysicsSimulator {
public:
    
    vector<Model*> mModels;
    ParticleSystem* mParticleSystem;
    PhysicsSimulator() {};
    

    void update(float deltaTime) {
        glm::vec3 dy = gravity*deltaTime*deltaTime;
        for (auto &itr:mParticleSystem->mParticles) {
            itr.pos += dy;
        }

        mParticleSystem->updateParticles();
    }

    



    void computeDensity() {
        for (auto &p1:mParticleSystem->mParticles) {
            for (auto &p2:mParticleSystem->mParticles) {
                float part = p1.distance(p2) <= H ? pow((H*H - p1.distance(p2)*p1.distance(p2)),3) : 0;
                p1.density += (p2.mass*POLY6*part);
            }
        }
    }


    void computeAcceleration() {
        for (auto &p1:mParticleSystem->mParticles) {
            glm::vec3 pressureForce = glm::vec3(0,0,0);
            glm::vec3 viscosityForce  = glm::vec3(0,0,0);
            for (auto &p2:mParticleSystem->mParticles) {
                float part = p1.distance(p2) <= H ? pow((H*H - p1.distance(p2)*p1.distance(p2)),3) : 0;
                pressureForce += (-p2.mass*((p1.pressure + p2.pressure)/(2*p2.density))*POLY6*part);
                viscosityForce += (MU*p2.mass*(p1.velocity-p2.velocity)/p2.density???)


            }

            float force = pressureForce;
            p1.acceleration = force/p1.density;
        }  
    }


private:
    float speedFactor = 1;
    glm::vec3 gravity = glm::vec3(0,-9.8f,0);
    float inverseDt = 0.0f;
};