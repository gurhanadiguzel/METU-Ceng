#include "raytracer.h"

Plane generatePlane(const Camera& camera) {
    Plane plane;
    plane.cameraPosition = camera.position;
    plane.top = camera.near_plane.w;
    plane.bottom = camera.near_plane.z;
    plane.left = camera.near_plane.x;
    plane.right = camera.near_plane.y;

    plane.gazeVector = camera.gaze;
    plane.gazeVector = plane.gazeVector.normalize();
    plane.n_x = camera.image_width;
    plane.n_y = camera.image_height;

    plane.v = camera.up;
    plane.u = crossProduct(plane.gazeVector, plane.v).normalize();
    plane.m = camera.position + (plane.gazeVector * camera.near_distance);
    plane.q = plane.m + (plane.u * plane.left) + (plane.v * plane.top);

    return plane;
}

Ray generateRay(const Plane& plane, int y, int x) {
    double s_u = (x + 0.5) * (plane.right - plane.left) / plane.n_x;
    double s_v = (y + 0.5) * (plane.top - plane.bottom) / plane.n_y;

    Vec3f s = plane.q + (plane.u * s_u) - (plane.v * s_v);

    Ray ray;
    ray.origin = plane.cameraPosition;
    ray.direction = (s - plane.cameraPosition).normalize();

    return ray;
}

HitRecord triangleIntersection(const Ray& ray, const Vec3f& a, const Vec3f& b, const Vec3f& c, int material_id, int object_type, int object_index, double epsilon) {
    HitRecord hitRecord;
    hitRecord.hit = false;

    Vec3f origin = ray.origin;
    Vec3f direction = ray.direction;

    Vec3f ab = b - a;
    Vec3f ac = c - a;
    Vec3f ba = a - b;
    Vec3f ca = a - c;
    Vec3f oa = a - origin;

    double determinantA = matrixDeterminant(ba, ca, direction);
    if (determinantA == 0.0) {
        return hitRecord;
    }
    double t = matrixDeterminant(ba, ca, oa) / determinantA;
    double gamma = matrixDeterminant(ba, oa, direction) / determinantA;
    double beta = matrixDeterminant(oa, ca, direction) / determinantA;

    if (t <= 0.0 || gamma + epsilon < 0 || beta + epsilon < 0 || 1 < (beta + gamma - epsilon)) {
        return hitRecord;
    }

    hitRecord.t = t;
    hitRecord.hit = true;
    hitRecord.material_id = material_id;
    hitRecord.object_type = object_type;
    hitRecord.object_index = object_index;
    hitRecord.intersectionPoint = ray.origin + ray.direction * t;
    hitRecord.surfaceNormal = crossProduct(ab, ac).normalize();

    return hitRecord;
}

HitRecord sphereIntersection(const Ray& ray, const Sphere& sphere, const Vec3f& center, int object_index) {
    HitRecord hitRecord;
    hitRecord.hit = false;

    Vec3f origin = ray.origin;
    Vec3f direction = ray.direction;
    Vec3f co = origin - center;
    double radius = sphere.radius;

    double A = dotProduct(direction, direction);
    double B = dotProduct(direction, co) * 2;
    double C = dotProduct(co, co) - (radius * radius);
    double D = dotProduct(direction, co);

    double discriminant = (B * B) - (4 * A * C);
    double delta = sqrt(discriminant);

    if (discriminant >= 0) {
        double t1 = (-1 * B + delta) / (2 * A);
        double t2 = (-1 * B - delta) / (2 * A);
        double t = fmin(t1, t2);
        hitRecord.t = t;
        hitRecord.hit = true;
        hitRecord.material_id = sphere.material_id;
        hitRecord.object_type = 2;
        hitRecord.object_index = object_index;
        hitRecord.intersectionPoint = ray.origin + ray.direction * t;
        hitRecord.surfaceNormal = hitRecord.intersectionPoint - center;
        hitRecord.surfaceNormal = hitRecord.surfaceNormal / radius;
    }

    return hitRecord;
}

