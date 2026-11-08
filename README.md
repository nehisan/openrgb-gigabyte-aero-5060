# OpenRGB Gigabyte AERO RTX 5060

Experimental support for the Gigabyte GeForce RTX 5060 AERO (PCI IDs 10DE:2D05 / 1458:41A0).

## Status

Protocol extracted from the supplied SignalRGB module. Hardware writes are not yet validated on this card.

- Detection PCI IDs: NVIDIA 10DE:2D05, Gigabyte subsystem 1458:41A0
- Detection I2C address: 0x75
- RGB write I2C address used by the SignalRGB module: 0x40
- One LED zone: Side logo
- RGB packet: 16 01 00 06 00 RR GG BB 00 00

The original SignalRGB script also sends empty-zone packets for zones 1-5 using a different header. This implementation must NOT reproduce those writes for the single-zone AERO.

## Safety

Do not test writes while RGB Fusion or another SMBus controller is running. Initial testing should be limited to a single static color write after verifying the target I2C bus and address.