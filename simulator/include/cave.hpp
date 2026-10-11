#ifndef LCERF_CAVE_HPP
#define LCERF_CAVE_HPP

#include <string>
#include <array>

#include "graphics.hpp"
#include "raylib.h"
#include "chunk.hpp"

constexpr float CHUNK_SIZE = 0.5;
constexpr int CHUNK_COUNT_X = 200;
constexpr int CHUNK_COUNT_Y = 200;

class Cave {
private:
    Model model{};
    Mesh mesh{};
    Vector3 modelBaseOffset{};
    Graphics* graphics;

    std::array<Chunk*, CHUNK_COUNT_X * CHUNK_COUNT_Y> chunks{};

    void loadCaveModel(const std::string& fileName);
    void getChunksInBox(Vector3 center, float width, float height, float length, std::vector<Chunk*>* result);
    static inline bool isPointInBox(Vector3 p, Vector3 center, float width, float height, float length);

public:
    explicit Cave(const std::string& fileName, Graphics* graphics, Vector3 offset);
    ~Cave();

    float getChunkSize();
    Chunk* getChunkAt(ChunkCoords c);
    Chunk* getChunkAt(Vector3 v);

    float getAverageYValueInRectangle(Vector3 center, Vector3 offset, float width, float height, float length);
    float getMaxYValueInRectangle(Vector3 center, Vector3 offset, float width, float height, float length);
    RayCollision getRayCollision(Ray ray);

    void drawPointCloud();
};

#endif //LCERF_CAVE_HPP
