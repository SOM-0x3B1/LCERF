#include "../../../include/devices/movable/robot.hpp"

Robot::Robot(Vector3 position) : DeviceMovable(position) { }

Robot::Robot(float x, float y, float z) : DeviceMovable(position) { }

void Robot::draw() {
    DrawCube(position, 0.2, 0.1, 0.15, YELLOW);
}
