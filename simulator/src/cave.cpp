#include "../include/cave.hpp"
#include "../include/graphics.hpp"

#include <random>
#include <exception>
#include "raymath.h"

void Cave::loadCaveModel(const std::string &fileName) {
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
        Chunk* chunk = getChunkAt(ChunkCoords(chunkPos, CHUNK_SIZE));
        chunk->AddPoint(vertexPos);
    }
}

void Cave::getChunksInBox(Vector3 center, float width, float height, float length, std::vector<Chunk*>* result) {
    float minX = center.x - width;
    float maxX = center.x + width;
    float minZ = center.z - length;
    float maxZ = center.z + length;
    float chunkSize = CHUNK_SIZE;

    for (float x = minX; x <= maxX; x += chunkSize / 2.0f) {
        for (float z = minZ; z <= maxZ; z += chunkSize / 2.0f) {
            Chunk* currChunk = getChunkAt(ChunkCoords(Vector2(x, z), chunkSize));
            if (std::find(result->begin(), result->end(), currChunk) == result->end()) {
                result->push_back(currChunk);
            }
        }
    }
}

bool Cave::isPointInBox(Vector3 p, Vector3 center, float width, float height, float length) {
    return (p.y < center.y + height && p.y > center.y - height &&
                        p.x < center.x + width && p.x > center.x - width &&
                        p.z < center.z + length && p.z > center.z - length);
}

RayCollision Cave::getRayCollision(Ray ray) {
    return GetRayCollisionMesh(ray, model.meshes[0], model.transform);
}

Cave::Cave(const std::string &fileName, Graphics* graphics, Vector3 offset) {
    for (int x = 0; x < CHUNK_COUNT_X; ++x) {
        for (int y = 0; y < CHUNK_COUNT_Y; ++y) {
            auto chunkCoords = ChunkCoords(x - CHUNK_COUNT_X / 2, y - CHUNK_COUNT_Y / 2);
            chunks[y * CHUNK_COUNT_X + x] = new Chunk(chunkCoords, graphics, CHUNK_SIZE);
        }
    }

    modelBaseOffset = offset;
    loadCaveModel(fileName);
    this->graphics = graphics;

    for (int i = 0; i < CHUNK_COUNT_X * CHUNK_COUNT_Y; ++i)
        chunks[i]->GenChunkModel();
}

Cave::~Cave() {
    UnloadModel(model);
    for (int i = 0; i < CHUNK_COUNT_X * CHUNK_COUNT_Y; ++i) {
        delete chunks[i];
    }
}

float Cave::getChunkSize() {
    return CHUNK_SIZE;
}

Chunk* Cave::getChunkAt(ChunkCoords c) {
    c.x += CHUNK_COUNT_X / 2;
    c.y += CHUNK_COUNT_Y / 2;
    return chunks[c.y * CHUNK_COUNT_X + c.x];
}

Chunk * Cave::getChunkAt(Vector3 v) {
    return getChunkAt(ChunkCoords(v, CHUNK_SIZE));
}

float Cave::getAverageYValueInRectangle(Vector3 center, Vector3 offset, float width, float height, float length) {
    auto relevantChunks = std::vector<Chunk*>();
    center = Vector3Subtract(center, offset);
    getChunksInBox(center, width, height, length, &relevantChunks);

    int count = 0;
    float sum = 0.0f;
    for (auto chunk: relevantChunks) {
        auto points = *chunk->getPoints();
        for (auto p: points) {
            if (isPointInBox(p, center, width, height, length)) {
                sum += p.y;
                count++;
            }
        }
    }
    return sum / count;
}

float Cave::getMaxYValueInRectangle(Vector3 center, Vector3 offset, float width, float height, float length) {
    auto relevantChunks = std::vector<Chunk*>();
    center = Vector3Subtract(center, offset);
    getChunksInBox(center, width, height, length, &relevantChunks);

    float max = -9999.9f;
    for (auto chunk: relevantChunks) {
        auto points = *chunk->getPoints();
        for (auto p: points) {
            if (p.y > max && isPointInBox(p, center, width, height, length)) {
                max = p.y;
            }
        }
    }
    return max;
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
            Chunk* chunk = getChunkAt(currCoords);
            chunk->DrawChunkModel(chunkDistance);
        }
    }
}
