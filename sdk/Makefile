# 获得当前目录
SDK_DIR := $(CURDIR)

include base.mak

MAKE_PARAM_LIST ?=

OUT_DIR ?= $(SDK_DIR)/out

TOOLS_DIR := $(SDK_DIR)/crosstools

BOOTSTRAP_DIR 	:= $(SDK_DIR)/bootstrap
KERNEL_DIR 		:= $(SDK_DIR)/kernel
FS_DIR 			:= $(SDK_DIR)/rootfs
DMS_DIR 		:= $(SDK_DIR)/dms
BOOT_DIR 		:= $(SDK_DIR)/uboot

KERNEL_VERSION	?= linux-2.6.30
KERNEL_IMAGE	:= uImage

UBOOT_VERSION	?= u-boot-1.3.4
MKIMAGE_FILE	:= $(BOOT_DIR)/$(UBOOT_VERSION)/mkimage

MAKE_PARAM_LIST ?= ARCH=arm
MAKE_PARAM_LIST += CROSS_COMPILE=$(TOOLS_DIR)/arm-2007q1/bin/arm-none-linux-guneabi-

test:
	echo $(SDK_DIR)

.PHONY: bootstrap boot kernel fs boot dms clean kernel_clean

bootstrap:

boot:

kernel:
	make all -C $(KERNEL_DIR)/$(KERNEL_VERSION) $(KERNEL_IMAGE) $(MAKE_PARAM_LIST)
fs:

boot:

dms:
	make all -C $(DMS_DIR) $(MAKE_PARAM_LIST)

kernel_clean:
	make all -C $(KERNEL_DIR)/$(KERNEL_VERSION) clean

clean:kernel_clean
	echo "clean success"

