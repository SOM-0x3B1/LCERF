#include "../include/robot.h++"

Robot::Robot() {
    this->position = {0, 0, 0};
}

Robot::Robot(Vector3 position) {
    this->position = { position.x, position.y, position.z };
}

Robot::Robot(float x, float y, float z) {
    this->position = { x, y, z };
}

Vector3 Robot::getPosition() {
    return this->position;
}
