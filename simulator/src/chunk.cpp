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

float ChunkCoords::distanceFrom(ChunkCoords c) {
    return sqrtf((c.x - x) * (c.x - x) + (c.y - y) * (c.y - y));
}

Mesh Chunk::GenerateMesh(int resolutionDivider) {
    int currResolution = fullPointCount / resolutionDivider;

    Mesh mesh = {
        .vertexCount = currResolution,
        .triangleCount = 1,
        .vertices = static_cast<float *>(MemAlloc(currResolution * 3 * sizeof(float))),
        .colors = static_cast<unsigned char *>(MemAlloc(currResolution * 4 * sizeof(unsigned char))),
    };

    // REF: https://en.wikipedia.org/wiki/Spherical_coordinate_system
    for (int i = 0; i < currResolution; i++)
    {
        mesh.vertices[i*3 + 0] = points[i * resolutionDivider].x;
        mesh.vertices[i*3 + 1] = points[i * resolutionDivider].y;
        mesh.vertices[i*3 + 2] = points[i * resolutionDivider].z;
    }

    for (int i = 0; i < currResolution; i++)
    {
        mesh.colors[i*4 + 0] = 255;
        mesh.colors[i*4 + 1] = 255;
        mesh.colors[i*4 + 2] = 255;
        mesh.colors[i*4 + 3] = 255;
    }

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}

Chunk::Chunk(ChunkCoords coords, Graphics *graphics, int chunkSize) : coords(coords), chunkSize(chunkSize) {
    this->fullPointCount = 0;
    this->graphics = graphics;
}

const std::vector<Vector3>* Chunk::GetPoints() {
    return &points;
}

void Chunk::AddPoint(Vector3 point) {
    this->fullPointCount++;
    points.push_back(point);
}

void Chunk::GenChunkModel() {
    Mesh mesh = GenerateMesh(1);
    modelFull = LoadModelFromMesh(mesh);
    mesh = GenerateMesh(2);
    modelHalf = LoadModelFromMesh(mesh);
    mesh = GenerateMesh(4);
    modelQuarter = LoadModelFromMesh(mesh);
    mesh = GenerateMesh(8);
    modelMin = LoadModelFromMesh(mesh);
}

void Chunk::DrawChunkModel(float chunkDistance) {
    float renderDistanceF = static_cast<float>(graphics->getRenderDistance());

    int alpha = 0;
    Model* model = nullptr;
    if (chunkDistance > renderDistanceF - renderDistanceF * 0.2) {
        alpha = 10;
        model = &modelMin;
    }
    else if (chunkDistance > renderDistanceF - renderDistanceF * 0.5) {
        alpha = 20;
        model = &modelQuarter;
    }
    else if (chunkDistance > renderDistanceF - renderDistanceF * 0.7) {
        alpha = 30;
        model = &modelHalf;
    }
    else if (chunkDistance > renderDistanceF - renderDistanceF * 0.8) {
        alpha = 40;
        model = &modelFull;
    }
    else {
        alpha = 255;
        model = &modelFull;
    }
    auto color = Color(255, 255, 255, alpha);

    Graphics::drawModelPoints(*model, {0, 0, 0}, 1.0, color);
}