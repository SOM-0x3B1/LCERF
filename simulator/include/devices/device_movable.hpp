#ifndef LCERF_DEVICE_MOVABLE_HPP
#define LCERF_DEVICE_MOVABLE_HPP

#include "device.hpp"


class DeviceMovable : public Device {
public:
    explicit DeviceMovable(Vector3 position);
};


#endif //LCERF_DEVICE_MOVABLE_HPP
