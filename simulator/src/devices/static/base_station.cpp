#include "../../../include/devices/static/base_station.hpp"

#include "raymath.h"

BaseStation::BaseStation(Vector3 position) : DeviceStatic(position) { }

void DeviceStatic::draw() {
    DrawCylinderWires(position, 0.5, 0.5, 0.1, 8, GREEN);
    //DrawLine3D(position, Vector3Add(position, Vector3(0, 3, 0)), GREEN);
    DrawCylinderWires(position, 0.02, 0.02, 5, 3, GREEN);
}