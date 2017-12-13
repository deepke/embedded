# 获得当前目录
SDK_DIR := $(CURDIR)

include base.mak

OUT_DIR                 ?= $(SDK_DIR)/out
TOOLS_DIR               := $(SDK_DIR)/crosstools
BOOTSTRAP_DIR           := $(SDK_DIR)/bootstrap
KERNEL_DIR              := $(SDK_DIR)/kernel
FS_DIR                  := $(SDK_DIR)/rootfs
DMS_DIR                 := $(SDK_DIR)/dms
BOOT_DIR                := $(SDK_DIR)/uboot

BOOTSTRAP_VERSION	?=	bootstrap-v1.14
UBOOT_VERSION   	?= 	u-boot-1.3.4
KERNEL_VERSION  	?= 	linux-2.6.30
CROSSTOOL_VERSION  	?= 	arm-2007q1

UBOOT_CONFIG_FILE	?=	at91sam9g45ekes_nandflash_config
KERNEL_IMAGE    	?=	uImage
MKIMAGE_FILE    	?=	$(BOOT_DIR)/$(UBOOT_VERSION)/mkimage

MAKE_PARAM_LIST := ARCH=arm
MAKE_PARAM_LIST += CROSS_COMPILE=$(TOOLS_DIR)/${CROSSTOOL_VERSION}/bin/arm-none-linux-gnueabi-

#*
#*	镜像编译
#*
.PHONY: all bootstrap boot kernel fs dms

all:bootstrap boot kernel fs dms
	echo "all"

bootstrap:
	make -C $(BOOTSTRAP_DIR)/$(BOOTSTRAP_VERSION)/board/at91sam9g45ekes/nandflash $(MAKE_PARAM_LIST)
	cp -f $(BOOTSTRAP_DIR)/$(BOOTSTRAP_VERSION)/board/at91sam9g45ekes/nandflash/nandflash_at91sam9g45ekes.bin $(OUT_DIR)

boot:
	make -C $(BOOT_DIR)/$(UBOOT_VERSION) $(UBOOT_CONFIG_FILE) $(MAKE_PARAM_LIST)
	make -C $(BOOT_DIR)/$(UBOOT_VERSION) $(MAKE_PARAM_LIST)
	cp -f $(BOOT_DIR)/$(UBOOT_VERSION)/u-boot.bin $(OUT_DIR)

kernel:
	#cp $(KERNEL_DIR)/$(KERNEL_VERSION)/arch/arm/configs/embest_EM-SAM9G45_4.3lcd_defconfig $(KERNEL_DIR)/$(KERNEL_VERSION)/.config
	make -C $(KERNEL_DIR)/$(KERNEL_VERSION) $(KERNEL_IMAGE) $(MAKE_PARAM_LIST)
	cp -f $(KERNEL_DIR)/$(KERNEL_VERSION)/arch/arm/boot/$(KERNEL_IMAGE) $(OUT_DIR)
#CP -f MKIMAGE_FILE

kernel_cfg:
	cp $(KERNEL_DIR)/$(KERNEL_VERSION)/arch/arm/configs/embest_EM-SAM9G45_4.3lcd_defconfig $(KERNEL_DIR)/$(KERNEL_VERSION)/.config

fs:
	echo "fs"


dms:
	make -C $(DMS_DIR) all $(MAKE_PARAM_LIST)


#*
#*
.PHONY: menuconfig menuconfig_kernel

menuconfig: menuconfig_kernel
	echo "menuconfig"

menuconfig_kernel:
	make -C $(KERNEL_DIR)/$(KERNEL_VERSION) $(MAKE_PARAM_LIST)  menuconfig

#*
#*
.PHONY: clean clean_kernel clean_boot

clean_boot:
	make -C $(BOOT_DIR)/$(UBOOT_VERSION) distclean $(MAKE_PARAM_LIST)
	make -C $(BOOT_DIR)/$(UBOOT_VERSION) clean $(MAKE_PARAM_LIST)

clean_kernel:
	make -C $(KERNEL_DIR)/$(KERNEL_VERSION) clean

clean:clean_kernel clean_boot
	echo "clean success"


