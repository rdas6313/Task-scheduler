CC = arm-none-eabi-gcc
CPU = cortex-m3
CFLAGS = -c -mcpu=$(CPU) -mthumb -g -O0 -I inc -Wall -std=gnu11 -mfloat-abi=soft 
LFLAGS = -Wl,-Map=final.map -Wall -g --specs=rdimon.specs -mcpu=$(CPU) -mthumb -mfloat-abi=soft -u _printf_int -u _printf_float -lc -lrdimon
SRC_DIR = src

.PHONY: clear run 

firmware.elf: startup.o main.o
	$(CC) $(LFLAGS) -T linker.ld $^ -o $@

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $^ -o $@

run:
	qemu-system-arm -M stm32vldiscovery -cpu cortex-m3 -semihosting-config enable=on,target=native -kernel firmware.elf -nographic -S -s

clear:
	rm -rf *.o *.elf *.map .gdb_history