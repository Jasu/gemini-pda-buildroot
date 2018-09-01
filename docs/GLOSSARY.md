# MediaTek slang dictionary

MediaTek / ARM slang. Most of the terms are MediaTek-specific, some are not.

## General

| Term                 | Description                                                                                                            |
| -------------------- | ---------------------------------------------------------------------------------------------------------------------- |
| `AEE`                | **Android Exception Engine**: MediaTek's proprietary method to collect exception / panic information.                  |
| `AHB`                | **AMBA High-Performance Bus**: An old AMBA bus. Used on MT6797 for at least USB, modem, and MSDC. Compatible with AXI. |
| `AP`                 | **Application Processor**: The actual ARM CPU.                                                                         |
| `AXI`                | **Advanced Extensible Interface**: A faster AMBA bus. Also used on the MT6797, alongside *AHB*. This is the main bus.  |
| `DCM`                | **Dynamic Clock Management**: Adjusts clock speed (e.g. the bus clock) automatically based on usage.                   |
| `DPE`                | Something related to the camera.                                                                                       |
| `EMI`                | **External Memory Interface**: The interface for the actual LPDDR3 RAM.                                                |
| `Everest`            | Codename for the MT6797 architecture.                                                                                  |
| `FHCTL`              | Hardware frequency-hopping control for system clocks.                                                                  |
| `GCPU`               | Secure processor, related to TrustZone and HDCP.                                                                       |
| `LDO`                | Power supply for SRAM in the CPU and the Mali GPU.                                                                     |
| `MD`                 | **Modem**: The baseband processor. A dual-core ARM Cortex-R4 processor.                                                |
| `MSDC`               | **Memory Stick and SD Card Controller**: Controller for SD cards.                                                      |
| `MU3D`, `U3D`        | **Mediatek Usb 3 Dual-role**: Peripheral / host mode controller.                                                       |
| `PMIC`               | **Power Management IC**: The external power controller. Integrated to audio codec. MT6797 has a MT6351.                |
| `pwrap`, `PMIC wrap` | **PMIC Wrapper**: The interface for talking to the *PMIC*.                                                             |
| `SCPSYS`             | Processor controlling system power and clocks.                                                                         |
| `SPM`                | Power-management system, lives in the SCPSYS.                                                                          |

## Display / multimedia

| Term    | Description                                                                                                             |
| ------- | ----------------------------------------------------------------------------------------------------------------------- |
| `CMDQ`  | **CoMmanD Queue**: A command queue used with the display system, MDP, video encoder, JPEG, and camera.                  |
| `DBI`   | **Display Bus Interface**: A display interface by MIPI. Not used on the Gemini.                                         |
| `DDP`   | **Display Data Path**: How elements (DMA, resizer, output, etc.) are connected in the display system.                   |
| `DPI`   | **Display Parallel Interface**: A parallel display interface by MIPI. Used for HDMI on the Gemini.                      |
| `DSI`   | **Display Parallel Interface**: A serial display interface by MIPI. Used for the main display on the Gemini (on DSI0).  |
| `LARB`  | **Local ARBiter**: Arbitrates peripheral access to the memory (via SMI).                                                |
| `LCM`   | **LCd Module**: The LCD module.                                                                                         |
| `M4U`   | **MultiMedia Memory Management Unit**: IOMMU used by the display and video/JPEG encoder and decoder subsystems.         |
| `MDP`   | **Multimedia Data Path**                                                                                                |
| `MFG`   | The processing unit containing the Mali processor.                                                                      |
| `MIPI`  | Standardization body for display interfaces. Usually refers either to DPI or DSI.                                       |
| `MJC`   | ClearMotion video (super-slow-motion etc.)                                                                              |
| `MOUT`  | **Multiple OUTput**: Allows a display processing path to write to multiple destinations.                                |
| `OD`    | **OverDrive**                                                                                                           |
| `OVL`   | **OVerLay**: Display overlay. MT6797 supports compositing multiple overlays to the display output.                      |
| `PRZ`   | Rotation functionality.                                                                                                 |
| `RDMA`  | **Read DMA**: Allows the display controller to read from RAM.                                                           |
| `SMI`   | **Smart Multimedia Interface**, contains the LARB ports.                                                                |
| `TDSHP` | Sharpness (edge-enhancement)                                                                                            |
| `UFO`   | MediaTek's proprietary display connection compression format.                                                           |
| `WDMA`  | **Write DMA**: Allows the display controller to write to RAM.                                                           |

# Audio

| Term            | Description                                                                     |
| --------------- | ------------------------------------------------------------------------------- |
| `AFE`           | **Audio FrontEnd**                                                              |
| `AMPL` / `AMPR` | Left and right amplifier. `L` and `R` suffixes usually refer to left and right. |
| `ANA`           | **ANAlog**                                                                      |
| `HP`            | **HeadPhones**                                                                  |

## Modem

| Term    | Description                                                                                                                                         |
| ------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| `BTIF`  | **Bluetooth Interface**                                                                                                                             |
| `C2K`   | **CDMA2000**: Probably refers to CDMA2000.                                                                                                          |
| `CCCI`  | **Cross-Core Communication Interface**: Facilitates communication between *AP* (application processor, i.e. the CPU) and *MD* (baseband processor). |
| `CCIF`  | Somewhat synonymous to CCCI                                                                                                                         |
| `ECCCI` | **Enhanced Cross-Core Communication Interface**: An updated version of `CCCI`. Used on the MT6797.                                                  |
| `MD`    | **Modem**: The baseband processor. A dual-core ARM Cortex-R4 processor.                                                                             |
| `WMT`   | **Wireless Management Task**: Controls Bluetooth and WIFI (maybe other basebands?), apparently switching between them under poor signal conditions. |
