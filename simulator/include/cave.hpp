#ifndef LCERF_CAVE_HPP
#define LCERF_CAVE_HPP

#include <string>
#include <vector>

#include "graphics.hpp"
#include "raylib.h"

#define CAVE_POINT_COUNT 2000

class Cave {
private:
    Model model{};
    Mesh mesh{};
    Vector3 modelBaseOffset{};
    std::vector<Vector3> pointCloud{};

    Graphics* graphics;

    void LoadCaveModel(const std::string& fileName);

public:
    explicit Cave(const std::string& fileName, Graphics* graphics);
    explicit Cave(const std::string& fileName, Graphics* graphics, Vector3 offset);
    ~Cave();

    void drawPointCloud();
};


#endif //LCERF_CAVE_HPP
