#include "Kernel.hpp"

//https://nccastaff.bournemouth.ac.uk/jmacey/MastersProjects/MSc15/06Burak/BurakErtekinMScThesis.pdf
class Poly6 : Kernel {
public:
    float h = 8.f;
    float r  = 0.f;
    float inverseH10 = 0.f;
    float inverseH9 = 0.f;
    float hrSQ = 0.f;
    float scale = 0.f;


    Poly6(float r) {
        this->r = r;
        inverseH10 = 1/pow(h,10);
        inverseH9 = 1/pow(h,9);
        hrSQ = (h*h - r*r);
        scale = (315/(64*M_PI))*inverseH9;
    }

    float calculate() override {
        if ( r<=h) {
            return scale * pow(hrSQ,3);
        }
        return 0;
    }


    float calculateGradient() override {
        if ( r<= h) {
            return scale*-6*r*hrSQ*hrSQ;
        }

        return 0;
    }

    float calculateLaplacian() override {
        if (r<=h) {
            return scale*-6*hrSQ*(3*h*h - 7*r*r);
        }

        return 0;
    }



};