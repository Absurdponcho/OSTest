#pragma once
#include "Typedefs.cpp"
#include "TextPrint.cpp"
#include "IO.cpp"

struct IDTDescriptor {
	uint_16 Limit;
	uint_64 Base;	
};

struct IDT_64 {
	uint_16 offset_1;
	uint_16 selector;
	uint_8 ist;
	uint_8 type_attr;
	uint_16 offset_2;
	uint_32 offset_3;
	uint_32 zero;
}__attribute__((packed));

extern IDT_64 _idt_[256];
extern uint_64 irq0;
extern "C" void* InitIDT();
extern IDTDescriptor idtDescriptor;
void InitializeIDT() {
	PrintStrings(3, "Initializing IDT at ", HexToString(&_idt_), "\n\r");
	PrintStrings(3, "irq0 is at ", HexToString(&irq0), "\n\r");
	
	for (int t = 0; t < 256; t++) {
		_idt_[t].zero = 0;
		_idt_[t].offset_1 = (uint_16)(((uint_64)&irq0 & 0x000000000000ffff));
		_idt_[t].offset_2 = (uint_16)(((uint_64)&irq0 & 0x00000000ffff0000) >> 16);
		_idt_[t].offset_3 = (uint_32)(((uint_64)&irq0 & 0xffffffff00000000) >> 32);
		_idt_[t].ist = 0;
		_idt_[t].selector = 0x08;
		_idt_[t].type_attr = 0x8e;

	}
	PrintString( "IDT1:\n\r");
	PrintStrings(2, HexToString(_idt_[1].offset_1), "\n\r");
	PrintStrings(2, HexToString(_idt_[1].selector), "\n\r");
	PrintStrings(2, HexToString(_idt_[1].ist), "\n\r");
	PrintStrings(2, HexToString(_idt_[1].type_attr), "\n\r");
	PrintStrings(2, HexToString(_idt_[1].offset_2), "\n\r");
	PrintStrings(2, HexToString(_idt_[1].offset_3), "\n\r");
	PrintStrings(2, HexToString(_idt_[1].zero), "\n\r");
	idtDescriptor.Base = (uint_64)_idt_;
	
	PrintStrings(3, "IDT Size: ", HexToString(idtDescriptor.Limit), "\n\r");
	PrintStrings(3, "IDT Base: ", HexToString(idtDescriptor.Base), "\n\r");


	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	InitIDT();

	PrintString("IDT has been initialized\n\r");

}

extern "C" void irq0_handler() {
	PrintString(HexToString(inb(0x60)));
	outb(0x20, 0x20);
	outb(0xa0, 0x20);
}
