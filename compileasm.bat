nasm bootloader.asm -f bin -o bootloader.bin

nasm ExtendedProgram.asm -f elf64 -o ExtendedProgram.o

x86_64-elf-g++ -ffreestanding -mno-red-zone -m64 -c "Kernel.cpp" -o "Kernel.o"

custom-ld -T"link.ld"

copy /b bootloader.bin+kernel.bin bootloader.flp

pause