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
    glm::vec3 pressure = glm::vec3(0,0,0);
    glm::vec3 accelration = glm::vec3(0,0,0);
    glm::vec4 color = glm::vec4(0,0,0,0);
    float size = 0 , angle = 0, weight = 0, mass = 0;
    float density = 0;
    float lifeTime = 0;

    float distance(const Particle& p2) {
        abs(glm::distance(this->pos, p2.pos));
    }
};


class ParticleSystem : private Model {
public:

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

// class ParticleSystem {
// public:
//     vector<Particle> particles;
//     GLuint VAO, VBO;

//     void setupModel() {
//         //this->instancePoses.push_back(glm::vec3(0,0,0));

//         glGenVertexArrays(1, &VAO);
//         glBindVertexArray(VAO); //순서.. 반드시 여기와야함?
//         glGenBuffers(1, &VBO);

//         // setting VBO
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
//         glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), &particles[0], GL_STATIC_DRAW); 

//         // setting VAO
//         // vertex positions
        
//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, pos));

//         // vertex normals
//         // glEnableVertexAttribArray(1);
//         // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

//         // vertex texture coords
//         glEnableVertexAttribArray(2);
//         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, color));

//         glBindVertexArray(0);
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//     }

//     void updateModel() {
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 	    glBufferSubData(GL_ARRAY_BUFFER, 0, particles.size() * sizeof(Particle), &particles[0]);      //replace data in VBO with new data
// 	    glBindBuffer(GL_ARRAY_BUFFER, 0);
//     }

//     void draw(Shader* pShader) {
        
//         glUseProgram(pShader->shaderId);
//         glPointSize(15);
//         glEnable(GL_POINT_SMOOTH);
//         glEnable(GL_BLEND);
//         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//         pShader->set_uniform("modelMatrix",glm::mat4{1});
//         glBindVertexArray(VAO);
//         glDrawArrays( GL_POINTS, 0, particles.size());
//         //glDrawArrays(GL_POINTS, 0, particles.size());
//         //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//         glBindVertexArray(0);

//         // glBegin(GL_POINTS);
//         // for (int i = 0; i<particles.size(); i++) {
//         //     glVertex3fv((GLfloat*)&particles[i].pos);
//         // }
//         // glEnd();
//     }

// private:

// };


