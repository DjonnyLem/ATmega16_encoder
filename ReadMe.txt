http://we.easyelectronics.ru/AVR/biblioteka-na-si-dlya-lcd-displeev-na-baze-processora-hd44780-dlya-mikrokontrollerov-avr.html

http://elm-chan.org/fsw/ezlcd/00index_e.html
/*
http://forum.easyelectronics.ru/viewtopic.php?f=23&t=32825&hilit=pinboard+linux

Для тех, кто (как я, например) не смог найти ответа в темах "Как, чОрт, под линухом залить прошивку Demo16-RTOS.hex из 5-го пункта инструкции "Pinboard II Быстрый старт. AVR."

1.
Код:
manuel@manuel-P5Q-VM:~/tmp/pb_II_qs_avr$ dmesg | grep FTDI
[...skipped...]
[189173.493329] ftdi_sio 7-2:1.0: FTDI USB Serial Device converter detected
[189173.495356] usb 7-2: FTDI USB Serial Device converter now attached to ttyUSB0
[189173.497317] ftdi_sio 7-2:1.1: FTDI USB Serial Device converter detected
[189173.499354] usb 7-2: FTDI USB Serial Device converter now attached to ttyUSB1


2. жмем резет на модуле с атмегой 16 и:
Код:
manuel@manuel-P5Q-VM:~/tmp/pb_II_qs_avr$ sudo avrdude -p m16 -c avr911 -P /dev/ttyUSB0 -B 19200 -U flash:w:Demo16-RTOS.hex:a

Hide avrdude output:
Connecting to programmer: .
Found programmer: Id = "AVRBOOT"; type = S
Software Version = 0.8; No Hardware Version given.
Programmer supports auto addr increment.
Programmer supports buffered memory access with buffersize=128 bytes.

Programmer supports the following devices:
Device code: 0x75

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.01s

avrdude: Device signature = 0x1e9403 (probably m16)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "Demo16-RTOS.hex"
avrdude: input file Demo16-RTOS.hex auto detected as Intel Hex
avrdude: writing flash (1642 bytes):

Writing | ################################################## | 100% 1.25s

avrdude: 1642 bytes of flash written
avrdude: verifying flash memory against Demo16-RTOS.hex:
avrdude: load data flash data from input file Demo16-RTOS.hex:
avrdude: input file Demo16-RTOS.hex auto detected as Intel Hex
avrdude: input file Demo16-RTOS.hex contains 1642 bytes
avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 1.25s

avrdude: verifying ...
avrdude: 1642 bytes of flash verified

avrdude: safemode: Sorry, reading back fuses was unreliable. I have given up and exited programming mode

avrdude done. Thank you.
/*
