#pragma once
#include <iostream>
#include <vector>
#include <glm/common.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>


#include "Shader.hpp"

using namespace std;


class Vertex {
public:
    glm::vec3 pos;
    glm::vec2 texCoord;
};

class Model {
public:
    static vector<Vertex> vertices;
    static vector<uint32_t> indices;
    static vector<glm::vec3> instancePoses;

    glm::vec3 centorPos, maxPos, minPos;
    glm::mat4 modelMatrix;

    GLuint VAO, VBO, EBO, instanceVBO;

    Model() {
        modelMatrix = glm::mat4{1};
    }

    ~Model() {

    }

    static void setVertices(vector<Vertex> vertices_) {
        Model::vertices = vertices_;
    }

    static void setIndices(vector<uint32_t> indices_) {
        Model::indices = indices_;
    }

    void transliate(glm::vec3 movement_) {
        modelMatrix = modelMatrix * glm::translate(movement_);
    }

    void rotate(glm::vec3 axis_, float angle_) {
        modelMatrix = modelMatrix * glm::rotate(angle_, axis_);
    }

    void scale(float factor_) {
        modelMatrix = modelMatrix * glm::scale(glm::vec3{factor_});
    }

    void addInstance(vector<glm::vec3> instancePoses_) {
        for (auto &itr : instancePoses_) {
            instancePoses.push_back(itr);
        }
        // instance VBO
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, instancePoses.size()*sizeof(glm::vec3), instancePoses.data(), GL_STATIC_DRAW);
        
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glVertexAttribDivisor(3,1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void setupModel() {
        this->instancePoses.push_back(glm::vec3(0,0,0));

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO); //순서.. 반드시 여기와야함?
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &instanceVBO);

        // setting VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); 

        // setting EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);


        // setting VAO
        // vertex positions
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));

        // vertex normals
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));


        // instance VBO
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, instancePoses.size()*sizeof(glm::vec3), &instancePoses[0], GL_STATIC_DRAW);
        
        // setting VAO for instance VBO
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glVertexAttribDivisor(3,1);


        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void updateModel() {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);      //replace data in VBO with new data
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void draw(Shader* pShader) {
        glUseProgram(pShader->shaderId);
        pShader->set_uniform("modelMatrix",modelMatrix);
        // glBindBuffer(GL_ARRAY_BUFFER, VBO); 주석해도 돌아감
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBindVertexArray(VAO);
        glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instancePoses.size());
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};


vector<Vertex> Model::vertices;
vector<uint32_t> Model::indices;
vector<glm::vec3> Model::instancePoses;