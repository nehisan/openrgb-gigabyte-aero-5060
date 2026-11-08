#include "GigabyteAERO5060Controller.h"
#include "LogManager.h"

#include <chrono>
#include <thread>

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
    // Match the supplied SignalRGB AERO sequence:
    // zone 0 uses the AERO header; zones 1-5 are explicitly blanked
    // using the controller's legacy/default header.
    uint8_t color_packet[10] =
    {
        0x16, 0x01, 0x00, 0x06, 0x00,
        (uint8_t)RGBGetRValue(color),
        (uint8_t)RGBGetGValue(color),
        (uint8_t)RGBGetBValue(color),
        0x00, 0x00
    };

    int result = bus->i2c_write_block(RGB_ADDRESS, sizeof(color_packet), color_packet);
    if(result < 0)
    {
        LOG_ERROR("[Gigabyte AERO RTX 5060] I2C RGB zone 0 write failed: %d", result);
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(9));

    // SignalRGB sends empty-zone frames for zones 1 through 5 on each update.
    for(uint8_t zone = 1; zone < 6; ++zone)
    {
        uint8_t empty_zone_packet[10] =
        {
            0x12, 0x01, 0x01, 0x06, 0x0A,
            0x00, 0x00, 0x00, 0x00, zone
        };

        result = bus->i2c_write_block(RGB_ADDRESS, sizeof(empty_zone_packet), empty_zone_packet);
        if(result < 0)
        {
            LOG_ERROR("[Gigabyte AERO RTX 5060] I2C empty zone %u write failed: %d", zone, result);
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(9));
    }
}
