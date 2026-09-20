#include "../include/chunk.hpp"

Chunk::Chunk(Graphics *graphics, int chunkSize) : chunkSize(chunkSize) {
    this->graphics = graphics;
}

const std::vector<Vector3> * Chunk::GetPoints() {
    return &points;
}

void Chunk::AddPoint(Vector3 point) {
    points.push_back(point);
}

ChunkCoord::ChunkCoord(Vector2 v, int chunkSize) : chunkSize(chunkSize) {
    this->x = static_cast<int>(v.x / chunkSize);
    this->y = static_cast<int>(v.y / chunkSize);
}

ChunkCoord::ChunkCoord(Vector3 v, int chunkSize) : chunkSize(chunkSize) {
    this->x = static_cast<int>(v.x / chunkSize);
    this->y = static_cast<int>(v.y / chunkSize);
}
