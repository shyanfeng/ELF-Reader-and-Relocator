#ifndef Get_Section_Header_H
#define Get_Section_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"

void loop_for_section_header_size(InStream *getId, Elf32_Shdr **e, Elf32_Ehdr **e2);
void read_ELF_Section_Header(InStream *getId, Elf32_Shdr **e, int i);

#endif // Get_Section_Header_H