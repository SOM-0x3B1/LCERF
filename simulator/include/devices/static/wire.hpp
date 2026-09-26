#ifndef LCERF_WIRE_HPP
#define LCERF_WIRE_HPP

#include <raylib.h>
#include "../device_static.hpp"

class Wire : public DeviceStatic {
private:
    Vector3 secondPosition{};

public:
    Wire(Vector3 startPosition, Vector3 endPosition, Graphics* graphics);

    Vector3 getStartPosition();
    Vector3 getEndPosition();

    void setStartPosition(Vector3 pos);
    void setEndPosition(Vector3 pos);

    void draw() override;
};


#endif //LCERF_WIRE_HPP
