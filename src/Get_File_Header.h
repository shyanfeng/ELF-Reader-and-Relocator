#ifndef Get_File_Header_H
#define Get_File_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"
// File Header
void getElfHeader(InStream *getId, Elf32_Ehdr **e);

// Program Header
void getProgramHeaders(InStream *getId, Elf32_Phdr **e, Elf32_Ehdr **e2);
void getProgramHeader(InStream *getId, Elf32_Phdr **e, int i);

// Elf32_Phdr *getProgramHeader(InStream *getId, Elf32_Ehdr *e2, int index);
// Elf32_Phdr *getProgramHeaders(InStream *getId, Elf32_Ehdr *e2);

// Section Header
void getSectionHeaders(InStream *getId, Elf32_Shdr **e, Elf32_Ehdr **e2);
void getSectionHeader(InStream *getId, Elf32_Shdr **e, int i);

// Symbol Table
void getSymbolTables(InStream *getId, Elf32_Sym **e, Elf32_Ehdr **e2);
 void getSymbolTable(InStream *getId, Elf32_Sym **e);

#endif // Get_File_Header_H