HitRecord findRaySceneIntersection(const Scene& scene, const Ray& ray, const vector<Triangle>& triangleList, const vector<Mesh>& meshList, bool isReflection) {
    HitRecord hitRecord;
    hitRecord.hit = false;
    hitRecord.t = numeric_limits<double>::max();
    double epsilon = numeric_limits<double>::epsilon();
    int numberOfSpheres = scene.spheres.size();
    int numberOfMeshes, numberOfTriangles;

    if (isReflection) {
        numberOfMeshes = scene.meshes.size();
        numberOfTriangles = scene.triangles.size();

    } else {
        numberOfMeshes = meshList.size();
        numberOfTriangles = triangleList.size();
    }

    /* CALCULATE INTERSECT WITH MESHES  */
    int object_index = 0;
    for (int meshIndex = 0; meshIndex < numberOfMeshes; meshIndex++) {
        Mesh mesh;
        if (isReflection) {
            mesh = scene.meshes[meshIndex];

        } else {
            mesh = meshList[meshIndex];
        }

        int numberOfFaces = mesh.faces.size();
        for (int faceIndex = 0; faceIndex < numberOfFaces; faceIndex++) {
            Face face = mesh.faces[faceIndex];
            Vec3f indice0 = scene.vertex_data[face.v0_id - 1];
            Vec3f indice1 = scene.vertex_data[face.v1_id - 1];
            Vec3f indice2 = scene.vertex_data[face.v2_id - 1];

            HitRecord tempHitRecord = triangleIntersection(ray, indice0, indice1, indice2, mesh.material_id, 0, object_index, epsilon);
            object_index++;

            if (tempHitRecord.hit && tempHitRecord.t < hitRecord.t && tempHitRecord.t >= 0) {
                hitRecord.t = tempHitRecord.t;
                hitRecord.hit = tempHitRecord.hit;
                hitRecord.material_id = tempHitRecord.material_id;
                hitRecord.object_index = tempHitRecord.object_index;
                hitRecord.object_type = tempHitRecord.object_type;
                hitRecord.intersectionPoint = tempHitRecord.intersectionPoint;
                hitRecord.surfaceNormal = tempHitRecord.surfaceNormal;
            }
        }
    }

    /* CALCULATE INTERSECT WITH TRIANGLES  */
    for (int triangleIndex = 0; triangleIndex < numberOfTriangles; triangleIndex++) {
        Triangle triangle;
        if (isReflection) {
            triangle = scene.triangles[triangleIndex];

        } else {
            triangle = triangleList[triangleIndex];
        }
        Vec3f indice0 = scene.vertex_data[triangle.indices.v0_id - 1];
        Vec3f indice1 = scene.vertex_data[triangle.indices.v1_id - 1];
        Vec3f indice2 = scene.vertex_data[triangle.indices.v2_id - 1];

        HitRecord tempHitRecord = triangleIntersection(ray, indice0, indice1, indice2, triangle.material_id, 1, triangleIndex, epsilon);

        if (tempHitRecord.hit && tempHitRecord.t < hitRecord.t && tempHitRecord.t >= 0) {
            hitRecord.t = tempHitRecord.t;
            hitRecord.hit = tempHitRecord.hit;
            hitRecord.material_id = tempHitRecord.material_id;
            hitRecord.object_index = tempHitRecord.object_index;
            hitRecord.object_type = tempHitRecord.object_type;
            hitRecord.intersectionPoint = tempHitRecord.intersectionPoint;
            hitRecord.surfaceNormal = tempHitRecord.surfaceNormal;
        }
    }

    /* CALCULATE  INTERSECT WITH SPHERES */
    for (int sphereIndex = 0; sphereIndex < numberOfSpheres; sphereIndex++) {
        Sphere sphere = scene.spheres[sphereIndex];
        Vec3f centerOfSphere = scene.vertex_data[sphere.center_vertex_id - 1];

        HitRecord tempHitRecord = sphereIntersection(ray, sphere, centerOfSphere, sphereIndex);

        if (tempHitRecord.hit && tempHitRecord.t < hitRecord.t && tempHitRecord.t >= 0) {
            hitRecord.t = tempHitRecord.t;
            hitRecord.hit = tempHitRecord.hit;
            hitRecord.material_id = tempHitRecord.material_id;
            hitRecord.object_index = tempHitRecord.object_index;
            hitRecord.object_type = tempHitRecord.object_type;
            hitRecord.intersectionPoint = tempHitRecord.intersectionPoint;
            hitRecord.surfaceNormal = tempHitRecord.surfaceNormal;
        }
    }

    return hitRecord;
}

