#include "Scene.h"

/*
    Parses XML file
*/
Scene::Scene(const char *xmlPath) {
    const char *str;
    XMLDocument xmlDoc;
    XMLElement *xmlElement;

    xmlDoc.LoadFile(xmlPath);

    XMLNode *rootNode = xmlDoc.FirstChild();

    // read background color
    xmlElement = rootNode->FirstChildElement("BackgroundColor");
    str = xmlElement->GetText();
    sscanf(str, "%lf %lf %lf", &backgroundColor.r, &backgroundColor.g, &backgroundColor.b);

    // read culling
    xmlElement = rootNode->FirstChildElement("Culling");
    if (xmlElement != NULL) {
        str = xmlElement->GetText();

        if (strcmp(str, "enabled") == 0) {
            this->cullingEnabled = true;
        } else {
            this->cullingEnabled = false;
        }
    }

    // read cameras
    xmlElement = rootNode->FirstChildElement("Cameras");
    XMLElement *camElement = xmlElement->FirstChildElement("Camera");
    XMLElement *camFieldElement;
    while (camElement != NULL) {
        Camera *camera = new Camera();

        camElement->QueryIntAttribute("id", &camera->cameraId);

        // read projection type
        str = camElement->Attribute("type");

        if (strcmp(str, "orthographic") == 0) {
            camera->projectionType = ORTOGRAPHIC_PROJECTION;
        } else {
            camera->projectionType = PERSPECTIVE_PROJECTION;
        }

        camFieldElement = camElement->FirstChildElement("Position");
        str = camFieldElement->GetText();
        sscanf(str, "%lf %lf %lf", &camera->position.x, &camera->position.y, &camera->position.z);

        camFieldElement = camElement->FirstChildElement("Gaze");
        str = camFieldElement->GetText();
        sscanf(str, "%lf %lf %lf", &camera->gaze.x, &camera->gaze.y, &camera->gaze.z);

        camFieldElement = camElement->FirstChildElement("Up");
        str = camFieldElement->GetText();
        sscanf(str, "%lf %lf %lf", &camera->v.x, &camera->v.y, &camera->v.z);

        camera->gaze = normalizeVec3(camera->gaze);
        camera->u = crossProductVec3(camera->gaze, camera->v);
        camera->u = normalizeVec3(camera->u);

        camera->w = inverseVec3(camera->gaze);
        camera->v = crossProductVec3(camera->u, camera->gaze);
        camera->v = normalizeVec3(camera->v);

        camFieldElement = camElement->FirstChildElement("ImagePlane");
        str = camFieldElement->GetText();
        sscanf(str, "%lf %lf %lf %lf %lf %lf %d %d",
               &camera->left, &camera->right, &camera->bottom, &camera->top,
               &camera->near, &camera->far, &camera->horRes, &camera->verRes);

        camFieldElement = camElement->FirstChildElement("OutputName");
        str = camFieldElement->GetText();
        camera->outputFilename = string(str);

        this->cameras.push_back(camera);

        camElement = camElement->NextSiblingElement("Camera");
    }

    // read vertices
    xmlElement = rootNode->FirstChildElement("Vertices");
    XMLElement *vertexElement = xmlElement->FirstChildElement("Vertex");
    int vertexId = 1;

    while (vertexElement != NULL) {
        Vec3 *vertex = new Vec3();
        Color *color = new Color();

        vertex->colorId = vertexId;

        str = vertexElement->Attribute("position");
        sscanf(str, "%lf %lf %lf", &vertex->x, &vertex->y, &vertex->z);

        str = vertexElement->Attribute("color");
        sscanf(str, "%lf %lf %lf", &color->r, &color->g, &color->b);

        this->vertices.push_back(vertex);
        this->colorsOfVertices.push_back(color);

        vertexElement = vertexElement->NextSiblingElement("Vertex");

        vertexId++;
    }

    // read translations
    xmlElement = rootNode->FirstChildElement("Translations");
    XMLElement *translationElement = xmlElement->FirstChildElement("Translation");
    while (translationElement != NULL) {
        Translation *translation = new Translation();

        translationElement->QueryIntAttribute("id", &translation->translationId);

        str = translationElement->Attribute("value");
        sscanf(str, "%lf %lf %lf", &translation->tx, &translation->ty, &translation->tz);

        this->translations.push_back(translation);

        translationElement = translationElement->NextSiblingElement("Translation");
    }

    // read scalings
    xmlElement = rootNode->FirstChildElement("Scalings");
    XMLElement *scalingElement = xmlElement->FirstChildElement("Scaling");
    while (scalingElement != NULL) {
        Scaling *scaling = new Scaling();

        scalingElement->QueryIntAttribute("id", &scaling->scalingId);
        str = scalingElement->Attribute("value");
        sscanf(str, "%lf %lf %lf", &scaling->sx, &scaling->sy, &scaling->sz);

        this->scalings.push_back(scaling);

        scalingElement = scalingElement->NextSiblingElement("Scaling");
    }

    // read rotations
    xmlElement = rootNode->FirstChildElement("Rotations");
    XMLElement *rotationElement = xmlElement->FirstChildElement("Rotation");
    while (rotationElement != NULL) {
        Rotation *rotation = new Rotation();

        rotationElement->QueryIntAttribute("id", &rotation->rotationId);
        str = rotationElement->Attribute("value");
        sscanf(str, "%lf %lf %lf %lf", &rotation->angle, &rotation->ux, &rotation->uy, &rotation->uz);

        this->rotations.push_back(rotation);

        rotationElement = rotationElement->NextSiblingElement("Rotation");
    }

    // read meshes
    xmlElement = rootNode->FirstChildElement("Meshes");

    XMLElement *meshElement = xmlElement->FirstChildElement("Mesh");
    while (meshElement != NULL) {
        Mesh *mesh = new Mesh();

        meshElement->QueryIntAttribute("id", &mesh->meshId);

        // read projection type
        str = meshElement->Attribute("type");

        if (strcmp(str, "wireframe") == 0) {
            mesh->type = WIREFRAME_MESH;
        } else {
            mesh->type = SOLID_MESH;
        }

        // read mesh transformations
        XMLElement *meshTransformationsElement = meshElement->FirstChildElement("Transformations");
        XMLElement *meshTransformationElement = meshTransformationsElement->FirstChildElement("Transformation");

        while (meshTransformationElement != NULL) {
            char transformationType;
            int transformationId;

            str = meshTransformationElement->GetText();
            sscanf(str, "%c %d", &transformationType, &transformationId);

            mesh->transformationTypes.push_back(transformationType);
            mesh->transformationIds.push_back(transformationId);

            meshTransformationElement = meshTransformationElement->NextSiblingElement("Transformation");
        }

        mesh->numberOfTransformations = mesh->transformationIds.size();

        // read mesh faces
        char *row;
        char *cloneStr;
        int v1, v2, v3;
        XMLElement *meshFacesElement = meshElement->FirstChildElement("Faces");
        str = meshFacesElement->GetText();
        cloneStr = strdup(str);

        row = strtok(cloneStr, "\n");
        while (row != NULL) {
            int result = sscanf(row, "%d %d %d", &v1, &v2, &v3);

            if (result != EOF) {
                mesh->triangles.push_back(Triangle(v1, v2, v3));
            }
            row = strtok(NULL, "\n");
        }
        mesh->numberOfTriangles = mesh->triangles.size();
        this->meshes.push_back(mesh);

        meshElement = meshElement->NextSiblingElement("Mesh");
    }
}

