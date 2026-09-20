#include "../include/cave.hpp"
#include "../include/graphics.hpp"

#include <random>
#include <exception>
#include "raymath.h"

Chunk * Cave::GetChunkAt(ChunkCoord c) {
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

        Vector2 chunkPos = {.x = vertexPos.x, .y = vertexPos.y};
        Chunk* chunk = GetChunkAt(ChunkCoord(chunkPos, CHUNK_SIZE));
        chunk->AddPoint(vertexPos);
    }
}

Cave::Cave(const std::string& fileName, Graphics* graphics) {
    LoadCaveModel(fileName);
    this->graphics = graphics;
}

Cave::Cave(const std::string &fileName, Graphics* graphics, Vector3 offset) {
    modelBaseOffset = offset;
    LoadCaveModel(fileName);
    this->graphics = graphics;
}

Cave::~Cave() {
    UnloadModel(model);
}

void Cave::drawPointCloud() {
    //DrawModel(model, {1, -0.5, 1}, 1.0f, WHITE);
    //DrawModelWires(model, {1, -0.5, 1}, 1.0f, BLUE);
    //Graphics::drawModelPoints(model, modelBaseOffset, 1.0, BLUE);
    /**/
    auto chunkCoordOfTarget = ChunkCoord(graphics->getTarget(), CHUNK_SIZE);
    Chunk* chunk = GetChunkAt(chunkCoordOfTarget);
    const std::vector<Vector3> *chunkPoints = chunk->GetPoints();
    for (auto point : *chunkPoints) {
        DrawPoint3D(point, BLUE);
    }
}