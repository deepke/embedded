################################################################################
#    SAM-BA history file
################################################################################

################################################################################
    global target
################################################################################

NANDFLASH::Init
#GENERIC::EraseAll
GENERIC::SendBootFile "FIRSTBOOT.nb0"
send_file {NandFlash} "EBOOT.nb0" 0x80000 0
send_file {NandFlash} "NK.nb0" 0x200000 0
