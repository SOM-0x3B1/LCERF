#ifndef LCERF_REGION_HPP
#define LCERF_REGION_HPP

#include "raylib.h"
#include <vector>
#include "graphics.hpp"


class ChunkCoords {
public:
    const int chunkSize;
    int x;
    int y;
    explicit ChunkCoords(int x, int y);
    explicit ChunkCoords(Vector2 v, int chunkSize);
    explicit ChunkCoords(Vector3 v, int chunkSize);

    float distanceFrom(ChunkCoords c);
};


class Chunk {
private:
    const ChunkCoords coords;
    const int chunkSize;

    int fullPointCount;
    std::vector<Vector3> points;

    Model modelFull{};
    Model modelHalf{};
    Model modelQuarter{};
    Model modelMin{};

    Graphics* graphics;
    Mesh GenerateMesh(int resolutionDivider);

public:
    explicit Chunk(ChunkCoords coords, Graphics* graphics, int chunkSize);

    [[nodiscard]] const std::vector<Vector3> *GetPoints();

    void AddPoint(Vector3 point);
    void GenChunkModel();

    void DrawChunkModel(float chunkDistance);
};

#endif //LCERF_REGION_HPP
