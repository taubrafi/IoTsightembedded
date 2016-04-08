################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./conversions.obj" \
"./main.obj" \
"./network_common.obj" \
"./network_if.obj" \
"./pinmux.obj" \
"./serial_wifi.obj" \
"./startup_ccs.obj" \
"./uart_config.obj" \
"./uart_if.obj" \
"../cc3200v1p32.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/serial_wifi/ccs/../../../oslib/ccs/free_rtos/free_rtos.a" \
-l"C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/serial_wifi/ccs/../../../simplelink/ccs/OS/simplelink.a" \
-l"C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/serial_wifi/ccs/../../../driverlib/ccs/Release/driverlib.a" \

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
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
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
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
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
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
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
EXE_OUTPUTS += \
serial_wifi.out \

EXE_OUTPUTS__QUOTED += \
"serial_wifi.out" \

BIN_OUTPUTS += \
serial_wifi.bin \

BIN_OUTPUTS__QUOTED += \
"serial_wifi.bin" \


# All Target
all: serial_wifi.out

# Tool invocations
serial_wifi.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me -g --gcc --define=__CCS__ --define=ccs --define=USE_FREERTOS --define=SL_PLATFORM_MULTI_THREADED --define=PLATFORM_LP --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number -z -m"serial_wifi.map" --heap_size=0x00008000 --stack_size=0x00001000 -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --reread_libs --priority --display_error_number --diag_wrap=off --warn_sections --xml_link_info="serial_wifi_linkInfo.xml" --rom_model -o "serial_wifi.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

serial_wifi.bin: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armhex"  -o "serial_wifi.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "conversions.pp" "main.pp" "network_common.pp" "network_if.pp" "pinmux.pp" "serial_wifi.pp" "startup_ccs.pp" "uart_config.pp" "uart_if.pp" 
	-$(RM) "conversions.obj" "main.obj" "network_common.obj" "network_if.obj" "pinmux.obj" "serial_wifi.obj" "startup_ccs.obj" "uart_config.obj" "uart_if.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Converting to bin'
	-"C:/ti/ccsv6/utils/tiobj2bin/tiobj2bin" "serial_wifi.out" "serial_wifi.bin" "C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armofd" "C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armhex" "C:/ti/ccsv6/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

