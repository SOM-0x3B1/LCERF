#include "../include/cave.hpp"
#include "../include/graphics.hpp"

#include <random>

Cave::Cave(const std::string& fileName) {
    std::string relPath = "resources/caves/" + fileName;
    model = LoadModel(relPath.c_str());

    /*for (auto & i : pointCloud)
        i = { .x = dist(mt), .y = dist(mt) / 2.0f + 1.0f, .z = dist(mt) };*/
}

void Cave::drawPointCloud() {
    //DrawModel(model, {1, -0.5, 1}, 1.0f, WHITE);
    DrawModelWires(model, {1, -0.5, 1}, 1.0f, BLUE);
    //Graphics::drawModelPoints(model, {1, -0.5, 1}, 1.0, RED);
    /*for (auto point : pointCloud) {
        DrawCube(point,  0.01, 0.01, 0.01, BLUE);
    }*/
}