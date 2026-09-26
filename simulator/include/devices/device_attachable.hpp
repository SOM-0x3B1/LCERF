#ifndef LCERF_DEVICE_ATTACHABLE_HPP
#define LCERF_DEVICE_ATTACHABLE_HPP


#include "device.hpp"

class DeviceAttachable : public Device {
public:
    DeviceAttachable(Vector3 position, Graphics* graphics);
};


#endif //LCERF_DEVICE_ATTACHABLE_HPP
