OUTPUT_FORMAT(binary)

ENTRY(_start)

INPUT
(
	ExtendedProgram.o 
	Kernel.o
)

OUTPUT
(
	Kernel.bin
)

SECTIONS
{
	. = 0x8000;
	
	.text : ALIGN(0x1000)
	{
	_text_section = .;
	*(.text)
	_text_section_end = .;

	}

	.data : ALIGN(0x1000)
	{
	_data_section = .;
	*(.data)
	_data_section_end = .;
	}
	
	.rodata : ALIGN(0x1000)
	{
	_rodata_section = .;
	*(.rodata*)
	_rodata_section_end = .;
	}
	
	.bss : ALIGN(0x1000)
	{
	_bss_section = .;
	*(COMMON)
	*(.bss)
	_bss_section_end = .;
	}
}
