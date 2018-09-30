BIN_DIR=bin
SRC_DIR=src
TOOLCHAIN=arm-linux-gnueabi

all: prereq $(BIN_DIR)/loader $(BIN_DIR)/blob_1_c.bin $(BIN_DIR)/blob_1_asm.bin

prereq:
	@mkdir -p bin

$(BIN_DIR)/loader:
	$(TOOLCHAIN)-gcc -g $(SRC_DIR)/*.c -o $(BIN_DIR)/loader

$(BIN_DIR)/blob_1_c.bin:
	$(TOOLCHAIN)-gcc $(SRC_DIR)/blob_1_c.c -fpic -shared -ffreestanding -o $(BIN_DIR)/blob_1_c.o
	$(TOOLCHAIN)-objcopy -j .text $(BIN_DIR)/blob_1_c.o $(BIN_DIR)/blob_1_c.bin -O binary

$(BIN_DIR)/blob_1_asm.bin:
	$(TOOLCHAIN)-as $(SRC_DIR)/blob_1_asm.asm -o $(BIN_DIR)/blob_1_asm.o
	$(TOOLCHAIN)-objcopy -j .text $(BIN_DIR)/blob_1_asm.o $(BIN_DIR)/blob_1_asm.bin -O binary
clean:
	rm -rf bin
