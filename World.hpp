#pragma once
#include "Shader.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Particle.hpp"
#include "Physics.hpp"

class World {
public:
    vector<Model*> models;
    vector<Shader*> worldShader;
    ParticleSystem* particleSystem;
    PhysicsSimulator* physics;
    Camera* cam;

    World() {
        cam = new Camera{};
    };
    ~World() {};


    void initPhysics() {
        
        physics = new PhysicsSimulator();
        physics->models = models;
        physics->particleSystem = particleSystem;
    }


    void updatePyhsics(float deltaTime_){
        physics->update(deltaTime_);       
    };
    

    //서로다른 쉐이더로 그릴수 있게끔 확장
    void drawModel() {
        worldShader[0]->set_uniform("viewMatrix", cam->getViewMatrix());
        worldShader[0]->set_uniform("projectionMatrix", cam->getProjectionMatrix());
        

        for (auto &itr : models) {
            itr->draw(worldShader[0]);
        }
    }

    void drawParticle() {
        
        worldShader[0]->set_uniform("viewMatrix", cam->getViewMatrix());
        worldShader[0]->set_uniform("projectionMatrix", cam->getProjectionMatrix());

        particleSystem->draw(worldShader[0]);
    }

private:

};