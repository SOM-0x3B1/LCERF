#include "../include/cave.hpp"
#include "../include/graphics.hpp"

#include <random>
#include <exception>
#include "raymath.h"

Chunk* Cave::GetChunkAt(ChunkCoords c) {
    c.x += CHUNK_COUNT_X / 2;
    c.y += CHUNK_COUNT_Y / 2;
    return chunks[c.y * CHUNK_COUNT_X + c.x];
}

void Cave::LoadCaveModel(const std::string &fileName) {
    std::string relPath = "resources/caves/" + fileName;
    model = LoadModel(relPath.c_str());

    mesh = model.meshes[0];
    for (int i = 0; i < mesh.vertexCount; ++i) {
        Vector3 vertexPos = {
            .x = mesh.vertices[i * 3 + 0],
            .y = mesh.vertices[i * 3 + 1],
            .z = mesh.vertices[i * 3 + 2]
        };

        Vector2 chunkPos = {.x = vertexPos.x, .y = vertexPos.z};
        Chunk* chunk = GetChunkAt(ChunkCoords(chunkPos, CHUNK_SIZE));
        chunk->AddPoint(vertexPos);
    }
}

Cave::Cave(const std::string &fileName, Graphics* graphics, Vector3 offset) {
    for (int x = 0; x < CHUNK_COUNT_X; ++x) {
        for (int y = 0; y < CHUNK_COUNT_Y; ++y) {
            auto chunkCoords = ChunkCoords(x - CHUNK_COUNT_X / 2, y - CHUNK_COUNT_Y / 2);
            chunks[y * CHUNK_COUNT_X + x] = new Chunk(chunkCoords, graphics, CHUNK_SIZE);
        }
    }

    modelBaseOffset = offset;
    LoadCaveModel(fileName);
    this->graphics = graphics;

    for (int i = 0; i < CHUNK_COUNT_X * CHUNK_COUNT_Y; ++i)
        chunks[i]->GenChunkModel();
}

Cave::~Cave() {
    UnloadModel(model);
}

void Cave::drawPointCloud() {
    auto chunkCoordOfTarget = ChunkCoords(graphics->getTarget(), CHUNK_SIZE);
    int renderDistance = graphics->getRenderDistance();
    int xStart = std::max(chunkCoordOfTarget.x - renderDistance, -CHUNK_COUNT_X/2);
    int xEnd= std::min(chunkCoordOfTarget.x + renderDistance, CHUNK_COUNT_X/2);
    int yStart = std::max(chunkCoordOfTarget.y - renderDistance, -CHUNK_COUNT_Y/2);
    int yEnd= std::min(chunkCoordOfTarget.y + renderDistance, CHUNK_COUNT_Y/2);

    for (int x = xStart; x < xEnd; ++x) {
        for (int y = yStart; y < yEnd; ++y) {
            auto currCoords = ChunkCoords(x, y);
            float chunkDistance = chunkCoordOfTarget.distanceFrom(currCoords);
            Chunk* chunk = GetChunkAt(currCoords);
            chunk->DrawChunkModel(chunkDistance);
        }
    }
}