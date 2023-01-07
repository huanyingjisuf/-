################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
RF_PHY_20221117.hex \

SECONDARY_SIZE += \
RF_PHY_20221117.siz \


# 所有目标
all: RF_PHY_20221117.elf secondary-outputs

# 工具调用
RF_PHY_20221117.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "D:\沁恒开发程序\无线LED_20221117\EXAM\SRC\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"D:\沁恒开发程序\无线LED_20221117\EXAM\BLE\LIB" -L"D:\沁恒开发程序\无线LED_20221117\EXAM\SRC\StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"RF_PHY_20221117.map" --specs=nano.specs --specs=nosys.specs -o "RF_PHY_20221117.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
RF_PHY_20221117.hex: RF_PHY_20221117.elf
	@	riscv-none-embed-objcopy -O ihex "RF_PHY_20221117.elf"  "RF_PHY_20221117.hex"
	@	@
RF_PHY_20221117.siz: RF_PHY_20221117.elf
	@	riscv-none-embed-size --format=berkeley "RF_PHY_20221117.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) RF_PHY_20221117.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
