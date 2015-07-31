#ifndef Get_File_Header_H
#define Get_File_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"
#include "ProgramElf.h"

typedef struct {
  InStream *myFile;
  Elf32_Ehdr *eh;
  Elf32_Shdr *sh;
  Elf32_Phdr *ph;
  _Elf32_Shdr *programElf;
  Elf32_Sym *st;
  Elf32_Rel *rel;
} ElfData;

extern ElfData *dataFromElf;
void initElfData();

// File Header
Elf32_Ehdr *getElfHeader(ElfData *dataFromElf);

// Program Header
Elf32_Phdr *getProgramHeaders(ElfData *dataFromElf);

// Section Header
Elf32_Shdr *getSectionHeaders(InStream *myFile, Elf32_Ehdr *eh);

// Symbol Table
Elf32_Sym *getSymbolTables(InStream *myFile, Elf32_Ehdr *eh, Elf32_Shdr *sh);

// Section and Name
_Elf32_Shdr *getSectionInfoNameUsingIndex(InStream *myFile, Elf32_Shdr *sh, int index);
_Elf32_Shdr *getSectionInfoUsingIndex(InStream *myFile, Elf32_Shdr *sh, int index);
_Elf32_Shdr *getAllSectionInfo(InStream *myFile, Elf32_Shdr *sh, Elf32_Ehdr *eh);


int getIndexOfSectionByName(InStream *myFile, Elf32_Shdr *sh, Elf32_Ehdr *eh, char *name);
int getSectionAddress(ElfData *dataFromElf, int index);
int getSectionSize(ElfData *dataFromElf, int index);
// uint32_t *getSectionData(InStream *myFile, Elf32_Shdr *sh, int index);

Elf32_Rel *getRelocation(ElfData *dataFromElf);
char *getRelSymbolName(ElfData *dataFromElf, int index);
uint32_t getRelType(ElfData *dataFromElf, int index);

#endif // Get_File_Header_H