void Scene::assignColorToPixel(int i, int j, Color c) {
    this->image[i][j].r = round(c.r);
    this->image[i][j].g = round(c.g);
    this->image[i][j].b = round(c.b);
}

/*
Initializes image with background color
*/
void Scene::initializeImage(Camera *camera) {
    if (this->image.empty()) {
        for (int i = 0; i < camera->horRes; i++) {
            vector<Color> rowOfColors;
            vector<double> rowOfDepths;

            for (int j = 0; j < camera->verRes; j++) {
                rowOfColors.push_back(this->backgroundColor);
                rowOfDepths.push_back(1.01);
            }

            this->image.push_back(rowOfColors);
            this->depth.push_back(rowOfDepths);
        }
    } else {
        for (int i = 0; i < camera->horRes; i++) {
            for (int j = 0; j < camera->verRes; j++) {
                assignColorToPixel(i, j, this->backgroundColor);
                this->depth[i][j] = 1.01;
                this->depth[i][j] = 1.01;
                this->depth[i][j] = 1.01;
            }
        }
    }
}

/*
    If given value is less than 0, converts value to 0.
    If given value is more than 255, converts value to 255.
    Otherwise returns value itself.
*/
int Scene::makeBetweenZeroAnd255(double value) {
    if (value >= 255.0)
        return 255;
    if (value <= 0.0)
        return 0;
    return (int)(value);
}

