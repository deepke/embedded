################################################################################
#    SAM-BA history file
################################################################################

################################################################################
    global target
################################################################################

NANDFLASH::Init
GENERIC::EraseAll
GENERIC::SendBootFile "nandflash_at91sam9g45ekes.bin"
send_file {NandFlash} "usb_hid_transfer.bin" 0x20000 0


