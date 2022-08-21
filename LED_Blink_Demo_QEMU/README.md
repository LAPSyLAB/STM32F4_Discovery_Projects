# LED_Blink_Demo_QEMU Howto

## XPack QEMU xpack-qemu-arm-2.8.0-12>
**QEMU xpack GDB server** 

		Is already included in project and nothing should be done separately...

**QEMU xpack GDB server can be started manually if needed**

* From project :
 * start **run_QEMU.bat**
 
* or externally :
 * .\bin\qemu-system-gnuarmeclipse --verbose --verbose --board STM32F4-Discovery --mcu STM32F407VG --gdb tcp::1234 -d unimp,guest_errors  --semihosting-config enable=on,target=native --semihosting-cmdline LED_Blink_Demo

## CubeIDE settings/instructions

Got it working in newer version of CubeIDE (05/2022) - brief instructions :

- **Install additional Software modules**
	- **QEMU embedded debugging plugin** (Install New Software -> search for "QEMU"
	- GNU GDB from ARM Cross Toolchain
		- Gnu GDB is already included in project (gdb folder)
		

- **Debug Configurations**
	- Create new configuration under QEMU DBG Debugging line
	- Setup all necessary paths 
		- use local xpack for QEMU
		- use local GDB from project
		- set all other parameters similarly to above parameters for manual start of xpack QEMU

## CubeIDE project settings/instructions

- **FP unit is not supported in QEMU**, so it has to be **removed from project**
	- **Project-Settings** -> C/C++ -> Build-Settings -> Tool Sett. -> MCU Sett.-> FP Unit and FP ABI set to None and Software impl. respectively
	
	- in **file   system_stm32f4xx.c**  FPU setting should be commented
> 			void SystemInit(void)
> 			{
> 			  /* FPU settings ------------------------------------------------------------*/
> 			  // #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
> 			  // SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2)); /* set CP10 and CP11 Full Access */
> 			  // #endif
> 			    


### **Sources :**

https://www.youtube.com/watch?v=CdH-cad8DSw&ab_channel=geek_eng

<https://community.st.com/s/question/0D73W000001MMvC/detail?s1oid=00Db0000000YtG6&t=1633116203317&s1nid=0DB0X000000DYbd&emkind=chatterCommentNotification&s1uid=0050X000008AYPO&emtm=1633083403015&fromEmail=1&s1ext=0> 
 
 https://developer.arm.com/downloads/-/gnu-rm
 
 https://eclipse-embed-cdt.github.io/
 
 
# CubeIDE settings/instructions

got it working - brief instructions :

- **Debug Configurations**
	- JLink and STlink(GDB) don't work - famous chip check "Cannot verify ST device !"
	- **STLink (OpenOCD) is the way to go** - with **Live expressions disabled**


- **FP unit is not supported in QEMU**, so it has to be **removed from project**
	- **Project-Settings** -> C/C++ -> Build-Settings -> Tool Sett. -> MCU Sett.-> FP Unit and FP ABI set to None and Software impl. respectively
	
	- in **file   system_stm32f4xx.c**  FPU setting should be commented
> 			void SystemInit(void)
> 			{
> 			  /* FPU settings ------------------------------------------------------------*/
> 			  // #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
> 			  // SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2)); /* set CP10 and CP11 Full Access */
> 			  // #endif
