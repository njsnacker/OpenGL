#include <glm/common.hpp>
#define max(a,b) a>b ? a: b
#define min(a,b) a<b ? a: b

class Ray {
public:
    glm::vec3 o; //origin
    glm::vec3 d; //direction
    mutable float mint, maxt;
    float time;
    int depth;
    Ray() : mint(0.f), maxt(INFINITY), time(0.f), depth(0) {}
    Ray(const glm::vec3 &origin, const glm::vec3 &direction,
        float start, float end = INFINITY, float t = 0.f, int d = 0) 
        : o(origin), d(direction), mint(start), maxt(end), time(t), depth(d) {}
    Ray(const glm::vec3 &origin, const glm::vec3 &direction, const Ray &parent,
        float start, float end = INFINITY)
        : o(origin), d(direction), mint(start), maxt(end), time(parent.time), depth(parent.depth +1) {}
    
    glm::vec3 operator() (float t) const {return o + d*t;}
};

class RayDifferential : public Ray {
public:
    RayDifferential () {hasDifferentials = false;}
    RayDifferential (const glm::vec3 &org, const glm::vec3 &dir, float start,
                    float end = INFINITY, float t = 0.f, int d = 0)
                    : Ray(org, dir, start, end, t, d) {
                        hasDifferentials = false;
                    }
    RayDifferential (const glm::vec3 &org, const glm::vec3 &dir, const Ray &paernt,
                    float start, float end = INFINITY)
                    : Ray(org, dir, start, end, paernt.time, paernt.depth +1) {
                        hasDifferentials = false;
                    }
    
    explicit RayDifferential(const Ray &ray) : Ray(ray) {
        hasDifferentials = false;
    }

    void scaleDifferentials(float s) {
        rxOrigin = o + (rxOrigin - o) * s;
        ryOrigin = o + (ryOrigin - o) * s;
        rxDirection = d + (rxDirection-d) * s;
        ryDirection = d + (ryDirection-d) * s;
    }

    bool hasDifferentials;
    glm::vec3 rxOrigin, ryOrigin;
    glm::vec3 rxDirection, ryDirection;

};

class BBox {
public:
    glm::vec3 pMin, pMax;

    BBox() {
        pMin = glm::vec3(INFINITY, INFINITY, INFINITY);
        pMax = glm::vec3(-INFINITY, -INFINITY, -INFINITY);
    }

    BBox(const glm::vec3 &p) : pMin(p), pMax(p) { }

    BBox(const glm::vec3 &p1, const glm::vec3 &p2) {
        pMin = glm::vec3( min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
        pMax = glm::vec3( max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
    }

    BBox Union(const BBox &b, const glm::vec3 &p) {
        BBox ret = b;
        ret.pMin.x = min(b.pMin.x, p.x);
        ret.pMin.y = min(b.pMin.y, p.y);
        ret.pMin.z = min(b.pMin.z, p.z);
        ret.pMax.x = min(b.pMax.x, p.x);
        ret.pMax.y = min(b.pMax.y, p.y);
        ret.pMax.z = min(b.pMax.z, p.z);
        return ret;
    }

    bool Overlaps(const BBox &b) {
        bool x = (pMax.x >= b.pMin.x) && (pMin.x <= b.pMax.x);
        bool y = (pMax.y >= b.pMin.y) && (pMin.y <= b.pMax.y);
        bool z = (pMax.z >= b.pMin.z) && (pMin.z <= b.pMax.z);
    }
    
    friend BBox Uinon(const BBox &b, const BBox &b2);

}