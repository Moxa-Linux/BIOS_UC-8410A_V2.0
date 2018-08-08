#!/usr/bin/env python

import os
import sys

SPI_FLASH_SIZE = 0x00800000

OUTPUT_FILE = "bios.rom"

if __name__ == '__main__':
    # sys.argv[0] u-boot.bos output_dir
    if len(sys.argv) != 3:
        print "%s u-boot.bos /path/for/output/file" % sys.argv[0]
        sys.exit()

    with open(os.path.join(sys.argv[2], OUTPUT_FILE), "wb") as output_file:
        count = 0
        with open(sys.argv[1]) as uboot_file:
            byte = uboot_file.read(1)
            while byte != "":
                output_file.write(byte)
                count = count + 1
                byte = uboot_file.read(1)

        output_file.write(chr(0xff) * (SPI_FLASH_SIZE - count))
