################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/沁恒开发程序/无线LED组网_20221212/EXAM/BLE/HAL/MCU.c \
D:/沁恒开发程序/无线LED组网_20221212/EXAM/BLE/HAL/RTC.c \
D:/沁恒开发程序/无线LED组网_20221212/EXAM/BLE/HAL/SLEEP.c 

OBJS += \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o 

C_DEPS += \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/MCU.o: D:/沁恒开发程序/无线LED组网_20221212/EXAM/BLE/HAL/MCU.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\Startup" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\BLE\RF_PHY\APP\include" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\StdPeriphDriver\inc" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\BLE\HAL\include" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\Ld" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\BLE\LIB" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
HAL/RTC.o: D:/沁恒开发程序/无线LED组网_20221212/EXAM/BLE/HAL/RTC.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\Startup" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\BLE\RF_PHY\APP\include" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\StdPeriphDriver\inc" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\BLE\HAL\include" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\Ld" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\BLE\LIB" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
HAL/SLEEP.o: D:/沁恒开发程序/无线LED组网_20221212/EXAM/BLE/HAL/SLEEP.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\Startup" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\BLE\RF_PHY\APP\include" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\StdPeriphDriver\inc" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\BLE\HAL\include" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\Ld" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\BLE\LIB" -I"D:\沁恒开发程序\无线LED组网_20221212\EXAM\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

