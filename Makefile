default:
	avr-gcc -Os -mmcu=atmega2560 -c *.c
	avr-gcc -mmcu=atmega2560 *.o -o a.elf
	avr-objcopy -O ihex -R .eeprom a.elf a.hex
	avrdude -F -v -c wiring -D -p ATMEGA2560 -P /dev/ttyACM0 -b 115200 -U flash:w:a.hex:i

clean:
	rm *.o
	rm *.hex
	rm *.elf