bool findShadowIntersection(const Scene& scene, const Ray& ray, double tLight) {
    double epsilon = scene.shadow_ray_epsilon;
    /* CALCULATE SHADOW RAY HIT WITH MESHES  */
    int numberOfMeshes = scene.meshes.size();
    for (int meshIndex = 0; meshIndex < numberOfMeshes; meshIndex++) {
        Mesh mesh = scene.meshes[meshIndex];
        int numberOfFaces = mesh.faces.size();
        for (int faceIndex = 0; faceIndex < numberOfFaces; faceIndex++) {
            Face face = mesh.faces[faceIndex];
            Vec3f indice0 = scene.vertex_data[face.v0_id - 1];
            Vec3f indice1 = scene.vertex_data[face.v1_id - 1];
            Vec3f indice2 = scene.vertex_data[face.v2_id - 1];

            HitRecord tempHitRecord = triangleIntersection(ray, indice0, indice1, indice2, mesh.material_id, 0, meshIndex, epsilon);

            if (tempHitRecord.hit && tLight > tempHitRecord.t && tempHitRecord.t >= 0) {
                return true;
            }
        }
    }

    /* CALCULATE SHADOW RAY HIT WITH TRIANGLES  */
    int numberOfTriangles = scene.triangles.size();
    for (int triangleIndex = 0; triangleIndex < numberOfTriangles; triangleIndex++) {
        Triangle triangle = scene.triangles[triangleIndex];
        Vec3f indice0 = scene.vertex_data[triangle.indices.v0_id - 1];
        Vec3f indice1 = scene.vertex_data[triangle.indices.v1_id - 1];
        Vec3f indice2 = scene.vertex_data[triangle.indices.v2_id - 1];

        HitRecord tempHitRecord = triangleIntersection(ray, indice0, indice1, indice2, triangle.material_id, 1, triangleIndex, epsilon);

        if (tempHitRecord.hit && tLight > tempHitRecord.t && tempHitRecord.t >= 0) {
            return true;
        }
    }
    /* CALCULATE SHADOW RAY HIT WITH SPHERES */
    int numberOfSpheres = scene.spheres.size();
    for (int sphereIndex = 0; sphereIndex < numberOfSpheres; sphereIndex++) {
        Sphere sphere = scene.spheres[sphereIndex];
        Vec3f centerOfSphere = scene.vertex_data[sphere.center_vertex_id - 1];

        HitRecord tempHitRecord = sphereIntersection(ray, sphere, centerOfSphere, sphereIndex);

        if (tempHitRecord.hit && tLight > tempHitRecord.t && tempHitRecord.t >= 0) {
            return true;
        }
    }

    return false;
}

Vec3f findIrradiance(const PointLight& light, const HitRecord& hitRecord) {
    Vec3f distanceVector = light.position - hitRecord.intersectionPoint;
    double distanceSquare = powf(distanceVector.length(), 2);

    Vec3f irradiance = {0, 0, 0};
    if (distanceSquare == 0.0f) {
        return irradiance;
    }

    irradiance = light.intensity / distanceSquare;
    return irradiance;
}

Vec3f findDiffuseShading(const Vec3f& surfaceNormal, const Material& material, const Vec3f w_i, const Vec3f irradiance) {
    double cosTheta = max(0.0, dotProduct(w_i, surfaceNormal));
    Vec3f diffuse = material.diffuse * cosTheta;

    Vec3f diffuseShading;
    diffuseShading.x = irradiance.x * diffuse.x;
    diffuseShading.y = irradiance.y * diffuse.y;
    diffuseShading.z = irradiance.z * diffuse.z;

    return diffuseShading;
}

Vec3f findSpecularShading(const Vec3f& surfaceNormal, const Material& material, const Vec3f w_i, const Vec3f w_o, const Vec3f irradiance, const Ray ray) {
    // Vec3f halfVector = (w_i + w_o).normalize();
    Vec3f halfVector = (w_i - ray.direction).normalize();

    double cosAlpha = max(0.0, dotProduct(halfVector, surfaceNormal));
    double phongOp = powf(cosAlpha, material.phong_exponent);
    Vec3f specular = material.specular * phongOp;

    Vec3f specularShading;
    specularShading.x = irradiance.x * specular.x;
    specularShading.y = irradiance.y * specular.y;
    specularShading.z = irradiance.z * specular.z;

    return specularShading;
}