/*
    Writes contents of image (Color**) into a PPM file.
*/
void Scene::writeImageToPPMFile(Camera *camera) {
    ofstream fout;

    fout.open(camera->outputFilename.c_str());

    fout << "P3" << endl;
    fout << "# " << camera->outputFilename << endl;
    fout << camera->horRes << " " << camera->verRes << endl;
    fout << "255" << endl;

    for (int j = camera->verRes - 1; j >= 0; j--) {
        for (int i = 0; i < camera->horRes; i++) {
            fout << makeBetweenZeroAnd255(this->image[i][j].r) << " "
                 << makeBetweenZeroAnd255(this->image[i][j].g) << " "
                 << makeBetweenZeroAnd255(this->image[i][j].b) << " ";
        }
        fout << endl;
    }
    fout.close();
}

/*
    Converts PPM image in given path to PNG file, by calling ImageMagick's 'convert' command.
*/
void Scene::convertPPMToPNG(string ppmFileName) {
    string command;

    // TODO: Change implementation if necessary.
    // "./magick convert "
    command = "convert " + ppmFileName + " " + ppmFileName.substr(0, ppmFileName.length() - 4) + ".png";
    system(command.c_str());
}

Matrix4 Scene::getModelingTransformationMatrix(Mesh &mesh) {
    Matrix4 modelingTransformationMatrix = getIdentityMatrix();

    for (int i = 0; i < mesh.numberOfTransformations; i++) {
        int transformationIndex = mesh.transformationIds[i] - 1;
        char transformationType = mesh.transformationTypes[i];
        if (transformationType == 't') {
            modelingTransformationMatrix = translations[transformationIndex]->doTranslation(modelingTransformationMatrix);
        } else if (transformationType == 'r') {
            modelingTransformationMatrix = rotations[transformationIndex]->doRotations(modelingTransformationMatrix);
        } else if (transformationType == 's') {
            modelingTransformationMatrix = scalings[transformationIndex]->doScaling(modelingTransformationMatrix);
        }
    }

    return modelingTransformationMatrix;
}

vector<Vec4> Scene::getTransformedTriangleVertices(Triangle &triangle, Matrix4 &transformationMatrix) {
    vector<Vec4> transformedTriangleVertices;

    for (int index = 0; index < 3; index++) {
        Vec3 vertex = *vertices[triangle.vertexIds[index] - 1];
        Vec4 newVertex = Vec4(vertex.x, vertex.y, vertex.z, 1, vertex.colorId);
        newVertex = multiplyMatrixWithVec4(transformationMatrix, newVertex);
        transformedTriangleVertices.push_back(newVertex);
    }

    return transformedTriangleVertices;
}

