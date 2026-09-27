#ifndef LCERF_WIRE_HPP
#define LCERF_WIRE_HPP

#include <raylib.h>
#include "../devices/attachable/interface.hpp"

class Wire{
private:
    Vector3 firstPosition{};
    Vector3 secondPosition{};

    Interface* firstConnectedTo;
    Interface* secondConnectedTo;

    Graphics* graphics;

public:
    Wire(Vector3 firstPosition, Vector3 secondPosition, Graphics* graphics);
    Wire(Interface* firstInterface, Interface* secondInterface, Graphics* graphics);

    Vector3 getFirstPosition();
    Vector3 getSecondPosition();
    Interface* getFirstConnectedTo();
    Interface* getSecondConnectedTo();

    void setFirstPosition(Vector3 pos);
    void setSecondPosition(Vector3 pos);
    void setFirstConnectedTo(Interface* connectedTo);
    void setSecondConnectedTo(Interface* connectedTo);

    void draw();
};


#endif //LCERF_WIRE_HPP
