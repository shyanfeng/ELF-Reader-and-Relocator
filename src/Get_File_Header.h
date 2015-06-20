#ifndef Get_File_Header_H
#define Get_File_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"
// File Header
void read_ELF_File_Header(InStream *getId, Elf32_Ehdr **e);

// Program Header
void loop_for_program_header_size(InStream *getId, Elf32_Phdr **e, Elf32_Ehdr **e2);
void read_ELF_Program_Header(InStream *getId, Elf32_Phdr **e, int i);

Elf32_Phdr *getProgramHeader(InStream *getId, int index);

// Section 
void loop_for_section_header_size(InStream *getId, Elf32_Shdr **e, Elf32_Ehdr **e2);
void read_ELF_Section_Header(InStream *getId, Elf32_Shdr **e, int i);

#endif // Get_File_Header_H