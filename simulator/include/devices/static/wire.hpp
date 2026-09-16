#ifndef LCERF_WIRE_HPP
#define LCERF_WIRE_HPP

#include <raylib.h>
#include "../device_static.hpp"

class Wire : public DeviceStatic {
private:
    Vector3 endPosition{};

public:
    Wire(Vector3 startPosition, Vector3 endPosition);
    Vector3 getEndPosition();

    void draw() override;
};


#endif //LCERF_WIRE_HPP
