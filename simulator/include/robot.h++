#ifndef RAYLIB_TEST_ROBOT_H
#define RAYLIB_TEST_ROBOT_H

#include <raylib.h>

class Robot {
private:
    Vector3 position{};

public:
    Robot();
    Robot(float x, float y, float z);

    Vector3 getPosition();
};


#endif //RAYLIB_TEST_ROBOT_H
