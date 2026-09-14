#ifndef LCERF_CAVE_HPP
#define LCERF_CAVE_HPP
#include <array>

#include "raylib.h"

#define CAVE_POINT_COUNT 2000

class Cave {
private:
    std::array<Vector3, CAVE_POINT_COUNT> pointCloud{};

public:
    Cave();

    void drawPointCloud();
};


#endif //LCERF_CAVE_HPP
