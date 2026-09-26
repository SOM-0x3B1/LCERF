#ifndef LCERF_DEVICE_H
#define LCERF_DEVICE_H

#include <raylib.h>
#include <vector>

#include "../../include/graphics.hpp"

class Device {
protected:
    Vector3 position{};
    Graphics* graphics;
    std::vector<Device*> attachedDevices;

public:
    explicit Device(Vector3 position, Graphics* graphics);
    virtual ~Device();

    Vector3 getPosition();

    virtual void draw() = 0;
};


#endif //LCERF_DEVICE_H
