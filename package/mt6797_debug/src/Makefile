# SPDX-License-Identifier: GPL-2.0

obj-m = mt6797_debug.o
mt6797_debug-objs = main.o regdump.o
mt6797_debug-objs += debug_bus_protect_regs.o
mt6797_debug-objs += debug_gpio_regs.o
mt6797_debug-objs += debug_gpuldo_regs.o
mt6797_debug-objs += debug_emi_mpu.o
mt6797_debug-objs += debug_emi_regs.o
mt6797_debug-objs += debug_io_cfg_l_regs.o
mt6797_debug-objs += debug_m4u_regs.o
mt6797_debug-objs += debug_pericfg_regs.o
mt6797_debug-objs += debug_pll.o
mt6797_debug-objs += debug_psci.o
mt6797_debug-objs += debug_spm_regs.o
mt6797_debug-objs += debug_uart_regs.o
mt6797_debug-objs += debug_usb_sifslv_u2phy_regs.o
mt6797_debug-objs += force_uart.o
ccflags-y = $(if $(MT6797_DEBUG_FORCE_UART),-DMT6797_DEBUG_FORCE_UART=1,)

default:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules_install

clean:
	rm -f *.ko* *.mod.* *.o modules.order Modules.symvers
