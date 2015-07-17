#ifndef Get_File_Header_H
#define Get_File_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"
#include "ProgramElf.h"
// File Header
Elf32_Ehdr *getElfHeader(InStream *getId);

// Program Header
Elf32_Phdr *getProgramHeaders(InStream *getId, Elf32_Ehdr *eh);

// Section Header
Elf32_Shdr *getSectionHeaders(InStream *getId, Elf32_Ehdr *eh);

// Symbol Table
Elf32_Sym *getSymbolTables(InStream *myFile, Elf32_Ehdr *eh, Elf32_Shdr *sh);

_Elf32_Shdr *getSectionInfoNameUsingIndex(InStream *myFile, Elf32_Shdr *sh, int index);
_Elf32_Shdr *getSectionInfoUsingIndex(InStream *myFile, Elf32_Shdr *sh, int index);
_Elf32_Shdr *getAllSectionInfo(InStream *myFile, Elf32_Shdr *sh, Elf32_Ehdr *eh);


#endif // Get_File_Header_H

// void printSectionHeaderStringTables(InStream *myFile, Elf32_Ehdr *eh, Elf32_Shdr *sh);
// void printStringTables(InStream *myFile, Elf32_Ehdr *eh, Elf32_Shdr *sh, Elf32_Sym *st);