// SPDX-License-Identifier: GPL-2.0

#include <linux/kernel.h>
#include <linux/module.h>
#include "regdump.h"

#define UART0_BASE 0x11002000

#define DEFINE_UART(num_) \
	DEFINE_REGISTER(UART##num_##_RBR, 0x000, "RX Buffer (TX when written)", \
		REGISTER_FIELD(0, 7, "Received character") \
	); \
	DEFINE_REGISTER(UART##num_##_IER, 0x004, "Interrupt Enable", \
		REGISTER_BIT_ENABLED(0, "Interrupt on new RX data"), \
		REGISTER_BIT_ENABLED(1, "Interrupt on TX data empty"), \
		REGISTER_BIT_ENABLED(2, "Interrupt on BI, FE, PE, or OE set"), \
		REGISTER_BIT_ENABLED(3, "Interrupt on DCTS set"), \
		REGISTER_BIT_ENABLED(5, "Interrupt on a received XOFF"), \
		REGISTER_BIT_ENABLED(6, "Interrupt on RTS rising edge"), \
		REGISTER_BIT_ENABLED(7, "Interrupt on CTS rising edge") \
	); \
	DEFINE_REGISTER(UART##num_##_LCR, 0x00C, "Line Control", \
		REGISTER_ENUM(0, 1, "Word length", \
			"5 bits", \
			"6 bits", \
			"7 bits", \
			"8 bits"), \
		REGISTER_BIT(2, \
			"Two STOP bits added to TX", \
			"One STOP bit added to TX"), \
		REGISTER_BIT_ENABLED(3, "Parity RX/TX"), \
		REGISTER_BIT(4, "Even parity", "Odd parity"), \
		REGISTER_BIT_ENABLED(5, "Force parity"), \
		REGISTER_BIT_SET(6, "Force SOUT / break to 1 "), \
		REGISTER_BIT_SET(7, "Divisor latch access") \
	); \
	DEFINE_REGISTER(UART##num_##_FCR, 0x008, "FIFO Control Register", \
		REGISTER_BIT_ENABLED(0, "FIFO"), \
		REGISTER_BIT_SET(1, "Clear RX FIFO"), \
		REGISTER_BIT_SET(2, "Clear TX FIFO"), \
		REGISTER_ENUM(4, 5, "TX FIFO trigger threshold", \
			"1", "4", "8", "14" \
		), \
		REGISTER_ENUM(6, 7, "RX FIFO trigger threshold", \
			"1", "6", "12", "RXTRIG" \
		) \
	); \
	DEFINE_REGISTER(UART##num_##_DLL, 0x090, "Divisor Latch LSB", \
		REGISTER_FIELD(0, 7, "Divisor latch low 8-bit") \
	); \
	DEFINE_REGISTER(UART##num_##_DLM, 0x094, "Divisor Latch MSB", \
		REGISTER_FIELD(0, 7, "Divisor latch high 8-bits") \
	); \
	DEFINE_REGISTER(UART##num_##_EFR, 0x098, "Enhanced Feature", \
		REGISTER_ENUM(0, 1, "TX software flow control", \
			"TX flow control disabled", \
			"TX XON2/XOFF2 flow control", \
			"TX XON1/XOFF1 flow control", \
			"Unused" \
		), \
		REGISTER_ENUM(2, 3, "RX software flow control", \
			"RX flow control disabled", \
			"RX XON2/XOFF2 flow control", \
			"RX XON1/XOFF1 flow control", \
			"Unused" \
		), \
		REGISTER_BIT_ENABLED(4, "Enhanced features"), \
		REGISTER_BIT_ENABLED(6, "Hardware RX flow control"), \
		REGISTER_BIT_ENABLED(7, "Hardware TX flow control") \
	); \
	DEFINE_REGISTER(UART##num_##_HIGHSPEED, 0x024, "High Speed Mode", \
		REGISTER_ENUM(0, 1, "Sample counter base", \
			"16", "8", "4", "Based on sample counter" \
		) \
	); \
	DEFINE_REGISTER(UART##num_##_SAMPLE_COUNT, 0x028, "Sample Counter", \
		REGISTER_FIELD(0, 7, "Sample counter") \
	); \
	DEFINE_REGISTER(UART##num_##_SAMPLE_POINT, 0x02C, "Sample Point", \
		REGISTER_FIELD(0, 7, "Sample point") \
	); \
	DEFINE_REGISTER(UART##num_##_RATEFIX_AD, 0x034, "Clock Rate Fix", \
		REGISTER_BIT_ENABLED(0, "Rate fix (divide by FREQ_SEL)"), \
		REGISTER_BIT_ENABLED(1, "Autobaud rate fix (divide by FREQ_SEL)"), \
		REGISTER_BIT(2, "FREQ_SEL=4", "FREQ_SEL=2") \
	); \
	DEFINE_REGISTER(UART##num_##_DMA_EN, 0x04C, "DMA Enable", \
		REGISTER_BIT_ENABLED(0, "RX DMA"), \
		REGISTER_BIT_ENABLED(1, "TX DMA"), \
		REGISTER_BIT_ON(2, "Auto-reset RX timeout"), \
		REGISTER_BIT_ON(3, "Auto-update FIFO LSR") \
	); \
	DEFINE_REGISTER(UART##num_##_FRACDIV_L, 0x054, "Fractional Divider LSB", \
		REGISTER_FIELD(0, 7, "High-speed mode fractional divider LSB") \
	); \
	DEFINE_REGISTER(UART##num_##_FRACDIV_M, 0x058, "Fractional Divider MSB", \
		REGISTER_FIELD(0, 1, "High-speed mode fractional divider MSB") \
	); \
	DEFINE_REGISTER(UART##num_##_FCR_RD, 0x05C, "FIFO Control", \
		REGISTER_BIT_ENABLED(0, "RX and TX FIFOs"), \
		REGISTER_BIT_SET(1, "RX FIFO clear"), \
		REGISTER_BIT_SET(2, "TX FIFO clear"), \
		REGISTER_ENUM(4, 5, "TX FIFO trigger threshold", \
			"1", "4", "8", "14"), \
		REGISTER_ENUM(6, 7, "RX FIFO trigger threshold", \
			"1", "6", "12", "RXTRIG") \
	); \
	DEFINE_REGISTER(UART##num_##_FEATURE_SEL, 0x09C, "UART Feature Select", \
		REGISTER_BIT_ENABLED(0, "New register map") \
	);

#define UART_FILE(i_) do { \
	struct dentry *uart_dir = debugfs_create_dir("uart"#i_, regs_dir); \
	u64 base_addr = UART0_BASE + 0x1000 * i_; \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_RBR); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_IER); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_LCR); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_FCR); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_DLL); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_DLM); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_EFR); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_HIGHSPEED); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_SAMPLE_COUNT); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_SAMPLE_POINT); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_RATEFIX_AD); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_DMA_EN); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_FRACDIV_L); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_FRACDIV_M); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_FCR_RD); \
	REGISTER_FILE(uart_dir, base_addr, UART##i_##_FEATURE_SEL); \
	} while (0)

DEFINE_UART(0);
DEFINE_UART(1);
DEFINE_UART(2);
DEFINE_UART(3);

void __init mt6797_debug_uart_regs_init(struct dentry * regs_dir)
{
	UART_FILE(0);
	UART_FILE(1);
	UART_FILE(2);
	UART_FILE(3);
}
