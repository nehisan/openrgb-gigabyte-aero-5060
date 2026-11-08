#include "GigabyteAERO5060Controller.h"
#include "LogManager.h"

#include <cstring>

GigabyteAERO5060Controller::GigabyteAERO5060Controller(i2c_smbus_interface* bus)
    : bus(bus)
{
}

std::string GigabyteAERO5060Controller::GetDeviceLocation() const
{
    return std::string("I2C: ") + bus->info.device_name + ", RGB address 0x75";
}

void GigabyteAERO5060Controller::SetColor(RGBColor color)
{
    // Match the native Gigabyte Blackwell GPU protocol used by the RTX 5060 Ti Aero:
    // 64-byte frame, register 0x16 (direct color), one zone, RGB at bytes 5-7.
    uint8_t color_packet[64] = {};

    color_packet[0] = 0x16; // Direct color register
    color_packet[1] = 0x01;
    color_packet[2] = 0x00; // Direct mode
    color_packet[3] = 0x06; // Fastest speed (native driver setting)
    color_packet[4] = 0x0A; // Maximum brightness
    color_packet[5] = (uint8_t)RGBGetRValue(color);
    color_packet[6] = (uint8_t)RGBGetGValue(color);
    color_packet[7] = (uint8_t)RGBGetBValue(color);
    color_packet[8] = 0x00;
    color_packet[9] = 0x00; // Zone 0
    color_packet[10] = 0x00; // No color-list payload in direct mode
    color_packet[11] = 0x00;

    int result = bus->i2c_write_block(RGB_ADDRESS, sizeof(color_packet), color_packet);
    if(result < 0)
    {
        LOG_ERROR("[Gigabyte AERO RTX 5060] Native 64-byte I2C RGB write to 0x75 failed: %d", result);
    }
}
