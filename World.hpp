#pragma once
#include "Shader.hpp"
#include "Model.hpp"
#include "Camera.hpp"

class World {
public:
    vector<Model*> models;
    vector<Shader*> worldShader;
    Camera* cam;

    World() {
        cam = new Camera{};
    };
    ~World() {};

    void updatePyhsics(){};
    

    //서로다른 쉐이더로 그릴수 있게끔 확장
    void draw() {
        worldShader[0]->set_uniform("viewMatrix", cam->getViewMatrix());
        worldShader[0]->set_uniform("projectionMatrix", cam->getProjectionMatrix());


        for (auto &itr : models) {
            itr->draw(worldShader[0]);
        }
    }

private:
    


};