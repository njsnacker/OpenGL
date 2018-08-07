#pragma once
#include <iostream>
#include <vector>
#include <glm/common.hpp>
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
    glm::vec3 centorPos, maxPos, minPos;
    glm::mat4 modelMatrix;
    uint32_t instanceCount = 0;

    GLuint VAO, VBO, EBO;

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

    void setupModel() {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); 

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));

        // vertex normals
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        // vertex texture coords
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

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
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

vector<Vertex> Model::vertices;
vector<uint32_t> Model::indices;
