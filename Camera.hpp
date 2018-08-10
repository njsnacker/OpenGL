#include <iostream>
#include <glm/common.hpp>
#include <glm/matrix.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>


using namespace std;

void dumpMat4(glm::mat4 mat_) {
    cout << "=======" << endl;
    cout << mat_[0][0] << " "  << mat_[0][1]  << " "<< mat_[0][2]  << " "<< mat_[0][3] << " "<< endl;
    cout << mat_[1][0] << " "  << mat_[1][1]  << " "<< mat_[1][2]  << " "<< mat_[1][3] << " "<< endl;
    cout << mat_[2][0] << " "  << mat_[2][1]  << " "<< mat_[2][2]  << " "<< mat_[2][3] << " "<< endl;
    cout << mat_[3][0] << " "  << mat_[3][1]  << " "<< mat_[3][2]  << " "<< mat_[3][3] << " "<< endl;
    cout << "=======" << endl;
}

class Camera {
public:
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -10.0f), 
            camForwardDirection = glm::vec3(0.0f, 0.0f, -1.0f), 
            camUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    int windowWidth = 1920;
    int windowHeight = 1080;
    float fov = 120, zNear = 0.001, zFar = 1000;
    float trackballScale = 1.0;
    float dollyScale = 1.0;

    Camera() {
        camQuat = glm::angleAxis(glm::degrees(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        isTrackballSet = false;

        updateViewMatrix();
        updateProjectionMatrix();
    }

    void resize(int width_, int height_, float fov_ = 120.0, float zNear_ = 0.001, float zFar_ = 1000) {
        windowWidth = width_;
        windowHeight = height_;
        fov = fov_;
        zNear = zNear_;
        zFar = zFar_;
		updateProjectionMatrix();
    }
    
    void startRotation(float xPos,float yPos) {
        isTrackballSet = true;
    }

    void endRotation(float xPos,float yPos) {
        isTrackballSet = false;    
    }

    glm::mat4 getViewMatrix() {
        return viewMatrix;
    }

    glm::mat4 getProjectionMatrix() {
        return projectionMatrix;
    }

    void updateMousePos(float xPos, float yPos) {
         
        //update trackball
        if (isTrackballSet == true) {
            glm::vec3 va = getArcballVector(xPosPrev,yPosPrev);
            glm::vec3 vb = getArcballVector(xPos,yPos);

            float angle = glm::degrees(acos(min(1.0f, glm::dot(va, vb))))*trackballScale;
            glm::vec3 axis = glm::normalize(glm::cross(va, vb));

            camQuat = glm::angleAxis(angle,axis)*camQuat; 
            camForwardDirection  = glm::vec3(glm::mat4_cast(camQuat)*glm::vec4(camForwardDirection,0));
            camUpDirection = glm::vec3(glm::mat4_cast(camQuat)*glm::vec4(camUpDirection,0));
            updateViewMatrix();
        }

        xPosPrev = xPos; yPosPrev = yPos;
    }

    void updateDolly(float dolly_) {
        camPos += glm::vec3 {0,0,dolly_*dollyScale};
		updateViewMatrix();
	}

private:
    bool isTrackballSet;
    float xPosPrev, yPosPrev;
    glm::quat camQuat;
    glm::mat4 projectionMatrix, viewMatrix;

    void updateViewMatrix() {
        viewMatrix = glm::translate(camPos)*glm::mat4_cast(camQuat);
        //viewMatrix = glm::lookAt(camPos, camPos + camForwardDirection, camUpDirection);
    }

    void updateProjectionMatrix() {
        projectionMatrix = glm::perspective(fov, (float)windowWidth / windowHeight, zNear, zFar);
    }

    glm::vec3 getArcballVector(int x, int y) {
        glm::vec3 P = glm::vec3(1.0 * x / windowWidth * 2 - 1.0,
                                1.0 * y / windowHeight * 2 - 1.0,
                                0);
        P.y = -P.y;
        float OP_squared = P.x * P.x + P.y * P.y;   
        if (OP_squared <= 1 * 1)
            P.z = sqrt(1 * 1 - OP_squared); // Pythagore
        else
            P = glm::normalize(P); // nearest point
        return P;
    }
};
