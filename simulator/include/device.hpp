#ifndef LCERF_DEVICE_HPP
#define LCERF_DEVICE_HPP

#include <raylib.h>

class Device {
protected:
    Vector3 position{};

public:
    virtual ~Device() = default;

    Vector3 getPosition();

    virtual void Draw() = 0;
};


#endif //LCERF_DEVICE_HPP
