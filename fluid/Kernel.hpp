#pragma once
#include "glm/common.hpp"
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
    virtual float calculate() = 0;
    virtual glm::vec3 calculateGradient() = 0;
    virtual float calculateLaplacian() = 0;
};