#ifndef LCERF_CAVE_HPP
#define LCERF_CAVE_HPP
#include <array>
#include <string>

#include "raylib.h"

#define CAVE_POINT_COUNT 2000

class Cave {
private:
    Model model{};
    std::array<Vector3, CAVE_POINT_COUNT> pointCloud{};

public:
    explicit Cave(const std::string& fileName);

    void drawPointCloud();
};


#endif //LCERF_CAVE_HPP
