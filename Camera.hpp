#include <iostream>
#include <glm/common.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

class Camera {
public:
    glm::mat4 projectionMatrix, viewMatrix;
    glm::vec3 camPos, camForwardDirection, camUpDirection;
    int windowWidth;
    int windowHeight;
    float fov, zNear, zFar;

    Camera() {
        camPos = glm::vec3(0.0f, 0.0f, 10.0f);
        camForwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
        camUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);
        windowWidth = 1920;
        windowHeight = 1080;
        fov = 120;
        zNear = 0.001;
        zFar = 100;

        updateViewMatrix();
        updateProjectionMatrix();
    }

    void resize(int width_, int height_, float fov_ = 120.0, float zNear_ = 0.001, float zFar_ = 100) {
        windowWidth = width_;
        windowHeight = height_;
        fov = fov_;
        zNear = zNear_;
        zFar = zFar_;
		updateProjectionMatrix();
    }
    
    void startRotation(float xPos,float yPos) {

    }

    void endRotation(float xPos,float yPos) {

    }

    glm::mat4 getViewMatrix() {
        return viewMatrix;
    }

    glm::mat4 getProjectionMatrix() {
        return projectionMatrix;
    }

    void updateTrackball() {
        glm::vec3 va = get_arch
    }

    void updateDolly(float dolly_) {
        camPos += dolly_*camForwardDirection;
		updateViewMatrix();
	}

private:

    void updateViewMatrix() {
        viewMatrix = glm::lookAt(camPos, camPos + camForwardDirection, camUpDirection);
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