#pragma once
#include "../Particle.hpp"
#include "glm/common.hpp"
#include <cmath>
// refer https://github.com/PaulKennedyDIT/SPH/blob/master/Assets/Code/SPH/Poly6.cs
// math

/**
 * http://sdolnote.tistory.com/entry/Gradient
 * http://happy8earth.tistory.com/297
 * https://wikidocs.net/4053
 * http://sdolnote.tistory.com/entry/Linearity?category=599855
 * https://wikidocs.net/6998
 * 
 * */

class Kernel {
protected:
    float h = 3.f;
    float r = 0.f;
    float inverseR = 0.f;
    float hrSQ = 0.f;
    float hr = 0.f;
    float scale = 0.f;

    Particle mP1;
    glm::vec3 diffVec{0,0,0};


    virtual float calculate() = 0;
    virtual glm::vec3 calculateGradient() = 0;
    virtual float calculateLaplacian() = 0;
};