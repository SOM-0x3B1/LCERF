#include "../include/cave.hpp"
#include "../include/graphics.hpp"

#include <random>
#include <exception>
#include "raymath.h"

void Cave::LoadCaveModel(const std::string &fileName) {
    std::string relPath = "resources/caves/" + fileName;
    model = LoadModel(relPath.c_str());
    mesh = model.meshes[0];
    pointCloud = std::vector<Vector3>(mesh.vertexCount);
    for (int i = 0; i < mesh.vertexCount; ++i) {
        Vector3 vertexPos = {
            .x = mesh.vertices[i * 3 + 0],
            .y = mesh.vertices[i * 3 + 1],
            .z = mesh.vertices[i * 3 + 2]
        };
        pointCloud[i] = vertexPos;
    }
}

Cave::Cave(const std::string& fileName, Graphics* graphics) {
    LoadCaveModel(fileName);
    this->graphics = graphics;
}

Cave::Cave(const std::string &fileName, Graphics* graphics, Vector3 offset) {
    modelBaseOffset = offset;
    LoadCaveModel(fileName);
    this->graphics = graphics;
}

Cave::~Cave() {
    UnloadModel(model);
}

void Cave::drawPointCloud() {
    //DrawModel(model, {1, -0.5, 1}, 1.0f, WHITE);
    //DrawModelWires(model, {1, -0.5, 1}, 1.0f, BLUE);
    Graphics::drawModelPoints(model, modelBaseOffset, 1.0, BLUE);
    /*for (auto point : pointCloud) {
        float d = graphics->getVectorDistanceFromTarget(point);
        if (d < 2.0)
            DrawCube(point,  0.01, 0.01, 0.01, BLUE);
    }*/
}
