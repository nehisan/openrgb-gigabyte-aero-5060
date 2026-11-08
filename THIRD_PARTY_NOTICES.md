# Licensing and source-code notice

This project builds a modified version of [OpenRGB](https://github.com/CalcProgrammer1/OpenRGB), using the upstream `release_1.1` source line, with a custom Gigabyte AERO RTX 5060 controller and a small diagnostic change to the Windows NvAPI I2C write path.

OpenRGB 1.1 is distributed under the GNU General Public License, version 2 (GPL-2.0). The upstream license text is reproduced in [LICENSE](LICENSE). Copyright and attribution notices in upstream files remain applicable.

The custom controller and build modifications are intended to be distributed under GPL-2.0 as part of this combined OpenRGB build. This repository is not an independently loadable controller DLL.

## Corresponding source

For each new Windows build, the GitHub Actions workflow is intended to publish a corresponding source archive alongside the executable artifact. That archive contains the checked-out OpenRGB source tree with this project's controller and build-time source modification applied. Keep the source archive available for recipients of the corresponding binary.

The upstream checkout currently follows the `release_1.1` ref. For a reproducible public release, record and pin the exact upstream commit used by the build, and verify that the source archive is retained and downloadable with the binary.

## Important

This notice is informational, not legal advice. Before distributing binaries publicly, verify the applicable license terms for OpenRGB and all included dependencies, preserve their notices, and ensure the corresponding source and build instructions are made available as required.
