################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
gpio_if.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/gpio_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/oslib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_FREERTOS --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="gpio_if.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/oslib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_FREERTOS --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

network_common.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/network_common.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/oslib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_FREERTOS --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="network_common.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

network_if.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/network_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/oslib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/third_party/FreeRTOS/source/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/third_party/FreeRTOS/source/include/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_FREERTOS --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="network_if.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pinmux.obj: ../pinmux.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/oslib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_FREERTOS --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pinmux.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/oslib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_FREERTOS --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer_if.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/timer_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/oslib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_FREERTOS --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="timer_if.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_if.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/uart_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/oslib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_FREERTOS --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="uart_if.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

utils_if.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/utils_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/oslib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_FREERTOS --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="utils_if.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


