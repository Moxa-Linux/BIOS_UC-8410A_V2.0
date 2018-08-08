#----------------------------------------------------------------------------
#Rev   Date         Name  Description
#----------------------------------------------------------------------------
#!/usr/bin/env python

import os
import sys

MLO_ADDRESS = 0x00000000
U_BOOT_ADDRESS = 0x00010000	
U_BOOT_ENV_ADDRESS = 0x00380000

SPI_FLASH_SIZE = 0x00400000

OUTPUT_FILE = "SPI.ROM"

if __name__ == '__main__':
    # sys.argv[0] MLO.byteswap u-boot.bin
    if len(sys.argv) != 4:
        print "%s MLO.byteswap u-boot.img /path/for/output/file" % sys.argv[0]
        sys.exit()

    with open(os.path.join(sys.argv[3], OUTPUT_FILE), "wb") as output_file:
        count = 0
        with open(sys.argv[1]) as mlo_file:
            byte = mlo_file.read(1)
            while byte != "":
                output_file.write(byte)
                count = count + 1
                byte = mlo_file.read(1)

        output_file.write(chr(0xff) * (U_BOOT_ADDRESS - count))

        count = 0
        with open(sys.argv[2]) as uboot_file:
            byte = uboot_file.read(1)
            while byte != "":
                output_file.write(byte)
                count = count + 1
                byte = uboot_file.read(1)

        output_file.write(chr(0xff) * (U_BOOT_ENV_ADDRESS - U_BOOT_ADDRESS - count))

        output_file.write(chr(0xff) * (SPI_FLASH_SIZE - U_BOOT_ENV_ADDRESS))
