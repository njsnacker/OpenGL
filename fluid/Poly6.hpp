#pragma once
#include "Kernel.hpp"

//https://nccastaff.bournemouth.ac.uk/jmacey/MastersProjects/MSc15/06Burak/BurakErtekinMScThesis.pdf
class Poly6 : Kernel {
public:
    float inverseH10 = 0.f;
    float inverseH9 = 0.f;
    
    Poly6(Particle& p1) {
        mP1 = p1;
        inverseH10 = 1/pow(h,10);
        inverseH9 = 1/pow(h,9);
        scale = (315/(64*M_PI))*inverseH9;
    }

    void update(Particle& p2) {
        this->diffVec = -(mP1.pos - p2.pos);
        this->r = mP1.distance(p2);
        inverseR = 1/r;
        hrSQ = (h*h - r*r);
        hr = h-r;
    }

    float calculate() override {
        if ( r<=h) {
            return scale * pow(hrSQ,3);
        }
        return 0;
    }


    glm::vec3 calculateGradient() override {
        if ( r<= h) {
            return -6*scale*hrSQ*hrSQ*diffVec;
        }

        return glm::vec3{0,0,0};
    }

    float calculateLaplacian() override {
        if (r<=h) {
            return -6*scale*hrSQ*(3*h*h - 7*r*r);
        }

        return 0;
    }



};