vector<Color> Scene::getTriangleVertexColors(Triangle &triangle) {
    vector<Color> triangleVertexColors;

    for (int index = 0; index < 3; index++) {
        Vec3 vertex = *vertices[triangle.vertexIds[index] - 1];
        int colorIndex = vertex.colorId - 1;
        triangleVertexColors.push_back(*colorsOfVertices[colorIndex]);
    }

    return triangleVertexColors;
}

bool Scene::visible(double denumerator, double numerator, double &tE, double &tL) {
    double t = numerator / denumerator;
    if (denumerator > 0) {  // potentially entering
        if (t > tL)
            return false;

        if (t > tE)
            tE = t;

    } else if (denumerator < 0) {  // potentially leaving
        if (t < tE)
            return false;

        if (t < tL)
            tL = t;

    } else if (numerator > 0) {  // line parallel to edge
        return false;
    }
    return true;
}

void Scene::clipping(Camera *camera, Vec4 vertex1, Vec4 vertex2, Color color1, Color color2, Matrix4 viewportTransformationMatrix) {
    // Liang-Barsky Line Clipping Algorithm
    double tE = 0;
    double tL = 1;

    vertex1 = divideVec4WithScalar(vertex1, vertex1.t);
    vertex2 = divideVec4WithScalar(vertex2, vertex2.t);

    Vec3 dVector = Vec3(vertex2.x - vertex1.x, vertex2.y - vertex1.y, vertex2.z - vertex1.z);
    Color dColor = subtractColor(color2, color1);

    // Canonical Viewing Volume Min and Max
    double min = -1;
    double max = 1;

    // Check is visible
    if (visible(dVector.x, min - vertex1.x, tE, tL) &&   // left
        visible(-dVector.x, vertex1.x - max, tE, tL) &&  // right
        visible(dVector.y, min - vertex1.y, tE, tL) &&   // top
        visible(-dVector.y, vertex1.y - max, tE, tL) &&  // bottom
        visible(dVector.z, min - vertex1.z, tE, tL) &&   // front
        visible(-dVector.z, vertex1.z - max, tE, tL)) {  // back
        if (tL < 1) {
            vertex2 = addVec4WithVec3(vertex1, multiplyVec3WithScalar(dVector, tL));
            color2 = addColor(color1, multiplyColorWithScalar(dColor, tL));
        }
        if (tE > 0) {
            vertex1 = addVec4WithVec3(vertex1, multiplyVec3WithScalar(dVector, tE));
            color1 = addColor(color1, multiplyColorWithScalar(dColor, tE));
        }
        lineRasterization(camera, vertex1, vertex2, color1, color2, viewportTransformationMatrix);
    }
}

