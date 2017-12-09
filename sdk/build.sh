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
SOURCE_DIR=${SDK_DIR}/source
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
			tar -xjvf ${SOURCE_DIR}/arm-2007q1-10-arm-none-linux-gnueabi.tar.bz2 -C ${TOOLS_DIR}/${CROSSTOOL_VERSION}
		fi
		#bootstrap
		if [ ! -d ${BOOTSTRAP_DIR} ] ; then
			mkdir -p ${BOOTSTRAP_DIR}
			tar -xjvf ${SOURCE_DIR}/bootstrap-v1.14.tar.bz2 -C ${BOOTSTRAP_DIR}
		fi
		#uboot
		if [ ! -d ${BOOT_DIR} ] ; then
			mkdir -p ${BOOT_DIR}
			tar -xjvf ${SOURCE_DIR}/u-boot-1.3.4.tar.bz2 -C ${BOOT_DIR}
		fi
		#kernel
		if [ ! -d ${KERNEL_DIR} ] ; then
			mkdir -p ${KERNEL_DIR}
			tar -xjvf ${SOURCE_DIR}/${KERNEL_VERSION}.tar.bz2 -C ${KERNEL_DIR}
			cd ${KERNEL_DIR}/${KERNEL_VERSION}
			patch -p1 < ${SOURCE_DIR}/patch/2.6.30-at91.patch.gz
			tar xvzf ${SOURCE_DIR}/patch/2.6.30-at91-exp.4.tar.gz -C ./
			for p in 2.6.30-at91-exp.4/*; do patch -p1 < $p ; done
			patch -p1 < ${SOURCE_DIR}/patch/embest_all_modify.diff
			cd -
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
		#out
		if [ ! -d ${OUT_DIR} ] ; then
			mkdir -p ${OUT_DIR}
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
		#out
		if [ ! -d ${OUT_DIR} ] ; then
			rm -rf ${OUT_DIR}
		fi
	fi
}

init_sdk $1

echo "init sdk success"
