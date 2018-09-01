# Undocumented registers

## `PERI_GLOBALCON_PDN0_STA` at `0x1003018`

This register is accompanied by `PERI_GLOBALCON_PDN0_CLR` and
`PERI_GLOBALCON_PDN0_SET` at `0x10030010` and `0x1003008`, respectively.

See the files `drivers/misc/mediatek/base/power/mt6797/mt_clkmgr2.c` and
`drivers/misc/mediatek/include/mt-plat/mt6797/include/mach/mt_clkmgr2.h` in the
Android sources for more information.

The register contains single bits representing power state of different
peripherals, 1 being powered off. Initially, all seem to be powered on.

| Bit | Name       | Notes                  | 
| --- | ---------- | ---------------------- | 
|   0 | `DISP_PWM` |                        | 
|   1 | `THERM`    |                        | 
|   2 | `PWM1`     |                        | 
|   3 | `PWM2`     |                        | 
|   4 | `PWM3`     |                        | 
|   5 | `PWM4`     |                        | 
|   6 | `PWM5`     |                        | 
|   7 | `PWM6`     |                        | 
|   8 | `PWM7`     |                        | 
|   9 | `PWM`      |                        | 
|  10 | `USB0`     |                        | 
|  11 | `IRDA`     |                        | 
|  12 | `APDMA`    |                        | 
|  13 | `MSDC30_0` |                        | 
|  14 | `MSDC30_1` |                        | 
|  15 | `MSDC30_2` | Commented out in code. | 
|  16 | `MSDC30_3` | Commented out in code. | 
|  17 | `UART0`    |                        | 
|  18 | `UART1`    |                        | 
|  19 | `UART2`    |                        | 
|  20 | `UART3`    |                        | 
|  21 | `UART4`    | Commented out in code. | 
|  22 | `BTIF`     |                        | 
|  23 | `I2C0`     |                        | 
|  24 | `I2C1`     |                        | 
|  25 | `I2C2`     |                        | 
|  26 | `I2C3`     |                        | 
|  27 | `AUXADC`   |                        | 
|  28 | `SPI0`     |                        | 
|  29 | `IRTX`     |                        | 


## `UART_RX_SEL` @ `0x110020B0`

Writing 1 to this register will connect the RX part of the UART to USB.

## Bit 7 in GPIO `MISC` register

Writing 1 in this will connect UART to the USB port.
