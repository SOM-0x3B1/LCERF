#ifndef LCERF_DEVICE_H
#define LCERF_DEVICE_H

#include <raylib.h>
#include "../../include/graphics.hpp"

class Device {
protected:
    Vector3 position{};
    Graphics* graphics;

public:
    explicit Device(Vector3 position, Graphics* graphics);

    virtual ~Device() = default;

    Vector3 getPosition();

    virtual void draw() = 0;
};


#endif //LCERF_DEVICE_H
