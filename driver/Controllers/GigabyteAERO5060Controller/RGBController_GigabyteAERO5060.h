#pragma once

#include "RGBController.h"
#include "GigabyteAERO5060Controller.h"

class RGBController_GigabyteAERO5060 : public RGBController
{
public:
    explicit RGBController_GigabyteAERO5060(GigabyteAERO5060Controller* controller);
    ~RGBController_GigabyteAERO5060();

protected:
    void DeviceUpdateLEDs() override;
    void DeviceUpdateZoneLEDs(int zone) override;
    void DeviceUpdateSingleLED(int led) override;
    void DeviceUpdateMode() override;
    void DeviceSaveMode() override;

private:
    void UpdateColor();
    GigabyteAERO5060Controller* controller;
};
