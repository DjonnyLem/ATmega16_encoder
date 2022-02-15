avr-gcc -Wall -g -Os -mmcu=atmega16 -o dj_usart.o dj_usart.c usart.c 
avr-size -C dj_usart.bin
avr-objcopy -j .text -j .data -O ihex dj_usart.bin dj_usart.hex

#############################################################################################################
Компиляция
Приведенная ниже команда скомпилирует ваш код. Это GCC, поэтому я полагаю, что он вам знаком, и никакой дополнительной информации не требуется. Если вы хотите выполнить компиляцию для другого MCU, вам нужно указать соответствующую опцию -mmcu.

avr-gcc -Wall -g -Os -mmcu=attiny13 -o main.bin main.c
После успешной компиляции вы можете проверить размер памяти программы и данных с помощью этой команды:

Тестер транзисторов / ESR-метр / генераторТестер транзисторов / ESR-метр / генераторМногофункциональный прибор для проверки транзисторов, диодов, тиристоров...Подробнее
avr-size -C main.bin
AVR Memory Usage
—————-
Device: Unknown
Program:      40 bytes
(.text + .data + .bootloader)
Data:          0 bytes
(.data + .bss + .noinit)

Создание .HEX
Большинство программаторов не принимают в качестве входного файла исполняемый файл GNU. Поэтому нам нужно проделать некоторую работу.

Итак, следующий шаг — преобразование информационной формы .BIN в файл .HEX. Утилита GNU, которая делает это, называется avr-objcopy.

avr-objcopy -j .text -j .data -O ihex main.bin main.hex
Программирование
Утилита под названием avrdude может программировать микропроцессоры, используя содержимое файлов .HEX, указанных в командной строке.

С помощью приведенной ниже команды файл main.hex будет записан во флэш-память. Параметр -p attiny13 позволяет avrdude узнать, что мы работаем с микроконтроллером ATtiny13. Другими словами — эта опция определяет устройство.

Полный список поддерживаемых чипов можно найти здесь. Обратите внимание, что также допустимо использовать и полные имена (т. е. t13 равно attiny13).

avrdude -p attiny13 -c usbasp -U flash:w:main.hex:i -F -P usb
И вуаля! Чип запрограммирован.

3. Make и makefiles
Теперь мы можем автоматизировать этот процесс, создав Makefile и поместив туда наши команды. Структура Makefile очень проста, и дополнительную информацию о ней можно найти здесь . Утилита make автоматически считывает файл Makefile в папке, в которой вы ее запускаете. Взгляните на готовый пример:

MCU=attiny13
F_CPU=1200000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.c
all:
${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
flash:
avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb
clean:
rm -f *.bin *.hex
Если вы запустите в терминале простую команду make , будет выполнена только метка «all». При запуске (sudo) make flash будет выполнена метка «flash» и так далее.

make
avr-gcc -std=c99 -Wall -g -Os -mmcu=attiny13 -DF_CPU=1200000 -I. -o main.bin main.c
avr-objcopy -j .text -j .data -O ihex main.bin main.hex

make flash



################################################################################################################


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
