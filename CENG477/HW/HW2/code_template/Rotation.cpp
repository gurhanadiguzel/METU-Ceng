#include "Rotation.h"

using namespace std;

#define PI 3.14159

Rotation::Rotation() {
    this->rotationId = -1;
    this->angle = 0;
    this->ux = 0;
    this->uy = 0;
    this->uz = 0;
}

Rotation::Rotation(int rotationId, double angle, double x, double y, double z) {
    this->rotationId = rotationId;
    this->angle = angle;
    this->ux = x;
    this->uy = y;
    this->uz = z;
}

std::ostream &operator<<(std::ostream &os, const Rotation &r) {
    os << std::fixed << std::setprecision(3) << "Rotation " << r.rotationId << " => [angle=" << r.angle << ", " << r.ux << ", " << r.uy << ", " << r.uz << "]";
    return os;
}

Matrix4 Rotation::doRotations(Matrix4 matrix) {
    Matrix4 Rx = getIdentityMatrix();
    Matrix4 M = getIdentityMatrix();
    Matrix4 InverseM = getIdentityMatrix();
    Matrix4 rotationMatrix = getIdentityMatrix();
    double cosTheta = cos(angle * PI / 180);
    double sinTheta = sin(angle * PI / 180);
    Vec3 v, w;
    Vec3 u = Vec3(ux, uy, uz);

    double minU = min(abs(ux), min(abs(uy), abs(uz)));

    if (minU == ux) {
        v = Vec3(0, -uz, uy);
    } else if (minU == uy) {
        v = Vec3(-uz, 0, ux);
    } else if (minU == uz) {
        v = Vec3(-uy, ux, 0);
    }
    w = crossProductVec3(u, v);

    M.values[0][0] = u.x;
    M.values[0][1] = u.y;
    M.values[0][2] = u.z;
    M.values[1][0] = v.x;
    M.values[1][1] = v.y;
    M.values[1][2] = v.z;
    M.values[2][0] = w.x;
    M.values[2][1] = w.y;
    M.values[2][2] = w.z;

    InverseM.values[0][0] = u.x;
    InverseM.values[1][0] = u.y;
    InverseM.values[2][0] = u.z;
    InverseM.values[0][1] = v.x;
    InverseM.values[1][1] = v.y;
    InverseM.values[2][1] = v.z;
    InverseM.values[0][2] = w.x;
    InverseM.values[1][2] = w.y;
    InverseM.values[2][2] = w.z;

    Rx.values[1][1] = cosTheta;
    Rx.values[1][2] = -sinTheta;
    Rx.values[2][1] = sinTheta;
    Rx.values[2][2] = cosTheta;

    rotationMatrix = multiplyMatrixWithMatrix(Rx, M);
    rotationMatrix = multiplyMatrixWithMatrix(InverseM, rotationMatrix);

    return multiplyMatrixWithMatrix(rotationMatrix, matrix);
}