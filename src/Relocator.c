#include "Relocator.h"
#include "GetHeaders.h"
#include "ProgramElf.h"
#include "Read_File.h"
#include "elf.h"
#include <stdio.h>
#include <malloc.h>
// #include "CException.h"
#include "ErrorCode.h"

/******************************************************************************
 * Relocation
 *
 *  Operation:
 *          To read the information in the Relocation by moving the file
 *          pointer to the sh_offset(Relocation_Offset) in the Elf32_Shdr
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *  
 *  Data:
 *          Information of the Relation allocate in the structure 
 *          of Elf32_Sym
 *
 *  Return:
 *          rel
 *          (The structure of Elf32_Rel)
 *
 ******************************************************************************/
Elf32_Rel *getRelocation(ElfData *dataFromElf){
  int i, rel_Entries, sizeToMalloc;
  
  for(i = 0; dataFromElf->sh[i].sh_type != SHT_REL; i++);
  rel_Entries = dataFromElf->sh[i].sh_size / 8;
  sizeToMalloc = rel_Entries * sizeof(Elf32_Rel);
  dataFromElf->rel = malloc(sizeToMalloc);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[i].sh_offset);
  fread(dataFromElf->rel, sizeToMalloc, 1, dataFromElf->myFile->file);

  return dataFromElf->rel;
}

/******************************************************************************
 * Get Relocation Symbol Name
 *
 *  Operation:
 *          To get the symbol name in the Relocation 
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Relocation index)
 *  
 *  Data:
 *          Symbol name of relocation
 *
 *  Return:
 *          dataFromElf->programElf
 *          (symbol name)
 *
 ******************************************************************************/
char *getRelSymbolName(ElfData *dataFromElf, int index){
  int symbolIndex, sectIndex;

  symbolIndex = ELF32_R_SYM(dataFromElf->rel[index].r_info);
  sectIndex = dataFromElf->st[symbolIndex].st_shndx;
  
  dataFromElf->programElf = (_Elf32_Shdr *)getSectionInfoNameUsingIndex(dataFromElf, sectIndex);
  
  return (char *)dataFromElf->programElf;
}

/******************************************************************************
 * Get Relocation Type
 *
 *  Operation:
 *          To get the type in the Relocation 
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Relocation index)
 *  
 *  Data:
 *          Type of relocation
 *
 *  Return:
 *          sectType
 *          (relocation type)
 *
 ******************************************************************************/
uint32_t getRelType(ElfData *dataFromElf, int index){
  int sectType;
  
  sectType = ELF32_R_TYPE(dataFromElf->rel[index].r_info);
  
  return sectType;
}

uint32_t *generateBLInstruction(ElfData *dataFromElf, char *secNameToRel){
  int indexToRel, i;
  uint32_t *instructionOfBL;
  
  indexToRel = getIndexOfSectionByName(dataFromElf, secNameToRel);
  instructionOfBL = getSectionInfoUsingIndex(dataFromElf, indexToRel);
  dataFromElf->sectionAddress = instructionOfBL;
  // dataFromElf->targetAddr = 0x08000000;
  for(i = 0; getRelType(dataFromElf, i) != R_ARM_THM_CALL; i++);
  instructionOfBL = (uint32_t *) (((char *)instructionOfBL) + dataFromElf->rel[i].r_offset);
  instructionOfBL[0] = (instructionOfBL[0] << 16) | (instructionOfBL[0] >> 16);
  
  return instructionOfBL;
}
/*
uint32_t extractBlArguments(ElfData *dataFromElf, BlArguments *blArgs){
  int I1, I2;
  uint32_t addressToCall;
  uint32_t *generateBL = generateBLInstruction(dataFromElf, ".text");

  blArgs->S = (generateBL[0] & 0x04000000) >> 26;
  blArgs->imm10 = (generateBL[0] & 0x03ff0000) >> 16;
  blArgs->J1 = (generateBL[0] & 0x00002000) >> 13;
  blArgs->J2 = (generateBL[0] & 0x00000800) >> 11;
  blArgs->imm11 = (generateBL[0] & 0x000007ff);

  I1 = ~(blArgs->J1 ^ blArgs->S) & 0x1;
  I2 = ~(blArgs->J2 ^ blArgs->S) & 0x1;

  addressToCall = (blArgs->S << 24) | (I1 << 23) | (I2 << 22) | (blArgs->imm10 << 12) | (blArgs->imm11 << 1) | 0;
  addressToCall = addressToCall & 0x01fffffe;
  
  return addressToCall;
}*/




