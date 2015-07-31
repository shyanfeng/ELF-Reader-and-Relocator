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
Elf32_Shdr *getSectionHeaders(ElfData *dataFromElf);

// Symbol Table
Elf32_Sym *getSymbolTables(ElfData *dataFromElf);

// Section and Name
_Elf32_Shdr *getSectionInfoNameUsingIndex(ElfData *dataFromElf, int index);
_Elf32_Shdr *getSectionInfoUsingIndex(ElfData *dataFromElf, int index);
_Elf32_Shdr *getAllSectionInfo(ElfData *dataFromElf);


int getIndexOfSectionByName(ElfData *dataFromElf, char *name);
int getSectionAddress(ElfData *dataFromElf, int index);
int getSectionSize(ElfData *dataFromElf, int index);

uint32_t getSectionPhysicalAddress(ElfData *dataFromElf, int index);
uint32_t getSectionVirtualAddress(ElfData *dataFromElf, int index);

int isSectionExecutable(ElfData *dataFromElf, int index);

Elf32_Rel *getRelocation(ElfData *dataFromElf);
char *getRelSymbolName(ElfData *dataFromElf, int index);
uint32_t getRelType(ElfData *dataFromElf, int index);

#endif // Get_File_Header_H

