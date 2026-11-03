#ifndef LCERF_ROBOT_HPP
#define LCERF_ROBOT_HPP

#include "raylib.h"
#include <queue>

class Robot {
private:
    int id;
    Vector2 position2D;
    std::queue<Vector2> waypoints;

public:
    explicit Robot(int id);

    int getID();

    std::queue<Vector2>* getWaypoints();
    void addWaypoint(Vector2 wp);

    void completeWaypoint();
};

#endif //LCERF_ROBOT_HPP
