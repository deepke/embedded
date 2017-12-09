# embedded

镜像烧写:
1. 在windows7使用工具里sam-ba

在下载好 uboot和boot环境变量之后通过网络下载image和文件系统：
****注意先打开tftp服务器****

1. 设置单板的 serverip 和 ipaddr
	setenv serverip 10.200.223.160
	setenv ipaddr 10.200.223.12

2. 下载 uImage
	tftp 0x70000000 uImage
	nand erase 0x200000 1dc09c
	nand write.i 0x70000000 0x200000  1dc09c

3. 下载rootfs
**** 注意下载地址 ****
**** 在官方的下载文档中写的nandflash的地址是0x400000这个地址是错误的，应该是0x500000 ****
	tftp 0x70000000 Angstrom-x11-image-demo-glibc-at91.rootfs.jffs2 
	nand erase 0x500000 1a00000
	nand write.jffs2 0x70000000 0x500000 0x1a00000

下载命令说明：
	tftp命令的使用：
	tftp [sdram的地址] [下载文件名] [如果是下载不写文件大小，如果写了文件大小表示上传文件]
	
	nand erase 使用：
	擦除nandflash的数据
	nand erase [要擦除nandflash的起始地址] [擦除的长度]
	
	nand write的使用：
	将sdram的数据写入nandflash中
	nand write.jffs2 [sdram的起始地址] [nandflash的起始地址] [写入的长度]
	
	
	
	
	