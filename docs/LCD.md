# Notes about the LCD

The display is controlled by a NT36672.

**NOTE:** The Android device tree refers to a Truly display controlled by
a Renesas R63419, but that is not actually used. The kernel configuration
overrides the selected display model.

## Backlight

The device tree contains LCD backlight as a LED, but it is possible and quite
likely that it is not used, since the DTS for the display contains a separate
reference to backlight. Additionally, the DTS references other non-existent
LEDs.
