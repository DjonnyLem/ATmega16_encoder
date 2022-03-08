MCU=atmega16
F_CPU=800000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.c

all:
	avr-gcc -Wall -g -Os -mmcu=atmega16 -o main.o main.c 
	avr-objcopy -j .text -j .data -O ihex main.o main.hex


#${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}*/
#${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
flash:
	sudo avrdude -p m16 -c avr911 -P /dev/ttyUSB0 -B 19200 -U flash:w:main.hex:a

#avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb
clean:
	rm -f *.bin *.hex *.o
#Если вы запустите в терминале простую команду make , будет выполнена только метка «all». При запуске (sudo) make flash будет выполнена метка «flash» и так далее.





