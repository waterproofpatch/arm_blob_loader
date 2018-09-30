# Binary blob loader
Memmap's exec memory to load a raw binary into memory and branch to it.

## Prerequisites:

* gnu-arm toolchain for cross compiling
```
sudo apt-get install gcc-arm-none-eabi
sudo apt-get install gcc-arm-linux-gnueabi
```

* qemu-user
```
sudo apt-get install qemu-user
```

* gdb-arm-none-eabi
```
sudo apt-get install gdb-arm-none-eabi
```

## Build:
make

## Run:
### gdb host:
```
qemu-arm -singlestep -g 12345 -L /usr/arm-linux-gnueabi/ bin/loader bin/blob_1_c.bin
```
or
```
qemu-arm -singlestep -g 12345 -L /usr/arm-linux-gnueabi/ bin/loader bin/blob_1_asm.bin
```

### gdb client:
```
arm-none-eabi-gdb
file bin/blob_1_asm.bin
target remote localhost:12345
```

### Note about disassembling the blobs:

When we get to execute_blob, disas stops working like we want (since we're executing outside the scope of anything gdb knows about from loading the file). To deal with this, use ```x/10i $r3``` where r3 contains the fptr to branch to and 10 is the number of instructions to try and decode. We can ```si 1``` at the bx r3 in order to step into the assembly blob.
