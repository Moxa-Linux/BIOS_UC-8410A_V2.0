source ./env_ls1021a.sh

# Check the number of parameters

rm -rf ./ls1021a
mkdir -p ./ls1021a
rm -rf ./output/*
rm  ./u-boot.*

rm -rf ./common/MOXA_BIOS

make O=ls1021a CROSS_COMPILE=arm-linux-gnueabihf- mrproper

		mkdir -p ./common/MOXA_BIOS
		cp ./common/MOXA_SRC/common/*.* ./common/MOXA_BIOS
		cp ./common/MOXA_SRC/common/Makefile ./common/MOXA_BIOS
		cp ./common/MOXA_SRC/model/bios.h ./include/bios.h
		cp ./common/MOXA_SRC/model/UC_8410A.h ./include/model.h
		cp ./common/MOXA_SRC/io/LED/*.* ./common/MOXA_BIOS/

		echo "******************************"
		echo "** UC-8400A QSPI Boot       **"
		echo "******************************"
#qds		cp ./board/freescale/ls1021aqds/qspi_ls1_pbi.cfg ./board/freescale/ls1021aqds/ls102xa_pbi.cfg
#qds		make O=ls1021a CROSS_COMPILE=arm-linux-gnueabihf- ls1021aqds_qspi_defconfig
		cp ./board/freescale/ls1021atwr/qspi_ls1_pbi.cfg ./board/freescale/ls1021atwr/ls102xa_pbi.cfg
		make O=ls1021a CROSS_COMPILE=arm-linux-gnueabihf- ls1021atwr_qspi_defconfig


make -j8 O=ls1021a CROSS_COMPILE=arm-linux-gnueabihf- all 2> ./build.log


echo "##### Build Log - START #####"
cat ./build.log
echo "##### Build Log - END #####"
rm -rf ./build.log

mkdir -p ./output

# Check The Model

		cp ./ls1021a/u-boot.pbl ./u-boot.pbl
		tclsh ./byte_swap.tcl ./u-boot.pbl ./u-boot.bos 8	
		cp ./u-boot.bos ./output/u-boot.bos
		/usr/bin/python build_rom.py ./output/u-boot.bos ./output/
		

