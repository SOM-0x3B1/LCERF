#ifndef RAYLIB_TEST_ROBOT_H
#define RAYLIB_TEST_ROBOT_H

#include <raylib.h>
#include "../device_movable.hpp"
#include "../attachable/interface_wired.hpp"
#include "../attachable/interface_wireless.hpp"

class Robot : public DeviceMovable {
    InterfaceWired* wiredInterface;
    InterfaceWireless* wirelessInterface;

public:
    explicit Robot(Vector3 position, Graphics* graphics);

    void connectNewWireTo(InterfaceWired* interface);

    void draw() override;

    void simulationStep() override;
};


#endif //RAYLIB_TEST_ROBOT_H
