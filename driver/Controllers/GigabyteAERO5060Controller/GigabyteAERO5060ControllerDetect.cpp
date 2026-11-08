#include "DetectionManager.h"
#include "GigabyteAERO5060Controller.h"
#include "RGBController_GigabyteAERO5060.h"

// Detection is deliberately read-only: the exact PCI/subsystem tuple is
// matched by OpenRGB's I2C PCI detector. No probe packet is sent to the GPU.
DetectedControllers DetectGigabyteAERO5060(i2c_smbus_interface* bus,
                                            uint8_t,
                                            const std::string&)
{
    DetectedControllers detected;
    GigabyteAERO5060Controller* controller = new GigabyteAERO5060Controller(bus);
    detected.push_back(new RGBController_GigabyteAERO5060(controller));
    return detected;
}

// NVIDIA RTX 5060 (10DE:2D05), Gigabyte AERO subsystem (1458:41A0).
// 0x75 is the discovery-side I2C address; RGB writes use 0x40.
REGISTER_I2C_PCI_DETECTOR("Gigabyte GeForce RTX 5060 AERO",
                          DetectGigabyteAERO5060,
                          0x10DE, 0x2D05, 0x1458, 0x41A0, 0x75);
