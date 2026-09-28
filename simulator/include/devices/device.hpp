#ifndef LCERF_DEVICE_H
#define LCERF_DEVICE_H

#include <raylib.h>
#include <vector>

#include "../../include/graphics.hpp"

class Device {
protected:
    int id;
    Vector3 position{};
    Graphics* graphics;
    std::vector<Device*> attachedDevices;

public:
    explicit Device(Vector3 position, Graphics* graphics);
    virtual ~Device();

    Vector3 getPosition();
    virtual void move(Vector3 dV);

    void attachDevice(Device* device);

    void drawAttachedDevices();
    virtual void draw() = 0;

    virtual void simulationStep();
};


#endif //LCERF_DEVICE_H
