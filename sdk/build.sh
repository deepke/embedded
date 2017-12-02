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
SOURCE_DIR=$(SDK_DIR)/source
TOOLS_DIR=${SDK_DIR}/crosstools
BOOTSTRAP_DIR=${SDK_DIR}/bootstrap
KERNEL_DIR=${SDK_DIR}/kernel
FS_DIR=${SDK_DIR}/rootfs
DMS_DIR=${SDK_DIR}/dms
BOOT_DIR=${SDK_DIR}/uboot
CONFIGS_DIR=${SDK_DIR}/configs
PATCH_DIR=${SDK_DIR}/patch

KERNEL_IMAGE=uImage

KERNEL_VERSION=linux-2.6.30
BOOTSTRAP_VERSION=bootstrap-v1.14
UBOOT_VERSION=u-boot-1.3.4
MKIMAGE_FILE=${BOOT_DIR}/${UBOOT_VERSION}/mkimage
function init_sdk()
{
	local clean=$1
	local CUR_DIR=
	if [ "${clean}" != "clean" ] ; then
		#tools
		if [ ! -d ${TOOLS_DIR} ] ; then
			mkdir -p ${TOOLS_DIR}
		fi
		#bootstrap
		if [ ! -d ${BOOTSTRAP_DIR} ] ; then
			mkdir -p ${BOOTSTRAP_DIR}
		fi
		#uboot
		if [ ! -d ${BOOT_DIR} ] ; then
			mkdir -p ${BOOT_DIR}
		fi
		#kernel
		if [ ! -d ${KERNEL_DIR} ] ; then
			mkdir -p ${KERNEL_DIR}
		fi
		#fs
		if [ ! -d ${FS_DIR} ] ; then
			mkdir -p ${FS_DIR}
		fi
		#dms
		if [ ! -d ${DMS_DIR} ] ; then
			mkdir -p ${DMS_DIR}
		fi
		#configs
		if [ ! -d ${CONFIGS_DIR} ] ; then
			mkdir -p ${CONFIGS_DIR}
		fi
		#patch
		if [ ! -d ${PATCH_DIR} ] ; then
			mkdir -p ${PATCH_DIR}
		fi
	else
		#clean
		#tools
		if [ -d ${TOOLS_DIR} ] ; then
			rm -rf ${TOOLS_DIR}
		fi
		#bootstrap
		if [ -d ${BOOTSTRAP_DIR} ] ; then
			rm -rf ${BOOTSTRAP_DIR}
		fi
		#uboot
		if [ -d ${BOOT_DIR} ] ; then
			rm -rf ${BOOT_DIR}
		fi
		#kernel
		if [ -d ${KERNEL_DIR} ] ; then
			rm -rf ${KERNEL_DIR}
		fi
		#fs
		if [ -d ${FS_DIR} ] ; then
			rm -rf ${FS_DIR}
		fi
		#dms
		if [ -d ${DMS_DIR} ] ; then
			rm -rf ${DMS_DIR}
		fi
		#configs
		if [ -d ${CONFIGS_DIR} ] ; then
			rm -rf ${CONFIGS_DIR}
		fi
		#patch
		if [ -d ${PATCH_DIR} ] ; then
			rm -rf ${PATCH_DIR}
		fi
	if
}

echo "init sdk success"
