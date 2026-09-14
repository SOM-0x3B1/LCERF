#include "../include/robot.h++"

Robot::Robot() {
    this->position = {.x = 0, .y = 0, .z = 0};
}

Robot::Robot(Vector3 position) {
    this->position = { .x = position.x, .y = position.y, .z = position.z };
}

Robot::Robot(float x, float y, float z) {
    this->position = { .x = x, .y = y, .z = z };
}

void Robot::Draw() {
    DrawCube(position, 0.2, 0.1, 0.15, YELLOW);
}
