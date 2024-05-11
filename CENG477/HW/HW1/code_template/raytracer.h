#ifndef CENG477_RAYTRACER_H
#define CENG477_RAYTRACER_H
#include <pthread.h>

#include <iostream>
#include <limits>

#include "parser.h"
#include "ppm.h"

using namespace parser;
using namespace std;

typedef unsigned char RGB[3];

struct Plane {
    Vec3f cameraPosition;
    Vec3f gazeVector;
    Vec3f m, q, u, v;
    double top, bottom, left, right;
    int n_x, n_y;
};

struct Ray {
    Vec3f origin;
    Vec3f direction;
};

struct HitRecord {
    bool hit;
    Vec3f intersectionPoint;
    Vec3f surfaceNormal;
    int material_id;
    int object_type;
    int object_index;
    double t;
};

struct ThreadData {
    Scene scene;
    Camera camera;
    Plane plane;
    vector<Triangle> triangleList;
    vector<Mesh> meshList;
    int y;
    int x;
};

Vec3f operator+(const Vec3f& v1, const Vec3f& v2) {
    Vec3f result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;

    return result;
}

Vec3f operator-(const Vec3f& v1, const Vec3f& v2) {
    Vec3f result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;

    return result;
}

Vec3f operator*(const Vec3f& v1, double alpha) {
    Vec3f result;
    result.x = v1.x * alpha;
    result.y = v1.y * alpha;
    result.z = v1.z * alpha;

    return result;
}

Vec3f operator/(const Vec3f& v1, double alpha) {
    Vec3f result;
    result.x = v1.x / alpha;
    result.y = v1.y / alpha;
    result.z = v1.z / alpha;

    return result;
}

Vec3f crossProduct(const Vec3f& vector1, const Vec3f& vector2) {
    Vec3f result;
    result.x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
    result.y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
    result.z = (vector1.x * vector2.y) - (vector1.y * vector2.x);
    return result;
}

double dotProduct(const Vec3f& vector1, const Vec3f& vector2) {
    double result = (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
    return result;
}

double matrixDeterminant(const Vec3f& vector1, const Vec3f& vector2, const Vec3f& vector3) {
    double result = vector1.x * (vector2.y * vector3.z - vector2.z * vector3.y) - vector2.x * (vector1.y * vector3.z - vector1.z * vector3.y) + vector3.x * (vector1.y * vector2.z - vector1.z * vector2.y);
    return result;
}

void printVector(Vec3f vector) {
    cout << "Vector is :"
         << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")" << endl;
}

Plane generatePlane(const Camera& camera);
Ray generateRay(const Plane& plane, int y, int x);
HitRecord triangleIntersection(const Ray& ray, const Vec3f& a, const Vec3f& b, const Vec3f& c, int material_id, int material_type);
HitRecord sphereIntersection(const Ray& ray, const Sphere& sphere, const Vec3f& center);
HitRecord findRaySceneIntersection(const Scene& scene, const Ray& ray, const vector<Triangle>& triangleList, const vector<Mesh>& meshList);
bool findShadowIntersection(const Scene& scene, const Ray& ray, double tLight);
Vec3f findIrradiance(const PointLight& light, const HitRecord& hitRecord);
Vec3f findDiffuseShading(const PointLight& light, const HitRecord& hitRecord, const Material& material, Vec3f w_i, Vec3f w_o);
Vec3f findSpecularShading(const PointLight& light, const HitRecord& hitRecord, const Material& material, Vec3f w_i, Vec3f w_o);
Vec3f applyShading(const Scene& scene, const Ray& ray, const Camera& camera, const HitRecord& hitRecord, int depth, const vector<Triangle>& triangleList, const vector<Mesh>& meshList);
Vec3f renderPixelColor(const Scene& scene, const Ray& ray, const Camera& camera, const HitRecord& hitRecord, int depth, const vector<Triangle>& triangleList, const vector<Mesh>& meshList);

#endif  // CENG477_RAYTRACER_H