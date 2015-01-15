################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c6000_7.4.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./vecs_irq.obj" \
"./timer.obj" \
"./main.obj" \
"./lumatrixinv.obj" \
"./ident.obj" \
"./gpcregler.obj" \
"./enkoder.obj" \
"./McBSP_Utility.obj" \
"./MatrixVectorOp.obj" \
"./MainLoop_Helper.obj" \
"./IRQ_Utility.obj" \
"./I2C_Utility.obj" \
"./EDMA_Utility.obj" \
"./DAC7716.obj" \
"./Command_Utility.obj" \
"./CPLD.obj" \
"./ADC8361.obj" \
"../mcbsp1.cmd" \
-l"C:\ti\ccsv5\tools\compiler\c6000_7.4.4\lib\dsk6713bsl.lib" \
-l"C:\ti\ccsv5\tools\compiler\c6000_7.4.4\lib\csl6713.lib" \
-l"rts6700.lib" \
-l"C:\CCStudio\c6700\dsplib\lib\dsp67x.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: mcbsp1.out

# Tool invocations
mcbsp1.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" --abi=coffabi -O1 -g --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off -z --stack_size=0x800 -m"HelikopterGPC.map" -i"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/lib" -i"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" -i"C:/Users/Adam/workspace_v5_5/HelikopterGPC" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="HelikopterGPC_linkInfo.xml" --rom_model -o "mcbsp1.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C6000_EXECUTABLE_OUTPUTS__QUOTED) "mcbsp1.out"
	-$(RM) "ADC8361.pp" "CPLD.pp" "Command_Utility.pp" "DAC7716.pp" "EDMA_Utility.pp" "I2C_Utility.pp" "IRQ_Utility.pp" "MainLoop_Helper.pp" "MatrixVectorOp.pp" "McBSP_Utility.pp" "enkoder.pp" "gpcregler.pp" "ident.pp" "lumatrixinv.pp" "main.pp" "timer.pp" 
	-$(RM) "ADC8361.obj" "CPLD.obj" "Command_Utility.obj" "DAC7716.obj" "EDMA_Utility.obj" "I2C_Utility.obj" "IRQ_Utility.obj" "MainLoop_Helper.obj" "MatrixVectorOp.obj" "McBSP_Utility.obj" "enkoder.obj" "gpcregler.obj" "ident.obj" "lumatrixinv.obj" "main.obj" "timer.obj" "vecs_irq.obj" 
	-$(RM) "vecs_irq.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

