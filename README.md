# STM32F4_Discovery_VIN_Projects

## Initial_Breadboard_VIN
- osnovni demo z nekaj diodami in tipkami

## LED_Blink_Demo

- 4 diode utripajo vsake 2 sekundi

## LED_Blink_Demo_QEMU

- 4 diode utripajo vsake 2 sekundi v QEMU emulirani STM32F4Disco ploščici

## LED PWM Demo
- 4 diode se postopoma prižigajo/ugašajo (s PWM modulacijo)

## Buzzer_PWM_Demo
- s pomočjo spreminjanja periode PWM signala ob konstantnem 50% "duty" se igrajo melodije na brenčaču (PA15 in GND)
- melodije so zapisane v "melody.h"

## Audio_playback_and_record
- v bistvu je to demo projekt iz zbirke Cube_F4, ki vsebuje različne primere posameznih funkctionalnosti
- aplikacija predvaja zvok (izhod za slušalke) iz wav datoteke na USB ključku
- s pritiskom na USER tipko sprožimo snemanje na USB ključek (rec.wav)
- ostale podrobnosti so v projektu (berime.txt in readme.txt) 