Vec3f applyShading(const Scene& scene, const Ray& ray, const Camera& camera, const HitRecord& hitRecord, int depth, const vector<Triangle>& triangleList, const vector<Mesh>& meshList) {
    Vec3f pixelColor = {0, 0, 0};
    Material material = scene.materials[hitRecord.material_id - 1];
    Vec3f surfaceNormal = hitRecord.surfaceNormal;

    Vec3f w_o = (camera.position - hitRecord.intersectionPoint).normalize();

    pixelColor.x = material.ambient.x * scene.ambient_light.x;
    pixelColor.y = material.ambient.y * scene.ambient_light.y;
    pixelColor.z = material.ambient.z * scene.ambient_light.z;

    int numberOfLights = scene.point_lights.size();
    for (int lightIndex = 0; lightIndex < numberOfLights; lightIndex++) {
        PointLight light = scene.point_lights[lightIndex];

        Vec3f w_i = (light.position - hitRecord.intersectionPoint).normalize();

        Ray shadowRay;
        shadowRay.origin = hitRecord.intersectionPoint + surfaceNormal * scene.shadow_ray_epsilon;
        shadowRay.direction = w_i;

        double tLight = (light.position - shadowRay.origin).x / shadowRay.direction.x;
        bool shadowFlag = findShadowIntersection(scene, shadowRay, tLight);

        if (!shadowFlag || (shadowFlag && (light.position == camera.position))) {
            Vec3f irradiance = findIrradiance(light, hitRecord);
            Vec3f diffuseShading = findDiffuseShading(surfaceNormal, material, w_i, irradiance);
            Vec3f specularShading = findSpecularShading(surfaceNormal, material, w_i, w_o, irradiance, ray);
            pixelColor = pixelColor + diffuseShading + specularShading;
        }
    }

    if (material.is_mirror && depth > 0) {
        Vec3f reflectionColor = {0, 0, 0};
        Vec3f w_r = ray.direction - (surfaceNormal * 2 * dotProduct(ray.direction, surfaceNormal));
        w_r = w_r.normalize();

        Ray reflectionRay;
        reflectionRay.origin = hitRecord.intersectionPoint + surfaceNormal * scene.shadow_ray_epsilon;
        reflectionRay.direction = w_r;
        HitRecord reflectionHitRecord = findRaySceneIntersection(scene, reflectionRay, triangleList, meshList, true);

        if (reflectionHitRecord.hit && (reflectionHitRecord.object_index != hitRecord.object_index || reflectionHitRecord.object_type != hitRecord.object_type)) {
            reflectionColor = renderPixelColor(scene, reflectionRay, camera, reflectionHitRecord, depth - 1, triangleList, meshList);
            pixelColor.x += (reflectionColor.x * material.mirror.x);
            pixelColor.y += (reflectionColor.y * material.mirror.y);
            pixelColor.z += (reflectionColor.z * material.mirror.z);
        }
    }

    return pixelColor;
}

Vec3f renderPixelColor(const Scene& scene, const Ray& ray, const Camera& camera, const HitRecord& hitRecord, int depth, const vector<Triangle>& triangleList, const vector<Mesh>& meshList) {
    Vec3f pixelColor = {0, 0, 0};
    Vec3i backgroundColor = scene.background_color;

    if (hitRecord.hit) {
        return applyShading(scene, ray, camera, hitRecord, depth, triangleList, meshList);

    } else if (depth == scene.max_recursion_depth) {
        pixelColor.x = double(backgroundColor.x);
        pixelColor.y = double(backgroundColor.y);
        pixelColor.z = double(backgroundColor.z);
        return pixelColor;
    } else {
        return pixelColor;
    }
}

vector<Triangle> backFaceCullingTriangle(const Scene& scene, int cameraIndex) {
    Camera camera = scene.cameras[cameraIndex];
    int numberOfTriangles = scene.triangles.size();
    Vec3f cameraPosition = camera.position;
    Vec3f triangleCenter, cameraToCenter;
    Vec3f indice0, indice1, indice2;
    double backFace;
    vector<Triangle> triangleList;

    for (int triangleIndex = 0; triangleIndex < numberOfTriangles; triangleIndex++) {
        Triangle triangle = scene.triangles[triangleIndex];
        indice0 = scene.vertex_data[triangle.indices.v0_id - 1];
        indice1 = scene.vertex_data[triangle.indices.v1_id - 1];
        indice2 = scene.vertex_data[triangle.indices.v2_id - 1];
        Vec3f ab = indice1 - indice0;
        Vec3f ac = indice2 - indice0;
        Vec3f surfaceNormal = crossProduct(ab, ac);
        triangleCenter = (indice0 + indice1 + indice2) / 3.0;
        cameraToCenter = (triangleCenter - cameraPosition).normalize();
        backFace = dotProduct(surfaceNormal, cameraToCenter);
        if (backFace <= 0) {
            triangleList.push_back(triangle);
        }
    }
    return triangleList;
}

