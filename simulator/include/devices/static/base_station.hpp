#ifndef LCERF_BASE_STATION_HPP
#define LCERF_BASE_STATION_HPP

#include "../device_static.hpp"


class BaseStation : public DeviceStatic {
public:
    explicit BaseStation(Vector3);

    void draw() override;
};


#endif //LCERF_BASE_STATION_HPP
