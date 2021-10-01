# LED_Blink_Demo_QEMU

## XPack QEMU xpack-qemu-arm-2.8.0-12>
- .\bin\qemu-system-gnuarmeclipse --verbose --verbose --board STM32F4-Discovery --mcu STM32F407VG --gdb tcp::1234 -d unimp,guest_errors  --semihosting-config enable=on,target=native --semihosting-cmdline LED_Blink_Demo


## CubeIDE settings/instructions

got it working - brief instructions :
- Debug Configurations
	- JLink and STlink(GDB) don't work - famous chip check "Cannot verify ST device !"
	- STLink (OpenOCD) is the way to go - with Live expressions disabled
- FP unit is not supported in QEMU, so it has to be removed from project
	- Project-Settings-C/C++Buiold-Settings-Tool Sett.-MCU Sett.-> FP Unit and FP ABI set to None and Software impl. respectively
	- in file   system_stm32f4xx.c FPU setting should be commented
			i. void SystemInit(void)
			ii.  {
			iii.  /* FPU settings ------------------------------------------------------------*/
			iv.  // #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
			v.  // SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2)); /* set CP10 and CP11 Full Access */
			vi.  // #endif
- Now LED diodes blink on QEMU STMF4Discovery displayed (simulated) board

From <https://community.st.com/s/question/0D73W000001MMvC/detail?s1oid=00Db0000000YtG6&t=1633116203317&s1nid=0DB0X000000DYbd&emkind=chatterCommentNotification&s1uid=0050X000008AYPO&emtm=1633083403015&fromEmail=1&s1ext=0> 
