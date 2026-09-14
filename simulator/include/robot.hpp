#ifndef RAYLIB_TEST_ROBOT_H
#define RAYLIB_TEST_ROBOT_H

#include <raylib.h>
#include "device.hpp"

class Robot : public Device {
public:
    Robot();

    explicit Robot(Vector3 position);

    Robot(float x, float y, float z);

    void Draw() override;
};


#endif //RAYLIB_TEST_ROBOT_H
