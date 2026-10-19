#ifndef RAYLIB_TEST_ROBOT_H
#define RAYLIB_TEST_ROBOT_H

#include <raylib.h>
#include "../device_movable.hpp"
#include "../attachable/interface_wired.hpp"
#include "../attachable/interface_wireless.hpp"

class Robot : public DeviceMovable {
    float width;
    float height;
    float length;

    InterfaceWired* wiredInterface;
    InterfaceWireless* wirelessInterface;

    std::deque<Vector2> movementWaypoints;
    std::deque<float> elevationHistory;
    const int elevationHistorySize;
    int stuckForTicks;

    bool showWaypoints;

public:
    explicit Robot(Vector3 position, Graphics* graphics);

    void moveTowardsWaypoint();
    inline float distanceFromWaypoint(Vector2 p);
    void snapToGround() override;

    void addWaypoint(Vector2 p);
    Vector2* getCurrWaypoint();
    Vector2* updateAndGetCurrWaypoint();
    void completeWaypoint();

    void connectNewWireTo(InterfaceWired* interface);

    void draw3D() override;

    void simulationStep() override;
};


#endif //RAYLIB_TEST_ROBOT_H
