#include "../include/chunk.hpp"


ChunkCoords::ChunkCoords(int x, int y) : chunkSize(1) {
    this->x = x;
    this->y = y;
}

ChunkCoords::ChunkCoords(Vector2 v, int chunkSize) : chunkSize(chunkSize) {
    this->x = static_cast<int>(roundf(v.x / chunkSize + chunkSize / 2.0f));
    this->y = static_cast<int>(roundf(v.y / chunkSize + chunkSize / 2.0f));
}

ChunkCoords::ChunkCoords(Vector3 v, int chunkSize) : chunkSize(chunkSize) {
    this->x = static_cast<int>(roundf(v.x / chunkSize + chunkSize / 2.0f));
    this->y = static_cast<int>(roundf(v.z / chunkSize + chunkSize / 2.0f));
}

Mesh Chunk::GenerateMesh()
{
    Mesh mesh = {
        .vertexCount = pointCount,
        .triangleCount = 1,
        .vertices = static_cast<float *>(MemAlloc(pointCount * 3 * sizeof(float))),
        .colors = static_cast<unsigned char *>(MemAlloc(pointCount * 4 * sizeof(unsigned char))),
    };

    // REF: https://en.wikipedia.org/wiki/Spherical_coordinate_system
    for (int i = 0; i < pointCount; i++)
    {
        mesh.vertices[i*3 + 0] = points[i].x;
        mesh.vertices[i*3 + 1] = points[i].y;
        mesh.vertices[i*3 + 2] = points[i].z;
    }

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}

Chunk::Chunk(ChunkCoords coords, Graphics *graphics, int chunkSize) : coords(coords), chunkSize(chunkSize) {
    this->pointCount = 0;
    this->graphics = graphics;
}

const std::vector<Vector3> * Chunk::GetPoints() {
    return &points;
}

void Chunk::AddPoint(Vector3 point) {
    this->pointCount++;
    points.push_back(point);
}

void Chunk::GenChunkModel() {
    Mesh mesh = GenerateMesh();
    model = LoadModelFromMesh(mesh);
}

void Chunk::DrawChunkModel() {
    auto position = Vector3(
        static_cast<float>(coords.x * chunkSize),
        0,
        static_cast<float>(coords.y * chunkSize));
    Graphics::drawModelPoints(model, position, 1.0, BLUE);
}