#ifndef Get_File_Header_H
#define Get_File_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"

void read_ELF_File_Header(InStream *getId, Elf32_Ehdr **e);

#endif // Get_File_Header_H