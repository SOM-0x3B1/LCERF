#include "../../include/devices/device_movable.hpp"
#include "raylib.h"
#include "raymath.h"

DeviceMovable::DeviceMovable(Vector3 position, Graphics* graphics) : Device(position, graphics) { }