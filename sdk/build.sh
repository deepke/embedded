#!/bin/bash
#base.mak  build.sh  
#configs  
#crosstools  
#kernel  
#linux-2.6.30.tar.bz2  
#Makefile  
#patch  
#uboot  
#u-boot-1.3.4.tar.bz2

SDK_DIR=$(pwd)
echo "${SDK_DIR}"

OUT_DIR=${SDK_DIR}/out
TOOLS_DIR=${SDK_DIR}/crosstools
BOOTSTRAP_DIR=${SDK_DIR}/bootstrap
KERNEL_DIR=${SDK_DIR}/kernel
FS_DIR=${SDK_DIR}/rootfs
DMS_DIR=${SDK_DIR}/dms
BOOT_DIR=${SDK_DIR}/uboot

KERNEL_VERSION=linux-2.6.30
KERNEL_IMAGE=uImage

UBOOT_VERSION=u-boot-1.3.4
MKIMAGE_FILE=${BOOT_DIR}/${UBOOT_VERSION}/mkimage

test -d patch || echo "sdada"
