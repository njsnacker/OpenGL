// #pragma once
// #include <iostream>
// #include <vector>
// #include <glm/common.hpp>
// #include <glm/gtx/transform.hpp>

// #include "Shader.hpp"

// using namespace std;

// class Particle {
// public:
//     uint32_t maxNum;
//     vector<glm::vec3> poses;
//     vector<glm::vec3> vertices{
// 		glm::vec3(0.5, 0.5, 0.5),
// 		glm::vec3(-0.5, 0.5, 0.5),
// 		glm::vec3(-0.5, -0.5, 0.5),
// 		glm::vec3(0.5, -0.5, 0.5),
// 		glm::vec3(0.5, 0.5, -0.5),
// 		glm::vec3(-0.5, 0.5, -0.5),
// 		glm::vec3(-0.5, -0.5, -0.5),
// 		glm::vec3(0.5, -0.5, -0.5)};
    
//     vector<uint32_t> indices {
//         0, 1, 2,
// 		0, 2, 3,
// 		4, 0, 3,
// 		4, 3, 7,
// 		5, 1, 0,
// 		5, 0, 4,
// 		6, 7, 3,
// 		6, 3, 2,
// 		1, 5, 6,
// 		1, 6, 2,
// 		6, 5, 4,
// 		6, 4, 7
//     };
    
//     GLuint VAO, VBO, EBO;

//     Particle() {
//     }

//     ~Particle() {
//     }

//     void setupParticle() {
//         glGenVertexArrays(1, &VAO);
//         glBindVertexArray(VAO);
//         glGenBuffers(1, &VBO);
//         glGenBuffers(1, &EBO);

//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
//         glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW); 

//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

//         // vertex positions
//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));

//         // vertex normals
//         // glEnableVertexAttribArray(1);
//         // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

//         // vertex texture coords
//         glEnableVertexAttribArray(1);
//         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

//         glBindVertexArray(0);
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//     }

//     void updateModel() {
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 	    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);      //replace data in VBO with new data
// 	    glBindBuffer(GL_ARRAY_BUFFER, 0);
//     }

//     void draw(Shader* pShader) {
//         glUseProgram(pShader->shaderId);
//         //pShader->set_uniform("modelMatrix",modelMatrix);
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//         glBindVertexArray(VAO);
//         glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//         glBindVertexArray(0);
//     }
// };

// vector<Vertex> Model::vertices;
// vector<uint32_t> Model::indices;
