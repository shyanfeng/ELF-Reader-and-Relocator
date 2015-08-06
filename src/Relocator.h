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

#endif // Relocator_H
