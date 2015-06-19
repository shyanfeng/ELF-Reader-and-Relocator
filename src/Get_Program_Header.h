#ifndef Get_Program_Header_H
#define Get_Program_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"

// void read_ELF_Program_Header(InStream *getId, Elf32_Phdr *e);
void read_ELF_Program_Header(InStream *getId, Elf32_Phdr **e, int i);
void loop_for_program_header_size(InStream *getId, Elf32_Phdr **e, Elf32_Ehdr **e2);

#endif // Get_Program_Header_H