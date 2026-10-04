#ifndef LCERF_DEVICE_H
#define LCERF_DEVICE_H

#include <raylib.h>
#include <vector>

#include "../../include/graphics.hpp"
#include "../cave.hpp"

class Device {
protected:
    int id;
    Vector3 position{};
    Graphics* graphics;
    Cave* cave;
    std::vector<Device*> attachedDevices;
    std::vector<Vector3> supportPoints;

public:
    explicit Device(Vector3 position, Graphics* graphics);
    virtual ~Device();

    void setCave(Cave* newCave);
    Vector3 getPosition();
    virtual void move(Vector3 dV);
    virtual void snapToGround();

    void attachDevice(Device* device);

    void drawAttachedDevices();
    virtual void draw() = 0;

    virtual void simulationStep();
};


#endif //LCERF_DEVICE_H
