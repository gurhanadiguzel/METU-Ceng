#include "Scaling.h"

Scaling::Scaling() {
    this->scalingId = -1;
    this->sx = 0;
    this->sy = 0;
    this->sz = 0;
}

Scaling::Scaling(int scalingId, double sx, double sy, double sz) {
    this->scalingId = scalingId;
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}

std::ostream &operator<<(std::ostream &os, const Scaling &s) {
    os << std::fixed << std::setprecision(3) << "Scaling " << s.scalingId << " => [" << s.sx << ", " << s.sy << ", " << s.sz << "]";

    return os;
}

Matrix4 Scaling::doScaling(Matrix4 matrix) {
    Matrix4 scalingMatrix = getIdentityMatrix();
    scalingMatrix.values[0][0] = sx;
    scalingMatrix.values[1][1] = sy;
    scalingMatrix.values[2][2] = sz;

    return multiplyMatrixWithMatrix(scalingMatrix, matrix);
}
