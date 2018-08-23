#pragma once
#include "glm/common.hpp"
#include "glm/matrix.hpp"
#include <iostream>

using namespace std;

void dumpMat4(glm::mat4 mat_) {
    cout << "=======" << endl;
    cout << mat_[0][0] << " "  << mat_[0][1]  << " "<< mat_[0][2]  << " "<< mat_[0][3] << " "<< endl;
    cout << mat_[1][0] << " "  << mat_[1][1]  << " "<< mat_[1][2]  << " "<< mat_[1][3] << " "<< endl;
    cout << mat_[2][0] << " "  << mat_[2][1]  << " "<< mat_[2][2]  << " "<< mat_[2][3] << " "<< endl;
    cout << mat_[3][0] << " "  << mat_[3][1]  << " "<< mat_[3][2]  << " "<< mat_[3][3] << " "<< endl;
    cout << "=======" << endl;
}

void dumpVec3(glm::vec3 mat_) {
    cout << "=======" << endl;
    cout << mat_.x << " "  << mat_.y  << " "<< mat_.z << " "<< endl;
    cout << "=======" << endl;
}
