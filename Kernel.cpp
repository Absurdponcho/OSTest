#include "TextPrint.cpp"
#include "IDT.cpp"
extern uint_64 _text_section ;
extern uint_64 _data_section ;
extern uint_64 _rodata_section ;
extern uint_64 _bss_section ;
extern uint_64 _text_section_end ;
extern uint_64 _data_section_end;
extern uint_64 _rodata_section_end;
extern uint_64 _bss_section_end;
extern "C" void _start() {
	SetCursorPosition(0);

	InitializeIDT();

	return;
}
