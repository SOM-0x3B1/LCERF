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
    std::queue<Vector2> movementCheckpoints;
    int stuckForTicks;

public:
    explicit Robot(Vector3 position, Graphics* graphics);

    void moveTowardsCheckpoint();
    inline float distanceFromCheckpoint(Vector2 p);
    void snapToGround() override;

    Vector2* getCurrCheckpoint();
    Vector2* updateAndGetCurrCheckpoint();
    void completeCheckpoint();
    void connectNewWireTo(InterfaceWired* interface);

    void draw() override;

    void simulationStep() override;
};


#endif //RAYLIB_TEST_ROBOT_H
