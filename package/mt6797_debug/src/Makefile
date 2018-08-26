# SPDX-License-Identifier: GPL-2.0

obj-m = mt6797_debug.o
mt6797_debug-objs = main.o regdump.o
mt6797_debug-objs += debug_emi_mpu.o
mt6797_debug-objs += debug_emi_regs.o
mt6797_debug-objs += debug_m4u_regs.o
mt6797_debug-objs += debug_pll.o
mt6797_debug-objs += debug_psci.o

default:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules_install

clean:
	rm -f *.ko* *.mod.* *.o modules.order Modules.symvers
