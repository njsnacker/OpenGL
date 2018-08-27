#pragma once
#include "./fluid/Poly6.hpp"
#include "./fluid/Spiky.hpp"
#include "./fluid/Viscosity.hpp"
#include "Particle.hpp"
#include "Model.hpp"
#include <vector>

const static float MU = 1; //viscosity effecient
const static float GAS = -1;




//ground
class PhysicsSimulator {
public:
    float boxSize = 64; // Virtual box 0~boxSize
    float damFac = -0.5;
    vector<Model*> mModels;
    ParticleSystem* mParticleSystem;
    PhysicsSimulator() {};
    
    void update(float deltaTime) {
        computeDensityAndPressure();
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



    void computeDensityAndPressure() {
        for (auto &p1:mParticleSystem->mParticles) {
            Poly6 kernel(p1);
            for (auto &p2:mParticleSystem->mParticles) {
                kernel.update(p2);
                p1.density += p2.mass*kernel.calculate();
            }
            p1.pressure = GAS*(p1.density - mParticleSystem->mDensityOffset);
        }
    }

    void computeAcceleration() {
        
        for (auto &p1:mParticleSystem->mParticles) {
            // Poly6 kernel(p1);
            Spiky kernel_spiky(p1);
            Viscosity kernel_vis(p1);

            glm::vec3 pressureForce = glm::vec3(0,0,0);
            glm::vec3 viscosityForce  = glm::vec3(0,0,0);
            for (auto &p2:mParticleSystem->mParticles) {
                // kernel.update(p2);
                kernel_spiky.update(p2);
                kernel_vis.update(p2);
                // pressureForce += -p2.mass*(p1.pressure + p2.pressure)*(1.0f/2*p2.density)*kernel_spiky.calculateGradient();
                // viscosityForce += MU*p2.mass*(p2.velocity - p1.velocity)*(1.0f/p2.density)*kernel_vis.calculateLaplacian();
                pressureForce += -p2.mass*(p1.pressure + p2.pressure)*(1.0f/2*p2.density)*kernel_spiky.calculateGradient();
                viscosityForce += MU*p2.mass*(p2.velocity - p1.velocity)*(1.0f/p2.density)*kernel_vis.calculateLaplacian();
            }
            glm::vec3 force = pressureForce + viscosityForce;
            p1.acceleration = force/p1.density;
        }  
    }

    void computeExternalForce() {
        for (auto &p1:mParticleSystem->mParticles) {
            p1.acceleration += gravity/p1.mass;
        }
    }

private:
    float speedFactor = 1;
    glm::vec3 gravity = glm::vec3(0,-9.8f,0);
    float inverseDt = 0.0f;
};