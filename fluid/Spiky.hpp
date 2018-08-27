#pragma once
#include "Kernel.hpp"

//https://nccastaff.bournemouth.ac.uk/jmacey/MastersProjects/MSc15/06Burak/BurakErtekinMScThesis.pdf
class Spiky : Kernel {
public:
    float inverseH6 = 0.f;
    
    Spiky(Particle& p1) {
        mP1 = p1;
        inverseH6 = 1/pow(h,6);
        scale = 15*inverseH6*M_PI;
    }

    void update(Particle& p2) {
        this->diffVec = -(mP1.pos - p2.pos);
        this->r = mP1.distance(p2);
        if (r!=0)  {
            inverseR = 1/r;
        } else {
            inverseR = 1;
        }
        hrSQ = (h*h - r*r);
        hr = h-r;
    }

    float calculate() override {
        if ( r<=h) {
            return scale * pow(hr,3);
        }
        return 0;
    }


    glm::vec3 calculateGradient() override {
        if ( r<= h) {
            return -3.0f* scale * hr*hr *inverseR*diffVec;
        }

        return glm::vec3{0,0,0};
    }

    float calculateLaplacian() override {
        if (r<=h) {
            return 0;
        }

        return 0;
    }



};