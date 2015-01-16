################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CPLD.obj: ../CPLD.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="CPLD.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Command_Utility.obj: ../Command_Utility.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Command_Utility.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DAC7716.obj: ../DAC7716.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DAC7716.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

EDMA_Utility.obj: ../EDMA_Utility.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="EDMA_Utility.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

I2C_Utility.obj: ../I2C_Utility.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="I2C_Utility.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

IRQ_Utility.obj: ../IRQ_Utility.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="IRQ_Utility.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MainLoop_Helper.obj: ../MainLoop_Helper.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="MainLoop_Helper.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MatrixVectorOp.obj: ../MatrixVectorOp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="MatrixVectorOp.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

McBSP_Utility.obj: ../McBSP_Utility.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="McBSP_Utility.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

enkoder.obj: ../enkoder.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="enkoder.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

gpcregler.obj: ../gpcregler.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="gpcregler.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ident.obj: ../ident.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="ident.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

lumatrixinv.obj: ../lumatrixinv.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="lumatrixinv.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer.obj: ../timer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="timer.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

vecs_irq.obj: ../vecs_irq.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.11/bin/cl6x" --abi=coffabi -O3 -ms3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="C:/Program Files/C6xCSL/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.8/dsk6713/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="vecs_irq.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


