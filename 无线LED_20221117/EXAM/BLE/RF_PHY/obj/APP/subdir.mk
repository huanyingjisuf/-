################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/RF_PHY.c \
../APP/RF_main.c 

OBJS += \
./APP/RF_PHY.o \
./APP/RF_main.o 

C_DEPS += \
./APP/RF_PHY.d \
./APP/RF_main.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"D:\�ߺ㿪������\����LED_20221117\EXAM\SRC\Startup" -I"D:\�ߺ㿪������\����LED_20221117\EXAM\BLE\RF_PHY\APP\include" -I"D:\�ߺ㿪������\����LED_20221117\EXAM\SRC\StdPeriphDriver\inc" -I"D:\�ߺ㿪������\����LED_20221117\EXAM\BLE\HAL\include" -I"D:\�ߺ㿪������\����LED_20221117\EXAM\SRC\Ld" -I"D:\�ߺ㿪������\����LED_20221117\EXAM\BLE\LIB" -I"D:\�ߺ㿪������\����LED_20221117\EXAM\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

