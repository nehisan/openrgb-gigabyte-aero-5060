# OpenRGB Gigabyte AERO RTX 5060

Experimental support notes for the Gigabyte GeForce RTX 5060 AERO.

## Hardware identifiers

- PCI vendor/device: `10DE:2D05` (NVIDIA RTX 5060)
- PCI subsystem vendor/device: `1458:41A0` (Gigabyte AERO)
- SignalRGB model key: `RTX5060_AERO`

## Protocol extracted from the supplied SignalRGB module

The module identifies the GPU using all four PCI identifiers. It scans the NVIDIA I2C bus at address `0x75`, then sends lighting frames to address `0x40`. These are distinct addresses.

- Discovery address: `0x75`
- RGB write address: `0x40`
- AERO header: `16 01 00 06 00`
- One exposed zone: `Side logo`
- Zone index: `0`
- Frame format (10 bytes): `16 01 00 06 00 R G B 00 00`

The SignalRGB `WriteRGB` function sends the five-byte AERO header followed by one RGB triplet, `0x00`, and the zone index. For this single-zone model, the zone index is zero.

**Do not send generic empty-zone frames for zones 1–5.** They use a different header and are not part of the AERO model's actual zone map.

## OpenRGB implementation requirements

OpenRGB has an existing Gigabyte Blackwell controller, but its 64-byte RGB Fusion packet format differs from this AERO-specific 10-byte SignalRGB frame. Reusing it unchanged would be incorrect.

1. Register the exact PCI/subsystem ID pair above on the NVIDIA I2C bus.
2. Preserve the discovery/write address distinction (`0x75` vs `0x40`).
3. Expose exactly one LED and one zone named `Side logo`.
4. Send only the documented 10-byte frame for direct/static color updates.
5. Keep detection read-only; it must not change lighting.

## Status and safety

These protocol details are extracted from the supplied SignalRGB source and have not been independently validated on the physical GPU. Hardware writes remain unverified. Do not test while RGB Fusion or another SMBus controller is running. The first hardware test should be one static-color write after confirming the selected NVIDIA I2C bus and target address.
