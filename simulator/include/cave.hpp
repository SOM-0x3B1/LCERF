#ifndef LCERF_CAVE_HPP
#define LCERF_CAVE_HPP

#include <string>
#include <array>

#include "graphics.hpp"
#include "raylib.h"
#include "chunk.hpp"

constexpr int CHUNK_SIZE = 1;
constexpr int CHUNK_COUNT_X = 100;
constexpr int CHUNK_COUNT_Y = 100;

class Cave {
private:
    Model model{};
    Mesh mesh{};
    Vector3 modelBaseOffset{};

    std::array<Chunk*, CHUNK_COUNT_X * CHUNK_COUNT_Y> chunks{};
    Chunk* GetChunkAt(ChunkCoords c);

    Graphics* graphics;

    void LoadCaveModel(const std::string& fileName);

public:
    explicit Cave(const std::string& fileName, Graphics* graphics, Vector3 offset);
    ~Cave();

    void drawPointCloud();
};

#endif //LCERF_CAVE_HPP
