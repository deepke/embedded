#!/bin/bash
SDK_DIR=$(pwd)
BOOT_DIR=${SDK_DIR}/uboot
UBOOT_VERSION=u-boot-1.3.4
MKIMAGE_DIR=${BOOT_DIR}/${UBOOT_VERSION}/tools
export PATH="${PATH}:${MKIMAGE_DIR}"

