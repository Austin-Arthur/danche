################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer/IfxGtm_Tom_Timer.c 

OBJS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer/IfxGtm_Tom_Timer.o 

COMPILED_SRCS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer/IfxGtm_Tom_Timer.src 

C_DEPS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer/IfxGtm_Tom_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer/%.src: ../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb -I"D:\Smart_car\mybike12\national-games\car_wushua0\CODE" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\doc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Configurations" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_Build" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_Impl" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_Lib" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_Lib\DataHandling" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_Lib\InternalMux" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\_PinMap" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin\Asc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin\Lin" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin\Spi" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Asclin\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\Icu" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\PwmBc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\PwmHl" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\Timer" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Ccu6\TPwm" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cif" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cif\Cam" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cif\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu\CStart" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu\Irq" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Cpu\Trap" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dma" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dma\Dma" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dma\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dsadc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dsadc\Dsadc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dsadc\Rdc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dsadc\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dts" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dts\Dts" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Dts\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Emem" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Emem\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eray" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eray\Eray" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eray\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eth" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eth\Phy_Pef7071" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Eth\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fce" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fce\Crc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fce\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fft" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fft\Fft" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Fft\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Flash" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Flash\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gpt12" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gpt12\IncrEnc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gpt12\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Atom" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Atom\Pwm" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Atom\PwmHl" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Atom\Timer" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tim" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tim\In" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tom" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tom\Pwm" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tom\PwmHl" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Tom\Timer" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Gtm\Trig" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Hssl" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Hssl\Hssl" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Hssl\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\I2c" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\I2c\I2c" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\I2c\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Iom" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Iom\Driver" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Iom\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Msc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Msc\Msc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Msc\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Mtu" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Mtu\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Multican" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Multican\Can" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Multican\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Port" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Port\Io" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Port\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5\Psi5" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5s" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5s\Psi5s" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Psi5s\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Qspi" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Qspi\SpiMaster" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Qspi\SpiSlave" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Qspi\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Scu" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Scu\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Sent" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Sent\Sent" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Sent\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Smu" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Smu\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Src" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Src\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Stm" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Stm\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Stm\Timer" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Vadc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Vadc\Adc" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\iLLD\TC26B\Tricore\Vadc\Std" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Infra" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Infra\Platform" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Infra\Platform\Tricore" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Infra\Platform\Tricore\Compilers" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Infra\Sfr" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Infra\Sfr\TC26B" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Infra\Sfr\TC26B\_Reg" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Service" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Service\CpuGeneric" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Service\CpuGeneric\_Utilities" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Service\CpuGeneric\If" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Service\CpuGeneric\StdIf" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\infineon_libraries\Service\CpuGeneric\SysSe" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\seekfree_libraries" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\seekfree_libraries\common" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Libraries\seekfree_peripheral" -I"D:\Smart_car\mybike12\national-games\car_wushua0\USER" -I"D:\Smart_car\mybike12\national-games\car_wushua0\Brushless_drive" --iso=99 --c++14 --language=+volatile --anachronisms --fp-model=3 --fp-model=c --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer/%.o: ./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Tom/Timer/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


