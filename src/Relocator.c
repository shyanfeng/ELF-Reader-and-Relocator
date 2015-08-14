#include "Relocator.h"
#include "GetHeaders.h"
#include "ProgramElf.h"
#include "Read_File.h"
#include "elf.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

/******************************************************************************
 * Relocation
 *
 *  Operation:
 *          To read the information in the Relocation by moving the file
 *          pointer to the sh_offset(Relocation_Offset) in the Elf32_Shdr
 *
 *  Input:
 *          elfData(ElfData structure)
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
Elf32_Rel *getRelocation(ElfData *elfData){
  int i, rel_Entries, sizeToMalloc;
  
  for(i = 0; elfData->sh[i].sh_type != SHT_REL; i++);
  rel_Entries = elfData->sh[i].sh_size / 8;
  sizeToMalloc = rel_Entries * sizeof(Elf32_Rel);
  elfData->rel = malloc(sizeToMalloc);
  
  inStreamMoveFilePtr(elfData->myFile, elfData->sh[i].sh_offset);
  fread(elfData->rel, sizeToMalloc, 1, elfData->myFile->file);

  return elfData->rel;
}

/******************************************************************************
 * Get Relocation Symbol Name
 *
 *  Operation:
 *          To get the symbol name in the Relocation 
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Relocation index)
 *  
 *  Data:
 *          Symbol name of relocation
 *
 *  Return:
 *          elfData->programElf
 *          (relocation symbol name)
 *
 ******************************************************************************/
char *getRelSymbolName(ElfData *elfData, int index){
  int symbolIndex, sectIndex;

  symbolIndex = ELF32_R_SYM(elfData->rel[index].r_info);
  sectIndex = elfData->st[symbolIndex].st_shndx;
  
  if(elfData->st[symbolIndex].st_shndx == 0){
    elfData->programElf = (_Elf32_Shdr *)getSymbolTableNameUsingIndex(elfData, symbolIndex);
  }else{
    elfData->programElf = (_Elf32_Shdr *)getSectionInfoNameUsingIndex(elfData, sectIndex);
  }
  
  return (char *)elfData->programElf;
}

/******************************************************************************
 * Get Relocation Type
 *
 *  Operation:
 *          To get the type in the Relocation 
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Relocation index)
 *  
 *  Data:
 *          Type of relocation
 *
 *  Return:
 *          symType
 *          (relocation type)
 *
 ******************************************************************************/
uint32_t getRelType(ElfData *elfData, int index){
  int symType;
  
  symType = ELF32_R_TYPE(elfData->rel[index].r_info);
  
  return symType;
}

/******************************************************************************
 * Generate BL Instruction
 *
 *  Operation:
 *          To generate the BL instruction for relocation
 *
 *  Input:
 *          elfData(ElfData structure)
 *          secNameToRel(Section Name to Relocate)
 *  
 *  Data:
 *          The instruction of BL
 *
 *  Return:
 *          instructionOfBL
 *
 ******************************************************************************/
uint32_t *generateBLInstruction(ElfData *elfData, char *secNameToRel){
  int indexToRel, i;
  uint32_t *instructionOfBL;
  
  indexToRel = getIndexOfSectionByName(elfData, secNameToRel);
  instructionOfBL = (uint32_t *)elfData->programElf[indexToRel].section;
  elfData->sectionAddress = instructionOfBL;
  
  for(i = 0; getRelType(elfData, i) != R_ARM_THM_CALL; i++);
  instructionOfBL = (uint32_t *) (((char *)instructionOfBL) + elfData->rel[i].r_offset);
  instructionOfBL[0] = (instructionOfBL[0] << 16) | (instructionOfBL[0] >> 16);

  return instructionOfBL;
}

/******************************************************************************
 * Extract BL Arguments
 *
 *  Operation:
 *          To extract the BL arguments to find out the value of S, imm10, J1,
 *          J2, imm11. J1 and S are use to generate the value of I1. J2 and
 *          S are use to generate I2. 
 *
 *  Input:
 *          elfData(ElfData structure)
 *          blArgs(BlArguments structure)
 *  
 *  Data:
 *          S, imm10, J1, J2, imm11
 *
 *  Return:
 *          addressToCall
 *
 ******************************************************************************/
uint32_t extractBlArguments(ElfData *elfData, BlArguments *blArgs){
  int I1, I2;
  uint32_t addressToCall;
  uint32_t *generateBL = generateBLInstruction(elfData, ".text");
  
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
}

uint32_t extractAddressNeedToRelocate(ElfData *elfData){
  uint32_t addrNeedToRelocate, sectAddr;
  int indexOfText;
  
  indexOfText = getIndexOfSectionByName(elfData, ".text");
  
  sectAddr = getSectionAddress(elfData, indexOfText);
  addrNeedToRelocate = elfData->rel[0].r_offset;
  
  addrNeedToRelocate = (addrNeedToRelocate + sectAddr) + 4;
  
  return addrNeedToRelocate;
}

/******************************************************************************
 * Extract Function Address to link
 *
 *  Operation:
 *          To extract the function address to link. elfData is the memory
 *          contain the BL instruction that link to elfData2. The function
 *          address to extract is from elfData2.
 *
 *  Input:
 *          elfData(ElfData structure)
 *          elfData2(ElfData structure)
 *  
 *  Data:
 *          function address
 *
 *  Return:
 *          funcAddr
 *          (Address of the function in the section)
 *
 ******************************************************************************/
uint32_t extractFunctionAddress(ElfData *elfData, ElfData *elfData2){
  char *symName;
  int i, j, symTabEntries, indexOfText;
  uint32_t funcAddr;
  
  symName = getRelSymbolName(elfData, 0);
  indexOfText = getIndexOfSectionByName(elfData2, ".text");
  symTabEntries = getSymbolTableEntries(elfData);

  for(j = 0; j < symTabEntries; j++){
    if(strcmp(symName, getSymbolTableNameUsingIndex(elfData2, j)) == 0){
      funcAddr = getSectionAddress(elfData2, indexOfText);
      funcAddr = funcAddr + (elfData2->st[j].st_value - 1);
    }
  }
  
  return funcAddr;
}

uint32_t relocateAddress(ElfData *elfData, ElfData *elfData2){
  uint32_t addressToCall, funcAddr, addrToLink;
  
  addressToCall = extractAddressNeedToRelocate(elfData);
  funcAddr = extractFunctionAddress(elfData, elfData2);
  
  addrToLink = funcAddr - addressToCall;
  
  return addrToLink;
}

uint32_t generateRelocateArguments(ElfData *elfData, ElfData *elfData2, BlArguments *blArgs){
  int I1, I2;
  uint32_t addressToExtract;
  uint32_t extractBL = relocateAddress(elfData, elfData2);
  
  blArgs->S = (extractBL & 0x01000000) >> 23;
  // blArgs->imm10 = (extractBL & 0x03ff0000) >> 16;
  // blArgs->J1 = (extractBL & 0x00002000) >> 13;
  // blArgs->J2 = (extractBL & 0x00000800) >> 11;
  // blArgs->imm11 = (extractBL & 0x000007ff);
  printf("S = %d\n",  blArgs->S);
  // I1 = ~(blArgs->J1 ^ blArgs->S) & 0x1;
  // I2 = ~(blArgs->J2 ^ blArgs->S) & 0x1;

  // addressToExtract = (blArgs->S << 24) | (I1 << 23) | (I2 << 22) | (blArgs->imm10 << 12) | (blArgs->imm11 << 1) | 0;
  // addressToExtract = addressToExtract & 0x01fffffe;
  
  return addressToExtract;
}





