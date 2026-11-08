#include "GigabyteAERO5060Controller.h"
#include "LogManager.h"

GigabyteAERO5060Controller::GigabyteAERO5060Controller(i2c_smbus_interface* bus)
    : bus(bus)
{
}

std::string GigabyteAERO5060Controller::GetDeviceLocation() const
{
    return std::string("I2C: ") + bus->info.device_name + ", RGB address 0x40";
}

void GigabyteAERO5060Controller::SetColor(RGBColor color)
{
    // AERO RTX 5060 frame reported by the supplied SignalRGB module.
    // This is intentionally separate from the 64-byte RGB Fusion protocol.
    uint8_t packet[10] =
    {
        0x16, 0x01, 0x00, 0x06, 0x00,
        (uint8_t)RGBGetRValue(color),
        (uint8_t)RGBGetGValue(color),
        (uint8_t)RGBGetBValue(color),
        0x00, 0x00
    };

    int result = bus->i2c_write_block(RGB_ADDRESS, sizeof(packet), packet);
    if(result < 0)
    {
        LOG_ERROR("[Gigabyte AERO RTX 5060] I2C RGB write failed: %d", result);
    }
}