void Scene::lineRasterization(Camera *camera, Vec4 vertex1, Vec4 vertex2, Color color1, Color color2, Matrix4 viewportTransformationMatrix) {
    // Midpoint Algorithm
    vertex1 = multiplyMatrixWithVec4(viewportTransformationMatrix, vertex1);
    vertex2 = multiplyMatrixWithVec4(viewportTransformationMatrix, vertex2);
    vertex1.x = static_cast<int>(vertex1.x);
    vertex1.y = static_cast<int>(vertex1.y);
    vertex2.x = static_cast<int>(vertex2.x);
    vertex2.y = static_cast<int>(vertex2.y);

    double slope = (vertex2.y - vertex1.y) / (vertex2.x - vertex1.x);

    double x1x2 = abs(vertex2.x - vertex1.x);
    double y1y2 = abs(vertex2.y - vertex1.y);

    double minX = min(vertex1.x, vertex2.x) < 0 ? 0 : min(vertex1.x, vertex2.x);
    double minY = min(vertex1.y, vertex2.y) < 0 ? 0 : min(vertex1.y, vertex2.y);
    double maxX = max(vertex1.x, vertex2.x) < 0 ? 0 : max(vertex1.x, vertex2.x);
    double maxY = max(vertex1.y, vertex2.y) < 0 ? 0 : max(vertex1.y, vertex2.y);

    if (minX > camera->horRes - 1) minX = camera->horRes - 1;
    if (minY > camera->verRes - 1) minY = camera->verRes - 1;
    if (maxX > camera->horRes - 1) maxX = camera->horRes - 1;
    if (maxY > camera->verRes - 1) maxY = camera->verRes - 1;

    int x = (slope < 0) ? maxX : minX;
    int y = minY;

    double d, dEast, dNorthEast;
    Color tempColor1, tempColor2, color;

    if (slope >= 0 && slope <= 1) {  // NorthEast (speed x > speed y)
        d = (2 * y1y2) - x1x2;
        dEast = 2 * y1y2;
        dNorthEast = 2 * (y1y2 - x1x2);

        while (x <= maxX && y <= maxY) {
            double minDepth = (vertex1.z * abs(x - vertex2.x) + vertex2.z * abs(x - vertex1.x)) / x1x2;
            // printf("X value: %d Y value: %d  \n", x, y);

            if (minDepth <= depth[x][y]) {
                tempColor1 = divideColorWithScalar(multiplyColorWithScalar(color1, abs(x - vertex2.x)), x1x2);
                tempColor2 = divideColorWithScalar(multiplyColorWithScalar(color2, abs(x - vertex1.x)), x1x2);
                color = addColor(tempColor1, tempColor2);
                assignColorToPixel(x, y, color);
                depth[x][y] = minDepth;
            }

            if (d <= 0) {  // choose E
                d += dEast;
            } else {  // choose NE
                d += dNorthEast;
                y++;
            }
            x++;
        }

    } else if (slope > 1) {  // NorthEast (speed y > speed x)
        d = (2 * x1x2) - y1y2;
        dEast = 2 * x1x2;
        dNorthEast = 2 * (x1x2 - y1y2);

        while (y <= maxY && x <= maxX) {
            double minDepth = (vertex1.z * abs(y - vertex2.y) + vertex2.z * abs(y - vertex1.y)) / y1y2;
            // printf("X value: %d Y value: %d \n", x, y);

            if (minDepth <= depth[x][y]) {
                tempColor1 = divideColorWithScalar(multiplyColorWithScalar(color1, abs(y - vertex2.y)), y1y2);
                tempColor2 = divideColorWithScalar(multiplyColorWithScalar(color2, abs(y - vertex1.y)), y1y2);
                color = addColor(tempColor1, tempColor2);
                assignColorToPixel(x, y, color);
                depth[x][y] = minDepth;
            }

            if (d <= 0) {  // choose N
                d += dEast;
            } else {  // choose NE
                d += dNorthEast;
                x++;
            }
            y++;
        }

    } else if (slope < 0 && slope >= -1) {  // NorthWest (speed x > speed y )
        d = (2 * y1y2) - x1x2;
        dEast = 2 * y1y2;
        dNorthEast = 2 * (y1y2 - x1x2);

        while (x >= minX && y <= maxY) {
            double minDepth = (vertex1.z * abs(x - vertex2.x) + vertex2.z * abs(x - vertex1.x)) / x1x2;
            // printf("X value: %d Y value: %d  \n", x, y);

            if (minDepth <= depth[x][y]) {
                tempColor1 = divideColorWithScalar(multiplyColorWithScalar(color1, abs(x - vertex2.x)), x1x2);
                tempColor2 = divideColorWithScalar(multiplyColorWithScalar(color2, abs(x - vertex1.x)), x1x2);
                color = addColor(tempColor1, tempColor2);
                assignColorToPixel(x, y, color);
                depth[x][y] = minDepth;
            }

            if (d <= 0) {  // choose W
                d += dEast;
            } else {  // chose NW
                d += dNorthEast;
                y++;
            }
            x--;
        }
    } else if (slope < -1) {  // NorthWest (speed y > speed x )
        d = (2 * x1x2) - y1y2;
        dEast = 2 * x1x2;
        dNorthEast = 2 * (x1x2 - y1y2);

        while (y <= maxY && x >= minX) {
            double minDepth = (vertex1.z * abs(y - vertex2.y) + vertex2.z * abs(y - vertex1.y)) / y1y2;
            // printf("X value: %d Y value: %d  \n", x, y);

            if (minDepth <= depth[x][y]) {
                tempColor1 = divideColorWithScalar(multiplyColorWithScalar(color1, abs(y - vertex2.y)), y1y2);
                tempColor2 = divideColorWithScalar(multiplyColorWithScalar(color2, abs(y - vertex1.y)), y1y2);
                color = addColor(tempColor1, tempColor2);
                assignColorToPixel(x, y, color);
                depth[x][y] = minDepth;
            }

            if (d <= 0) {  // choose N
                d += dEast;
            } else {  // choose NW
                d += dNorthEast;
                x--;
            }
            y++;
        }
    }
}

