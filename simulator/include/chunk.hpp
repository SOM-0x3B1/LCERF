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
};


class Chunk {
private:
    const ChunkCoords coords;
    const int chunkSize;

    int pointCount;
    std::vector<Vector3> points;

    Model model{};
    Graphics* graphics;
    Mesh GenerateMesh();

public:
    explicit Chunk(ChunkCoords coords, Graphics* graphics, int chunkSize);

    [[nodiscard]] const std::vector<Vector3> *GetPoints();

    void AddPoint(Vector3 point);
    void GenChunkModel();

    void DrawChunkModel();
};

#endif //LCERF_REGION_HPP
