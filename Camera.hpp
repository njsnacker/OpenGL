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

    void updateDolly(float dolly_) {
        camPos += dolly_*camForwardDirection;
		updateViewMatrix();
	}

    void updateViewMatrix() {
        viewMatrix = glm::lookAt(camPos, camPos + camForwardDirection, camUpDirection);
    }

    void updateProjectionMatrix() {
        projectionMatrix = glm::perspective(fov, (float)windowWidth / windowHeight, zNear, zFar);
    }

    glm::mat4 getViewMatrix() {
        return viewMatrix;
    }

    glm::mat4 getProjectionMatrix() {
        return projectionMatrix;
    }
};