double Scene::lineEquation(double x, double y, double x1, double y1, double x2, double y2) {
    return (x * (y1 - y2) + y * (x2 - x1) + (x1 * y2) - (y1 * x2));
}

void Scene::triangleRasterization(Camera *camera, vector<Vec4> transformedTriangleVertices, vector<Color> triangleVertexColors) {
    Vec4 vertex1 = transformedTriangleVertices[0];
    Vec4 vertex2 = transformedTriangleVertices[1];
    Vec4 vertex3 = transformedTriangleVertices[2];
    vertex1.x = static_cast<int>(vertex1.x);
    vertex1.y = static_cast<int>(vertex1.y);
    vertex2.x = static_cast<int>(vertex2.x);
    vertex2.y = static_cast<int>(vertex2.y);
    vertex3.x = static_cast<int>(vertex3.x);
    vertex3.y = static_cast<int>(vertex3.y);

    double minX = min(vertex1.x, min(vertex2.x, vertex3.x)) < 0 ? 0 : min(vertex1.x, min(vertex2.x, vertex3.x));
    double minY = min(vertex1.y, min(vertex2.y, vertex3.y)) < 0 ? 0 : min(vertex1.y, min(vertex2.y, vertex3.y));
    double maxX = max(vertex1.x, max(vertex2.x, vertex3.x)) < 0 ? 0 : max(vertex1.x, max(vertex2.x, vertex3.x));
    double maxY = max(vertex1.y, max(vertex2.y, vertex3.y)) < 0 ? 0 : max(vertex1.y, max(vertex2.y, vertex3.y));

    if (minX > camera->horRes - 1) minX = camera->horRes - 1;
    if (minY > camera->verRes - 1) minY = camera->verRes - 1;
    if (maxX > camera->horRes - 1) maxX = camera->horRes - 1;
    if (maxY > camera->verRes - 1) maxY = camera->verRes - 1;

    Color color1, color2, color3, color;
    double alpha, beta, gamma;

    double minDepth;
    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            alpha = lineEquation((double)x, (double)y, vertex2.x, vertex2.y, vertex3.x, vertex3.y) / lineEquation(vertex1.x, vertex1.y, vertex2.x, vertex2.y, vertex3.x, vertex3.y);
            beta = lineEquation((double)x, (double)y, vertex3.x, vertex3.y, vertex1.x, vertex1.y) / lineEquation(vertex2.x, vertex2.y, vertex3.x, vertex3.y, vertex1.x, vertex1.y);
            // gamma = getBaricentricCoordinates((double)x, (double)y, vertex1.x, vertex1.y, vertex2.x, vertex2.y) / getBaricentricCoordinates(vertex3.x, vertex3.y, vertex1.x, vertex1.y, vertex2.x, vertex2.y);
            gamma = 1 - (alpha + beta);
            minDepth = vertex1.z * alpha + vertex2.z * beta + vertex3.z * gamma;

            // If they are all positive then pixel center in the triangle and check depth value
            if (alpha >= 0 && beta >= 0 && gamma >= 0 && depth[x][y] > minDepth) {
                color1 = multiplyColorWithScalar(triangleVertexColors[0], alpha);
                color2 = multiplyColorWithScalar(triangleVertexColors[1], beta);
                color3 = multiplyColorWithScalar(triangleVertexColors[2], gamma);
                color = addColor(color1, addColor(color2, color3));
                assignColorToPixel(x, y, color);
                depth[x][y] = minDepth;
            }
        }
    }
}

