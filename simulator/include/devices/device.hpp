#ifndef LCERF_DEVICE_H
#define LCERF_DEVICE_H

#include <raylib.h>

class Device {
protected:
    Vector3 position{};

public:
    explicit Device(Vector3 position);

    virtual ~Device() = default;

    Vector3 getPosition();

    virtual void draw() = 0;
};


#endif //LCERF_DEVICE_H
