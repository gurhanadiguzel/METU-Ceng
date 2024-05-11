#include "Translation.h"

Translation::Translation() {
    this->translationId = -1;
    this->tx = 0.0;
    this->ty = 0.0;
    this->tz = 0.0;
}

Translation::Translation(int translationId, double tx, double ty, double tz) {
    this->translationId = translationId;
    this->tx = tx;
    this->ty = ty;
    this->tz = tz;
}

std::ostream &operator<<(std::ostream &os, const Translation &t) {
    os << std::fixed << std::setprecision(3) << "Translation " << t.translationId << " => [" << t.tx << ", " << t.ty << ", " << t.tz << "]";
    return os;
}

Matrix4 Translation::doTranslation(Matrix4 matrix) {
    Matrix4 translationMatrix = getIdentityMatrix();
    translationMatrix.values[0][3] = tx;
    translationMatrix.values[1][3] = ty;
    translationMatrix.values[2][3] = tz;
    return multiplyMatrixWithMatrix(translationMatrix, matrix);
}