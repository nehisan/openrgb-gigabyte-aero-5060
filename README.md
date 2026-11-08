# OpenRGB — Gigabyte GeForce RTX 5060 AERO

Personal, experimental hardware support for the **Gigabyte GeForce RTX 5060 AERO** in a standalone Windows build of OpenRGB 1.1.

This is an independent project. It is not an official OpenRGB release and is not endorsed by the OpenRGB project.

## Hardware tested

| Item | Value |
|---|---|
| GPU | Gigabyte GeForce RTX 5060 AERO |
| NVIDIA PCI device ID | `10DE:2D05` |
| Gigabyte subsystem ID | `1458:41A0` |
| RGB controller | NVIDIA NvAPI I²C |
| RGB I²C address | `0x75` |
| Exposed lighting zone | `Side logo` |

The controller exposes one LED and one zone. It does not send writes for additional, unused zones.

## Working RGB protocol

The known-good implementation follows the 64-byte Gigabyte Blackwell RGB Fusion frame used by the native OpenRGB controller for the RTX 5060 Ti AERO family, adapted and tested on the RTX 5060 AERO.

- I²C write address: `0x75`
- Frame size: **64 bytes**
- Register/command: `0x16` (direct color)
- Mode: direct (`0x00`)
- Speed: `0x06`
- Brightness: `0x0A`
- RGB values: bytes 5–7
- Zone index: byte 9, value `0x00`
- Only zone 0 is written.

The controller uses the normal NvAPI I²C port configuration (`is_ddc_port = 0`). No DDC-mode workaround is required.

## Build

The repository contains a GitHub Actions workflow that checks out OpenRGB's `release_1.1` source, copies in this controller, and builds a Windows x64 release.

1. Open the **Actions** tab in this repository.
2. Select **Build OpenRGB 1.1 with AERO RTX 5060 driver**.
3. Run the workflow (or push a change to `main`).
4. Download the `OpenRGB-1.1-AERO-RTX5060-Windows-x64` artifact from the completed run.

The artifact is a standalone OpenRGB build with the AERO controller integrated; it is not a separately installable controller DLL.

## Known-good build

Build #8 was successfully tested on the target Gigabyte RTX 5060 AERO:

[GitHub Actions run #8 — successful hardware-tested build](https://github.com/nehisan/openrgb-gigabyte-aero-5060/actions/runs/42492363818)

Keep this build as the known-good version when experimenting with future changes.

## Scope and cautions

- This project currently targets the Gigabyte RTX 5060 AERO identified above. Other GPU variants are not confirmed.
- The protocol description reflects the implementation validated on the physical card; do not replace it with the older 10-byte experimental frame.
- Avoid running multiple RGB/I²C control applications against the GPU at the same time.
- Changes to the controller should be tested in a separate workflow run before replacing the known-good build.
