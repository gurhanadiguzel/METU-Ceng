#include "Camera.h"

Camera::Camera() {}

Camera::Camera(int cameraId,
               int projectionType,
               Vec3 position, Vec3 gaze,
               Vec3 u, Vec3 v, Vec3 w,
               double left, double right, double bottom, double top,
               double near, double far,
               int horRes, int verRes,
               std::string outputFilename) {
    this->cameraId = cameraId;
    this->projectionType = projectionType;
    this->position = position;
    this->gaze = gaze;
    this->u = u;
    this->v = v;
    this->w = w;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;
    this->horRes = horRes;
    this->verRes = verRes;
    this->outputFilename = outputFilename;
}

Camera::Camera(const Camera &other) {
    this->cameraId = other.cameraId;
    this->projectionType = other.projectionType;
    this->position = other.position;
    this->gaze = other.gaze;
    this->u = other.u;
    this->v = other.v;
    this->w = other.w;
    this->left = other.left;
    this->right = other.right;
    this->bottom = other.bottom;
    this->top = other.top;
    this->near = other.near;
    this->far = other.far;
    this->horRes = other.horRes;
    this->verRes = other.verRes;
    this->outputFilename = other.outputFilename;
}

std::ostream &operator<<(std::ostream &os, const Camera &c) {
    const char *camType = c.projectionType ? "perspective" : "orthographic";

    os << std::fixed << std::setprecision(6) << "Camera " << c.cameraId << " (" << camType << ") => pos: " << c.position << " gaze: " << c.gaze << std::endl
       << "\tu: " << c.u << " v: " << c.v << " w: " << c.w << std::endl
       << std::fixed << std::setprecision(3) << "\tleft: " << c.left << " right: " << c.right << " bottom: " << c.bottom << " top: " << c.top << std::endl
       << "\tnear: " << c.near << " far: " << c.far << " resolutions: " << c.horRes << "x" << c.verRes << " fileName: " << c.outputFilename;

    return os;
}

Matrix4 Camera::getCameraTransformationMatrix() {
    Matrix4 translationMatrix = getIdentityMatrix();
    Matrix4 rotationMatrix = getIdentityMatrix();

    translationMatrix.values[0][3] = (-1.0) * position.x;
    translationMatrix.values[1][3] = (-1.0) * position.y;
    translationMatrix.values[2][3] = (-1.0) * position.z;

    rotationMatrix.values[0][0] = u.x;
    rotationMatrix.values[0][1] = u.y;
    rotationMatrix.values[0][2] = u.z;
    rotationMatrix.values[1][0] = v.x;
    rotationMatrix.values[1][1] = v.y;
    rotationMatrix.values[1][2] = v.z;
    rotationMatrix.values[2][0] = w.x;
    rotationMatrix.values[2][1] = w.y;
    rotationMatrix.values[2][2] = w.z;

    return multiplyMatrixWithMatrix(rotationMatrix, translationMatrix);
}
Matrix4 Camera::getOrthographicProjectionTransformationMatrix() {
    Matrix4 orthographicProjectionTransformationMatrix = getIdentityMatrix();

    orthographicProjectionTransformationMatrix.values[0][0] = (2.0) / (right - left);
    orthographicProjectionTransformationMatrix.values[0][3] = -(right + left) / (right - left);
    orthographicProjectionTransformationMatrix.values[1][1] = (2.0) / (top - bottom);
    orthographicProjectionTransformationMatrix.values[1][3] = -(top + bottom) / (top - bottom);
    orthographicProjectionTransformationMatrix.values[2][2] = -(2.0) / (far - near);
    orthographicProjectionTransformationMatrix.values[2][3] = -(far + near) / (far - near);

    return orthographicProjectionTransformationMatrix;
}

Matrix4 Camera::getPerspectiveProjectionTransformationMatrix() {
    Matrix4 perspectiveProjectionTransformationMatrix = getIdentityMatrix();

    perspectiveProjectionTransformationMatrix.values[0][0] = (2.0 * near) / (right - left);
    perspectiveProjectionTransformationMatrix.values[0][2] = (right + left) / (right - left);
    perspectiveProjectionTransformationMatrix.values[1][1] = (2.0 * near) / (top - bottom);
    perspectiveProjectionTransformationMatrix.values[1][2] = (top + bottom) / (top - bottom);
    perspectiveProjectionTransformationMatrix.values[2][2] = -(far + near) / (far - near);
    perspectiveProjectionTransformationMatrix.values[2][3] = -(2.0 * far * near) / (far - near);
    perspectiveProjectionTransformationMatrix.values[3][2] = -1.0;
    perspectiveProjectionTransformationMatrix.values[3][3] = 0.0;

    return perspectiveProjectionTransformationMatrix;
}

Matrix4 Camera::getProjectionTransformationMatrix() {
    if (projectionType) {
        return getPerspectiveProjectionTransformationMatrix();
    } else {
        return getOrthographicProjectionTransformationMatrix();
    }
}
Matrix4 Camera::getViewportTransformationMatrix() {
    Matrix4 viewportTransformationMatrix = getIdentityMatrix();

    viewportTransformationMatrix.values[0][0] = horRes / (2.0);
    viewportTransformationMatrix.values[0][3] = (horRes - 1.0) / (2.0);
    viewportTransformationMatrix.values[1][1] = verRes / (2.0);
    viewportTransformationMatrix.values[1][3] = (verRes - 1.0) / (2.0);
    viewportTransformationMatrix.values[2][2] = (1.0) / (2.0);
    viewportTransformationMatrix.values[2][3] = (1.0) / (2.0);

    return viewportTransformationMatrix;
}