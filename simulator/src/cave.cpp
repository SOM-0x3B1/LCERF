#include "../include/cave.hpp"

#include <random>

Cave::Cave() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-2.0, 2.0);

    for (auto & i : pointCloud)
        i = { .x = dist(mt), .y = dist(mt) / 2.0f + 1.0f, .z = dist(mt) };
}

void Cave::drawPointCloud() {
    for (auto point : pointCloud) {
        DrawCube(point,  0.01, 0.01, 0.01, BLUE);
    }
}