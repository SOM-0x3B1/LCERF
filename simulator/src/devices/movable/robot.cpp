#include "../../../include/devices/movable/robot.hpp"

Robot::Robot(Vector3 position, Graphics* graphics) : DeviceMovable(position, graphics) { }

void Robot::draw() {
    DrawCube(position, 0.2, 0.1, 0.15, YELLOW);
}
