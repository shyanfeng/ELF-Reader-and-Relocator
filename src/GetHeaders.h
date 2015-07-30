#ifndef Get_File_Header_H
#define Get_File_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"
#include "ProgramElf.h"
// File Header
Elf32_Ehdr *getElfHeader(InStream *myFile);

// Program Header
Elf32_Phdr *getProgramHeaders(InStream *myFile, Elf32_Ehdr *eh);

// Section Header
Elf32_Shdr *getSectionHeaders(InStream *myFile, Elf32_Ehdr *eh);

// Symbol Table
Elf32_Sym *getSymbolTables(InStream *myFile, Elf32_Ehdr *eh, Elf32_Shdr *sh);

// Section and Name
_Elf32_Shdr *getSectionInfoNameUsingIndex(InStream *myFile, Elf32_Shdr *sh, int index);
_Elf32_Shdr *getSectionInfoUsingIndex(InStream *myFile, Elf32_Shdr *sh, int index);
_Elf32_Shdr *getAllSectionInfo(InStream *myFile, Elf32_Shdr *sh, Elf32_Ehdr *eh);


int getIndexOfSectionByName(InStream *myFile, Elf32_Shdr *sh, Elf32_Ehdr *eh, char *name);
int getSectionAddress(InStream *myFile, Elf32_Shdr *sh, int index);
int getSectionSize(InStream *myFile, Elf32_Shdr *sh, int index);
uint32_t *getSectionData(InStream *myFile, Elf32_Shdr *sh, int index);

Elf32_Rel *getRelocation(InStream *myFile, Elf32_Shdr *sh);
char *getRelSymbolName(InStream *myFile, Elf32_Shdr *sh, Elf32_Rel *getRel, Elf32_Sym *st, int index);
uint32_t getRelType(InStream *myFile, Elf32_Rel *getRel, int index);
uint32_t getRelSymValue(InStream *myFile, Elf32_Rel *getRel, Elf32_Sym *st, int index);

#endif // Get_File_Header_H

