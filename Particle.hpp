#pragma once
#include "Model.hpp"
#include <cmath>
#include <vector>
#include <glm/common.hpp>
#include "Shader.hpp"

using namespace std;



class Particle {
public:
    glm::vec3 pos = glm::vec3(0,0,0);
    glm::vec3 velocity = glm::vec3(0,0,0);
    glm::vec3 acceleration = glm::vec3(0,0,0);
    float size = 0 , angle = 0, mass = 1;
    float density = 0, pressure = 0;
    float lifeTime = 0;

    float distance(const Particle& p2) {
        return abs(glm::distance(this->pos, p2.pos));
    }
};


class ParticleSystem : private Model {
public:
    float mDensityOffset = 1.0f;
    vector<Particle> mParticles;

    ParticleSystem() {
        this->loadObj("./sphere.obj");
        setupModel();
    }

    void initParticles(const vector<Particle> partices_) {
        mParticles = partices_;
        vector<glm::vec3> tmpInstancePoses;
        for (auto &itr : mParticles) {
            tmpInstancePoses.push_back(itr.pos);
        }
        updateInstance(tmpInstancePoses);
    }

    void updateParticles() {
        vector<glm::vec3> tmpInstancePoses;
        for (auto &itr : mParticles) {
            tmpInstancePoses.push_back(itr.pos);
        }
        updateInstance(tmpInstancePoses);
    }

    void draw(Shader* pShader_) {
        Model::draw(pShader_);
    }
};