/*
    Transformations, clipping, culling, rasterization are done here.
*/
void Scene::forwardRenderingPipeline(Camera *camera) {
    Matrix4 cameraTransformationMatrix = camera->getCameraTransformationMatrix();
    Matrix4 projectionTransformationMatrix = camera->getProjectionTransformationMatrix();
    Matrix4 viewportTransformationMatrix = camera->getViewportTransformationMatrix();

    for (auto mesh : this->meshes) {
        Matrix4 modelingTransformationMatrix = getModelingTransformationMatrix(*mesh);
        Matrix4 transformationMatrix = multiplyMatrixWithMatrix(cameraTransformationMatrix, modelingTransformationMatrix);
        transformationMatrix = multiplyMatrixWithMatrix(projectionTransformationMatrix, transformationMatrix);

        for (auto triangle : mesh->triangles) {
            // In Canonical Viewing Volume take depth values
            vector<double> depthBuffer;
            // Get colors of triangles
            vector<Color> triangleVertexColors = getTriangleVertexColors(triangle);
            // Get transformed vertices of triangles
            vector<Vec4> transformedTriangleVertices = getTransformedTriangleVertices(triangle, transformationMatrix);
            for (int i = 0; i < 3; i++) {
                transformedTriangleVertices[i] = divideVec4WithScalar(transformedTriangleVertices[i], transformedTriangleVertices[i].t);
                depthBuffer.push_back(transformedTriangleVertices[i].z);
            }

            // Check cullingEnabled
            if (cullingEnabled) {
                Vec3 vertex1 = Vec3(transformedTriangleVertices[0].x, transformedTriangleVertices[0].y, transformedTriangleVertices[0].z);
                Vec3 vertex2 = Vec3(transformedTriangleVertices[1].x, transformedTriangleVertices[1].y, transformedTriangleVertices[1].z);
                Vec3 vertex3 = Vec3(transformedTriangleVertices[2].x, transformedTriangleVertices[2].y, transformedTriangleVertices[2].z);

                Vec3 vector1 = subtractVec3(vertex2, vertex1);
                Vec3 vector2 = subtractVec3(vertex3, vertex1);

                Vec3 crossProduct = normalizeVec3(crossProductVec3(vector1, vector2));
                double dotProduct = dotProductVec3(crossProduct, vertex1);
                if (dotProduct < 0) {
                    continue;
                }
            }

            // Check Mesh Type
            if (mesh->type) {  // Type 1 for Solid
                for (int i = 0; i < 3; i++) {
                    transformedTriangleVertices[i] = multiplyMatrixWithVec4(viewportTransformationMatrix, transformedTriangleVertices[i]);
                }
                triangleRasterization(camera, transformedTriangleVertices, triangleVertexColors);

            } else {  // Type 0 for Wireframe
                clipping(camera, transformedTriangleVertices[0], transformedTriangleVertices[1], triangleVertexColors[0], triangleVertexColors[1], viewportTransformationMatrix);
                clipping(camera, transformedTriangleVertices[1], transformedTriangleVertices[2], triangleVertexColors[1], triangleVertexColors[2], viewportTransformationMatrix);
                clipping(camera, transformedTriangleVertices[2], transformedTriangleVertices[0], triangleVertexColors[2], triangleVertexColors[0], viewportTransformationMatrix);
            }
        }
    }
}
