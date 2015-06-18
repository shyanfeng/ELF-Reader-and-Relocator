#ifndef Get_Program_Header_H
#define Get_Program_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"

// void read_ELF_Program_Header(InStream *getId, Elf32_Phdr *e);
void read_ELF_Program_Header(InStream *getId, Elf32_Phdr **e, int i);
void for_loop(InStream *getId, Elf32_Phdr **e);

#endif // Get_Program_Header_H