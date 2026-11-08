#pragma once

#include <string>
#include "i2c_smbus.h"
#include "RGBController.h"

class GigabyteAERO5060Controller
{
public:
    explicit GigabyteAERO5060Controller(i2c_smbus_interface* bus);
    std::string GetDeviceLocation() const;
    void SetColor(RGBColor color);

private:
    i2c_smbus_interface* bus;
    static constexpr uint8_t RGB_ADDRESS = 0x75;
};