vector<Mesh> backFaceCullingMesh(const Scene& scene, int cameraIndex) {
    Camera camera = scene.cameras[cameraIndex];
    Vec3f cameraPosition = camera.position;
    Vec3f faceCenter, cameraToCenter;
    double backFace;
    vector<Mesh> meshList;

    int numberOfMeshes = scene.meshes.size();
    for (int meshIndex = 0; meshIndex < numberOfMeshes; meshIndex++) {
        Mesh mesh = scene.meshes[meshIndex];
        int numberOfFaces = mesh.faces.size();
        vector<Face> faceList;
        for (int faceIndex = 0; faceIndex < numberOfFaces; faceIndex++) {
            Face face = mesh.faces[faceIndex];
            Vec3f indice0 = scene.vertex_data[face.v0_id - 1];
            Vec3f indice1 = scene.vertex_data[face.v1_id - 1];
            Vec3f indice2 = scene.vertex_data[face.v2_id - 1];
            Vec3f ab = indice1 - indice0;
            Vec3f ac = indice2 - indice0;
            Vec3f surfaceNormal = crossProduct(ab, ac).normalize();
            faceCenter = (indice0 + indice1 + indice2) / 3.0;
            cameraToCenter = (faceCenter - cameraPosition).normalize();
            backFace = dotProduct(surfaceNormal, cameraToCenter);
            if (backFace <= 0) {
                faceList.push_back(face);
            }
        }
        Mesh newMesh;
        newMesh.faces = faceList;
        newMesh.material_id = mesh.material_id;
        meshList.push_back(newMesh);
    }
    return meshList;
}

void* rayProcess(void* data) {
    ThreadData* threadData = (ThreadData*)data;
    const Scene& scene = threadData->scene;
    const Camera& camera = threadData->camera;
    const Plane& plane = threadData->plane;
    const vector<Triangle>& triangleList = threadData->triangleList;
    const vector<Mesh>& meshList = threadData->meshList;
    const int y = threadData->y;
    const int x = threadData->x;

    // GENERATE RAY
    Ray ray = generateRay(plane, y, x);

    // HANDLE WITH RAY INTERSECTION
    HitRecord hitRecord = findRaySceneIntersection(scene, ray, triangleList, meshList, false);

    // RENDER PIXEL COLOR
    Vec3f pixelColor = renderPixelColor(scene, ray, camera, hitRecord, scene.max_recursion_depth, triangleList, meshList);

    return new Vec3f(pixelColor);
}

int main(int argc, char* argv[]) {
    // Sample usage for reading an XML scene file

    Scene scene;
    scene.loadFromXml(argv[1]);
    unsigned char* image = nullptr;
    int numberOfCameras = scene.cameras.size();
    int numberOfThreads = 4;
    pthread_t threads[numberOfThreads];

    for (int cameraIndex = 0; cameraIndex < numberOfCameras; cameraIndex++) {
        const Camera& camera = scene.cameras[cameraIndex];
        const Plane plane = generatePlane(camera);

        const vector<Triangle> triangleList = backFaceCullingTriangle(scene, cameraIndex);
        const vector<Mesh> meshList = backFaceCullingMesh(scene, cameraIndex);

        int width = camera.image_width;
        int height = camera.image_height;
        image = new unsigned char[width * height * 3];
        int pixelNumber = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x += numberOfThreads) {
                ThreadData threadData[numberOfThreads];
                vector<Vec3f*> colors(numberOfThreads);

                for (int i = 0; i < numberOfThreads; i++) {
                    threadData[i] = {scene, camera, plane, triangleList, meshList, y, x + i};
                    pthread_create(&threads[i], NULL, rayProcess, &threadData[i]);
                }

                for (int i = 0; i < numberOfThreads; i++) {
                    pthread_join(threads[i], (void**)&colors[i]);
                }

                for (int i = 0; i < numberOfThreads; i++) {
                    image[pixelNumber++] = min(255.0, round(colors[i]->x));
                    image[pixelNumber++] = min(255.0, round(colors[i]->y));
                    image[pixelNumber++] = min(255.0, round(colors[i]->z));
                }
            }
        }
        write_ppm(camera.image_name.c_str(), image, width, height);
    }
    return 0;
}
