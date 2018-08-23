#pragma once
#include "./fluid/Poly6.hpp"
#include "Particle.hpp"
#include "Model.hpp"
#include <vector>

const static float MU = 1; //viscosity effecient





//ground
class PhysicsSimulator {
public:
    float boxSize = 32; // Virtual box 0~boxSize
    float damFac = -0.5;
    vector<Model*> mModels;
    ParticleSystem* mParticleSystem;
    PhysicsSimulator() {};
    
    void update(float deltaTime) {
        computeDensity();
        computeAcceleration();
        computeExternalForce();
        
        for (auto &itr:mParticleSystem->mParticles) {

            itr.velocity += itr.acceleration*deltaTime;
            itr.pos += itr.velocity*deltaTime;

            for (int i = 0; i<3; i++) {
                if (itr.pos[i] > boxSize) {
                    itr.pos[i] = boxSize;
                    itr.velocity[i] *= damFac;
                }
                if (itr.pos[i] <0) {
                    itr.pos[i] = 0.f;
                    itr.velocity[i] *= damFac;
                }
            }           
        }

        mParticleSystem->updateParticles();
    }

    void computeDensity() {
        Poly6 kernel(0);
        for (auto &p1:mParticleSystem->mParticles) {
            for (auto &p2:mParticleSystem->mParticles) {
                kernel.r = p1.distance(p2); //update kernel
                p1.density += p2.mass*kernel.calculate();
            }
        }
    }

    void computeAcceleration() {
        // TODO : acc error, Pressure?
        Poly6 kernel(0);
        for (auto &p1:mParticleSystem->mParticles) {
            glm::vec3 pressureForce = glm::vec3(0,0,0);
            glm::vec3 viscosityForce  = glm::vec3(0,0,0);
            for (auto &p2:mParticleSystem->mParticles) {
                kernel.r = p1.distance(p2); //update kernel
                pressureForce += -p2.mass*(p1.pressure + p2.pressure)*(1.0f/2*p2.density)*kernel.calculateGradient();
                viscosityForce += MU*p2.mass*(p2.velocity - p1.velocity)*(1.0f/p2.density)*kernel.calculateLaplacian();
            }

            glm::vec3 force = pressureForce + viscosityForce;
            p1.acceleration = force/p1.density;
            //dumpVec3(p1.acceleration);
            cout << p1.acceleration.x << endl;
        }  
    }

    void computeExternalForce() {
        for (auto &p1:mParticleSystem->mParticles) {
            p1.acceleration += gravity;
        }
    }

private:
    float speedFactor = 1;
    glm::vec3 gravity = glm::vec3(0,-9.8f,0);
    float inverseDt = 0.0f;
};