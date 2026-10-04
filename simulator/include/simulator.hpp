#ifndef LCERF_SIMULATOR_HPP
#define LCERF_SIMULATOR_HPP

#include "cave.hpp"
#include "device_manager.hpp"

class Simulator {
private:
    Cave* cave;
    DeviceManager* deviceManager;
    Graphics* graphics;

public:
    explicit Simulator(Cave* cave, DeviceManager* deviceManager, Graphics* graphics);

    Cave* getCave();
    DeviceManager* getDeviceManager();
    Graphics* getGraphics();

    void init();

    void step();
};


#endif //LCERF_SIMULATOR_HPP
