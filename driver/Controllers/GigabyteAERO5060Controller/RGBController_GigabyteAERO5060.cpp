#include "RGBController_GigabyteAERO5060.h"

RGBController_GigabyteAERO5060::RGBController_GigabyteAERO5060(GigabyteAERO5060Controller* controller)
    : controller(controller)
{
    name        = "Gigabyte GeForce RTX 5060 AERO";
    vendor      = "Gigabyte";
    description = "Gigabyte AERO RTX 5060 single-zone RGB controller";
    location    = controller->GetDeviceLocation();
    type        = DEVICE_TYPE_GPU;

    mode Static;
    Static.name       = "Static";
    Static.value      = 0;
    Static.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Static.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Static);

    zone logo_zone;
    logo_zone.name       = "Side logo";
    logo_zone.type       = ZONE_TYPE_SINGLE;
    logo_zone.leds_min   = 1;
    logo_zone.leds_max   = 1;
    logo_zone.leds_count = 1;
    zones.push_back(logo_zone);

    led logo_led;
    logo_led.name = "Side logo";
    leds.push_back(logo_led);

    SetupColors();
}

RGBController_GigabyteAERO5060::~RGBController_GigabyteAERO5060()
{
    Shutdown();
    delete controller;
}

void RGBController_GigabyteAERO5060::UpdateColor()
{
    if(!colors.empty())
    {
        controller->SetColor(colors[0]);
    }
}

void RGBController_GigabyteAERO5060::DeviceUpdateLEDs()
{
    UpdateColor();
}

void RGBController_GigabyteAERO5060::DeviceUpdateZoneLEDs(int)
{
    UpdateColor();
}

void RGBController_GigabyteAERO5060::DeviceUpdateSingleLED(int)
{
    UpdateColor();
}

void RGBController_GigabyteAERO5060::DeviceUpdateMode()
{
    UpdateColor();
}

void RGBController_GigabyteAERO5060::DeviceSaveMode()
{
    // The AERO frame protocol exposes direct color writes only.
}
