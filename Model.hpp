#pragma once
#include <iostream>
#include <vector>
#include <glm/common.hpp>

#include "Shader.hpp"

using namespace std;


class Vertex {
public:
    glm::vec3 pos;
    glm::vec2 texCoord;
};

class Model {
public:
    vector<Vertex> vertices;
    vector<uint32_t> indices;
    glm::vec3 centorPos, maxPos, minPos;

    GLuint VAO, VBO, EBO;

    Model() {

    }

    ~Model() {

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
    }

    void updateModel() {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);      //replace data in VBO with new data
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void draw(Shader* pShader) {
        //glUseProgram(pShader->shaderId);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

