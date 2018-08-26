################################################################################
#
# mt6797_debug
#
################################################################################

MT6797_DEBUG_VERSION = dev
MT6797_DEBUG_LICENSE = GPL-2.0
MT6797_DEBUG_KCONFIG_FILE = $(BR2_EXTERNAL_GEMINI_PATH)/package/mt6797_debug/src/Kconfig
MT6797_DEBUG_KCONFIG_EDITORS = menuconfig
MT6797_DEBUG_DEFCONFIG_FILE = $(BR2_EXTERNAL_GEMINI_PATH)/package/mt6797_debug/src/defconfig
MT6797_DEBUG_SITE_METHOD = local
MT6797_DEBUG_SITE = $(BR2_EXTERNAL_GEMINI_PATH)/package/mt6797_debug/src
$(eval $(kernel-module))
$(eval $(generic-package))
