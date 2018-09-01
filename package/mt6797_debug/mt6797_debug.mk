################################################################################
#
# mt6797_debug
#
################################################################################

MT6797_DEBUG_VERSION = dev
MT6797_DEBUG_LICENSE = GPL-2.0
MT6797_DEBUG_SITE_METHOD = local
MT6797_DEBUG_SITE = $(BR2_EXTERNAL_GEMINI_PATH)/package/mt6797_debug/src
MT6797_DEBUG_MODULE_MAKE_OPTS = \
	MT6797_DEBUG_FORCE_UART=$(MT6797_DEBUG_FORCE_UART)
$(eval $(kernel-module))
$(eval $(generic-package))
