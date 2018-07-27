#pragma once
#include "Shader.hpp"
#include "Model.hpp"

class World {
public:
    vector<Model*> models;
    vector<Shader*> worldShader;

    World() {
        
    };
    ~World() {};

    void updatePyhsics(){};
    

    //서로다른 쉐이더로 그릴수 있게끔 확장
    void draw() {
        for (auto &itr : models) {
            itr->draw(worldShader[0]);
        }
    }

private:
    


};