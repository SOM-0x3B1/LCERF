#ifndef RAYLIB_TEST_ROBOT_H
#define RAYLIB_TEST_ROBOT_H

#include <raylib.h>
#include "../device_movable.hpp"

class Robot : public DeviceMovable {
public:
    explicit Robot(Vector3 position, Graphics* graphics);

    void draw() override;
};


#endif //RAYLIB_TEST_ROBOT_H
