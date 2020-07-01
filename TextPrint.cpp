#pragma once
#include "Typedefs.cpp"
#include "IO.cpp"
#include <stdarg.h>
#define VGA_WIDTH 80
#define VGA_MEMORY (uint_8*)0xb8000

uint_16 CursorPosition;

uint_16 PosFromCoords(uint_8 x, uint_8 y) {
	return y * VGA_WIDTH + x;
}

void SetCursorPosition(uint_16 pos) {
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint_8)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint_8)((pos >> 8) & 0xFF));

	CursorPosition = pos;
}

void PrintString(const char* str) {
	uint_8* charPtr = (uint_8*)str;
	uint_16 index = CursorPosition;
	while (*charPtr != 0) {

		switch (*charPtr)
		{
		case 10:	// new line
			index += 80;
			break;
		case 13:	// new line
			index -= index % 80;
			break;
		default:
			*(VGA_MEMORY + index * 2) = *charPtr;
			index++;
		}
		charPtr++;
	}
	SetCursorPosition(index);
}

void PrintStrings(int params, ...) {
	va_list args;
	va_start(args, params);

	for (int i = 0; i < params; ++i) {
		char* element = va_arg(args, char*);
		PrintString(element);
	}

	va_end(args);
}

char hexToStringOutputT[128];
template <typename T>
const char* HexToString(T value) {
	T* valPtr = &value;
	uint_8* ptr;
	uint_8 temp;
	uint_8 size = (sizeof(T)) * 2 - 1;
	uint_8 i;
	for (i = 0; i < size; i++) {
		ptr = ((uint_8*)valPtr + i);
		temp = ((*ptr & 0xF0) >> 4);
		hexToStringOutputT[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
		temp = ((*ptr & 0x0F));
		hexToStringOutputT[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
	}
	
	hexToStringOutputT[size + 1] = 0;
	return hexToStringOutputT;
}

