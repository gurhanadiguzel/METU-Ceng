#ifndef __ROTATION_H__
#define __ROTATION_H__

#include <iomanip>

#include "Helpers.h"
#include "Matrix4.h"

class Rotation {
   public:
    int rotationId;
    double angle, ux, uy, uz;

    Rotation();
    Rotation(int rotationId, double angle, double x, double y, double z);
    friend std::ostream &operator<<(std::ostream &os, const Rotation &r);

    Matrix4 doRotations(Matrix4 matrix);
};

#endif