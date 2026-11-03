#include "../include/robot.hpp"

Robot::Robot(int id) : position2D(Vector2(0, 0)) {
    this->id = id;
}

int Robot::getID() {
    return id;
}

std::queue<Vector2> * Robot::getWaypoints() {
    return &this->waypoints;
}

void Robot::addWaypoint(Vector2 wp) {
    waypoints.push(wp);
}

void Robot::completeWaypoint() {
    if (!waypoints.empty()) {
        waypoints.pop();
    }
}
