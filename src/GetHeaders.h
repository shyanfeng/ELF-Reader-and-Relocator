#ifndef Get_File_Header_H
#define Get_File_Header_H

#include <stdio.h>

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
  uint32_t *sectionAddress;
  uint32_t *targetAddr;
} ElfData;

// File Header
Elf32_Ehdr *getElfHeader(ElfData *dataFromElf);

// Program Header
Elf32_Phdr *getProgramHeaders(ElfData *dataFromElf);

// Section Header
Elf32_Shdr *getSectionHeaders(ElfData *dataFromElf);

// Symbol Table
Elf32_Sym *getSymbolTables(ElfData *dataFromElf);

// Section info and Name
char *getSectionInfoNameUsingIndex(ElfData *dataFromElf, int index);
uint32_t *getSectionInfoUsingIndex(ElfData *dataFromElf, int index);
_Elf32_Shdr *getAllSectionInfo(ElfData *dataFromElf);

// ElfData initialization with file directory
ElfData *openElfFile(char *fileName);

//  Index, Address and Size of section
int getIndexOfSectionByName(ElfData *dataFromElf, char *name);
uint32_t getSectionAddress(ElfData *dataFromElf, int index);
int getSectionSize(ElfData *dataFromElf, int index);

//  Physical and Virtual Address of Program Headers
uint32_t getSectionPhysicalAddress(ElfData *dataFromElf, int index);
uint32_t getSectionVirtualAddress(ElfData *dataFromElf, int index);

//  Status check for Executable, Writeable and Readable
int isSectionExecutable(ElfData *dataFromElf, int index);
int isSectionWriteable(ElfData *dataFromElf, int index);
int isSectionReadable(ElfData *dataFromElf, int index);

//  Entries of Symbol Table
int getSymbolTableEntries(ElfData *elfData);

//  Symbol Table Size and Address from Name
uint32_t getSymbolTableSizeUsingName(ElfData *dataFromElf, char *name);
uint32_t getSymbolTableAddressUsingName(ElfData *dataFromElf, char *name);

//  Name of Symbol Table
char *getSymbolTableNameUsingIndex(ElfData *elfData, int index);

#endif // Get_File_Header_H

