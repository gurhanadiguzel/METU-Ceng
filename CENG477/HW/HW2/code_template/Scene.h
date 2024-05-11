#ifndef _SCENE_H_
#define _SCENE_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include "Camera.h"
#include "Color.h"
#include "Helpers.h"
#include "Matrix4.h"
#include "Mesh.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "Vec4.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Scene {
   public:
    Color backgroundColor;
    bool cullingEnabled;

    vector<vector<Color>> image;
    vector<vector<double>> depth;
    vector<Camera *> cameras;
    vector<Vec3 *> vertices;
    vector<Color *> colorsOfVertices;
    vector<Scaling *> scalings;
    vector<Rotation *> rotations;
    vector<Translation *> translations;
    vector<Mesh *> meshes;

    Scene(const char *xmlPath);

    void assignColorToPixel(int i, int j, Color c);
    void initializeImage(Camera *camera);
    int makeBetweenZeroAnd255(double value);
    void writeImageToPPMFile(Camera *camera);
    void convertPPMToPNG(string ppmFileName);
    void forwardRenderingPipeline(Camera *camera);
    Matrix4 getModelingTransformationMatrix(Mesh &mesh);
    vector<Vec4> getTransformedTriangleVertices(Triangle &triangle, Matrix4 &transformationMatrix);
    vector<Color> getTriangleVertexColors(Triangle &triangle);
    bool visible(double den, double num, double &tE, double &tL);
    void clipping(Camera *camera, Vec4 vertex1, Vec4 vertex2, Color color1, Color color2, Matrix4 viewportTransformationMatrix);
    void lineRasterization(Camera *camera, Vec4 vertex1, Vec4 vertex2, Color color1, Color color2, Matrix4 viewportTransformationMatrix);
    double lineEquation(double x, double y, double x1, double y1, double x2, double y2);
    void triangleRasterization(Camera *camera, vector<Vec4> transformedTriangleVertices, vector<Color> triangleVertexColors);
};

#endif
