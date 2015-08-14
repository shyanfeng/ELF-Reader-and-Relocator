#ifndef Relocator_H
#define Relocator_H

#include <stdio.h>

#include "Read_File.h"
#include "elf.h"
#include "ProgramElf.h"
#include "GetHeaders.h"

typedef struct {
  int S;
  int J1;
  int J2;
  int imm10;
  int imm11;
} BlArguments;

//  Relocation
Elf32_Rel *getRelocation(ElfData *dataFromElf);
char *getRelSymbolName(ElfData *dataFromElf, int index);
uint32_t getRelType(ElfData *dataFromElf, int index);

uint32_t *generateBLInstruction(ElfData *dataFromElf, char *secNameToRel);
uint32_t extractBlArguments(ElfData *dataFromElf, BlArguments *blArgs);

uint32_t extractAddressNeedToRelocate(ElfData *elfData);

uint32_t extractFunctionAddress(ElfData *elfData, ElfData *elfData2);

uint32_t relocateAddress(ElfData *elfData, ElfData *elfData2);

uint32_t generateRelocateArguments(ElfData *elfData, ElfData *elfData2, BlArguments *blArgs);

#endif // Relocator_H
