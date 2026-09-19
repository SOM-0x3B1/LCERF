#ifndef LCERF_BASE_STATION_HPP
#define LCERF_BASE_STATION_HPP

#include "../device_static.hpp"


class BaseStation : public DeviceStatic {
    const float radius = 0.3f;
    const float height = 0.1f;

public:
    explicit BaseStation(Vector3 position, Graphics* graphics);

    void draw() override;
};


#endif //LCERF_BASE_STATION_HPP
