.PHONY: init default buildroot_make
.DEFAULT_GOAL := default

MKBOOTIMG_TAG = 2018.06.15
BUILDROOT_TAG = master

ext/mkbootimg:
	git clone --depth=1 --single-branch --branch=$(MKBOOTIMG_TAG) https://github.com/osm0sis/mkbootimg.git ext/mkbootimg

ext/buildroot:
	git clone --depth=1 --single-branch --branch=$(BUILDROOT_TAG) git://git.buildroot.net/buildroot ext/buildroot

init: ext/buildroot ext/mkbootimg/mkbootimg
	$(call buildroot_make, BR2_DEFCONFIG=../../configs/gemini_pda_defconfig defconfig)

ext/mkbootimg/mkbootimg: ext/mkbootimg
	cd ext/mkbootimg && make $(MAKEFLAGS) $(MAKEOVERRIDES)


# By default, pass control to buildroot's Makefile
default:
	$(call buildroot_make)

buildroot_make:
	$(call buildroot_make, $(MAKECMDGOALS))

%: buildroot_make;

define buildroot_make
	cd ext/buildroot && $(MAKE) BR2_EXTERNAL=../../ $(MAKEFLAGS) $(MAKEOVERRIDES) $1
endef
