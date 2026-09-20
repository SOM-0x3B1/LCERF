#ifndef LCERF_REGION_HPP
#define LCERF_REGION_HPP

#include "raylib.h"
#include <vector>
#include "graphics.hpp"

class Chunk {
private:
    const int chunkSize;
    std::vector<Vector3> points;
    Graphics* graphics;

public:
    explicit Chunk(Graphics* graphics, int chunkSize);

    [[nodiscard]] const std::vector<Vector3> *GetPoints();

    void AddPoint(Vector3 point);
};

class ChunkCoord {
public:
    const int chunkSize;
    int x;
    int y;
    explicit ChunkCoord(Vector2 v, int chunkSize);
    explicit ChunkCoord(Vector3 v, int chunkSize);
};

#endif //LCERF_REGION_HPP
