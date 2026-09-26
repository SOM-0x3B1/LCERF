#ifndef LCERF_DEVICE_STATIC_HPP
#define LCERF_DEVICE_STATIC_HPP

#include "device.hpp"


class DeviceStatic : public Device {
public:
    explicit DeviceStatic(Vector3, Graphics* graphics);
};


#endif //LCERF_DEVICE_STATIC_HPP