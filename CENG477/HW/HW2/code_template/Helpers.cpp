#include "Helpers.h"

/*
 * Calculate cross product of vec3 a, vec3 b and return resulting vec3.
 */
Vec3 crossProductVec3(Vec3 a, Vec3 b) {
    return Vec3(a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y);
}

/*
 * Calculate dot product of vec3 a, vec3 b and return resulting value.
 */
double dotProductVec3(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/*
 * Find length (|v|) of vec3 v.
 */
double magnitudeOfVec3(Vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

/*
 * Normalize the vec3 to make it unit vec3.
 */
Vec3 normalizeVec3(Vec3 v) {
    double d = magnitudeOfVec3(v);
    return Vec3(v.x / d, v.y / d, v.z / d);
}

/*
 * Return -v (inverse of vec3 v)
 */
Vec3 inverseVec3(Vec3 v) {
    return Vec3(-v.x, -v.y, -v.z);
}

/*
 * Add vec3 a to vec3 b and return resulting vec3 (a+b).
 */
Vec3 addVec3(Vec3 a, Vec3 b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec4 addVec4(Vec4 a, Vec4 b) {
    return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.t + b.t);
}

Vec4 addVec4WithVec3(Vec4 a, Vec3 b) {
    return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.t);
}

Color addColor(Color a, Color b) {
    return Color(a.r + b.r, a.g + b.g, a.b + b.b);
}

/*
 * Subtract vec3 b from vec3 a and return resulting vec3 (a-b).
 */
Vec3 subtractVec3(Vec3 a, Vec3 b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec4 subtractVec4(Vec4 a, Vec4 b) {
    return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.t - b.t);
}

Color subtractColor(Color a, Color b) {
    return Color(a.r - b.r, a.g - b.g, a.b - b.b);
}

/*
 * Multiply each element of vec3 with scalar.
 */
Vec3 multiplyVec3WithScalar(Vec3 v, double c) {
    return Vec3(v.x * c, v.y * c, v.z * c);
}

Vec4 multiplyVec4WithScalar(Vec4 v, double c) {
    return Vec4(v.x * c, v.y * c, v.z * c, v.t * c);
}

Color multiplyColorWithScalar(Color v, double c) {
    return Color(v.r * c, v.g * c, v.b * c);
}

Vec3 divideVec3WithScalar(Vec3 v, double c) {
    return Vec3(v.x / c, v.y / c, v.z / c);
}

Vec4 divideVec4WithScalar(Vec4 v, double c) {
    return Vec4(v.x / c, v.y / c, v.z / c, v.t / c);
}

Color divideColorWithScalar(Color v, double c) {
    return Color(v.r / c, v.g / c, v.b / c);
}

/*
 * Prints elements in a vec3. Can be used for debugging purposes.
 */
void printVec3(Vec3 v) {
    std::cout << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
}

void printVec4(Vec4 v) {
    std::cout << "(" << v.x << "," << v.y << "," << v.z << "," << v.t << ")" << std::endl;
}

void printMatrix(Matrix4 matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix.values[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

/*
 * Check whether vec3 a and vec3 b are equal.
 * In case of equality, returns 1.
 * Otherwise, returns 0.
 */
int areEqualVec3(Vec3 a, Vec3 b) {
    /* if x difference, y difference and z difference is smaller than threshold, then they are equal */
    if ((ABS((a.x - b.x)) < EPSILON) && (ABS((a.y - b.y)) < EPSILON) && (ABS((a.z - b.z)) < EPSILON)) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * Returns an identity matrix (values on the diagonal are 1, others are 0).
 */
Matrix4 getIdentityMatrix() {
    Matrix4 result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                result.values[i][j] = 1.0;
            } else {
                result.values[i][j] = 0.0;
            }
        }
    }

    return result;
}

/*
 * Multiply matrices m1 (Matrix4) and m2 (Matrix4) and return the result matrix r (Matrix4).
 */
Matrix4 multiplyMatrixWithMatrix(Matrix4 m1, Matrix4 m2) {
    Matrix4 result;
    double total;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            total = 0;
            for (int k = 0; k < 4; k++) {
                total += m1.values[i][k] * m2.values[k][j];
            }

            result.values[i][j] = total;
        }
    }

    return result;
}

/*
 * Multiply matrix m (Matrix4) with vector v (vec4) and store the result in vector r (vec4).
 */
Vec4 multiplyMatrixWithVec4(Matrix4 m, Vec4 v) {
    double values[4];
    double total;

    for (int i = 0; i < 4; i++) {
        total = 0;
        for (int j = 0; j < 4; j++) {
            total += m.values[i][j] * v.getNthComponent(j);
        }
        values[i] = total;
    }

    return Vec4(values[0], values[1], values[2], values[3], v.colorId);
}