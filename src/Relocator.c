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
 *          To generate the BL instruction at the address need to perform 
 *          relocation
 *
 *  Example:
 *          The address need to relocate at address 0x2c with bl instruction
 *          to branch with link to another object file fuction call minus()
 *
 *          2c: f7ff fffe   bl  0<minus>
 *          
 *          So, f7ff fffe is the instruction of BL
 *
 *  Input:
 *          elfData(ElfData structure)
 *          secNameToRel(Section Name to Relocate)
 *  
 *  Data:
 *          The instruction of BL at the address need to relocate
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
 * Extract BL Arguments from function generateBLInstruction
 *
 *  Operation:
 *          To extract the BL arguments to find out the value of S, imm10, J1,
 *          J2, imm11. J1 and S are use to generate the value of I1. J2 and
 *          S are use to generate I2. 
 *
 *  Example:
 *          f7ff fffe is the instruction of bl generated
 *
 *          bit 31 30 29 28 | 27 26 25 24 | 23 22 21 20 | 19 18 17 16 |
 *               1  1  1  1    0  1  1  1    1  1  1  1    1  1  1  1
 *          bit 15 14 13 12 | 11 10  9  8 |  7  6  5  4 |  3  2  1  0 |
 *               1  1  1  1    1  1  1  1    1  1  1  1    1  1  1  0
 *
 *          S will picked from bit 26 (1)
 *          imm10 will picked from bit 16 to 25 (11 1111 1111)
 *          J1 will picked from bit 13 (1)
 *          J2 will picked from bit 11 (1)
 *          imm11 will picked from bit 0 to 10 (111 1111 1110)
 *
 *          After get all the arguements, it will be arranged
 *               S   I1 I2 |------------imm10--------------|   
 *          bit 24 | 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 
 *               1    1  1  1  1    1  1  1  1    1  1  1  1
 *
 *              |-------------imm11---------------|
 *          bit 11 10  9  8 | 7  6  5  4 | 3  2  1  0|
 *               1  1  1  1   1  1  1  1   1  1  0  0
 *          
 *          So, the address is 0x01fffffc (1 1111 1111 1111 1111 1111 1100)
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

/******************************************************************************
 * Extract Address Need to Relocate
 *
 *  Operation:
 *          To extract the address that need to perform relocation with
 *          instruction BL
 *
 *  Example:
 *          2c: f7ff fffe   bl  0 <minus>
 *          30: 6178
 *          
 *          So, the address need to relocate is memory section address + 0x2c
 *          + 0x4 which is the 0x30 because to relocate, it need to move 4  
 *          byte below
 *
 *  Input:
 *          elfData(ElfData structure)
 *  
 *  Data:
 *          The address need to relocate with BL instruction
 *
 *  Return:
 *          instructionOfBL
 *
 ******************************************************************************/
uint32_t extractRelocateAddress(ElfData *elfData){
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
 *          contain the BL instruction that link with elfData2. The function
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

/******************************************************************************
 * Generate Address to Link
 *
 *  Operation:
 *          To generate the address to link. The address to link is to 
 *          generated by function address minus with relocate address
 *
 *  Input:
 *          elfData(ElfData structure)
 *          elfData2(ElfData structure)
 *  
 *  Data:
 *          addrToLink
 *
 *  Return:
 *          addrToLink
 *
 ******************************************************************************/
uint32_t generateAddressToLink(ElfData *elfData, ElfData *elfData2){
  uint32_t addressToCall, funcAddr, addrToLink;
  
  addressToCall = extractRelocateAddress(elfData);
  funcAddr = extractFunctionAddress(elfData, elfData2);

  addrToLink = funcAddr - addressToCall;

  return addrToLink;
}

uint32_t generateRelocateArguments(ElfData *elfData, ElfData *elfData2, BlArguments *blArgs){
  int I1, I2;
  uint32_t addressFromGenerate;
  uint32_t extractBL = generateAddressToLink(elfData, elfData2);

  blArgs->S = (extractBL >>24) & 0x00000001;
  I1 = (extractBL >> 23) & 0x00000001;
  I2 = (extractBL >> 22) & 0x00000001;
  blArgs->J1 = ~(I1 ^ blArgs->S) & 0x1;
  blArgs->J2 = ~(I2 ^ blArgs->S) & 0x1;
  blArgs->imm10 = (extractBL  >> 12) & 0x000003ff;
  blArgs->imm11 = (extractBL >> 1) & 0x000007ff;

  addressFromGenerate = blArgs->imm11 | (blArgs->J2 << 11) | (0x1 << 12) | (blArgs->J1 << 13) | (0x3 << 14) |(blArgs->imm10 << 16) | (blArgs->S << 26) | ((0x1e << 27));
  addressFromGenerate = addressFromGenerate & 0xf7ffffff;
  printf("addressFromGenerate = %x\n", addressFromGenerate);
  return addressFromGenerate;
}

uint32_t *relocateNewInstruction(ElfData *elfData, ElfData *elfData2, BlArguments *blArgs){
  uint32_t *newTextInfo, relocArgs;
  int indexOfSection, i;
  
  indexOfSection = getIndexOfSectionByName(elfData, ".text");
  newTextInfo = getSectionInfoUsingIndex(elfData, indexOfSection);
  relocArgs = generateRelocateArguments(elfData, elfData2, blArgs);
  
  for(i = 0; getRelType(elfData, i) != R_ARM_THM_CALL; i++);
  newTextInfo[elfData->rel[i].r_offset] = relocArgs;
  
  return newTextInfo;
}

uint32_t *newTextSection(ElfData *elfData, ElfData *elfData2, BlArguments *blArgs){
  uint32_t *newText, *textSecToLink, section1Address, section2Address, *endOfSection1Address, endOfSection2Address;
  int indexOfSection1, indexOfSection2, i;
  
  indexOfSection1 = getIndexOfSectionByName(elfData, ".text");
  indexOfSection2 = getIndexOfSectionByName(elfData2, ".text");
  
  newText = relocateNewInstruction(elfData, elfData2, blArgs); 
  elfData->programElf[indexOfSection1].section = (char *)newText;
  printf("newText = %x\n", newText[0x2c]);
  printf("sec = %x\n", elfData->programElf[indexOfSection1].section[0x2c]);
  printf("sec = %x\n", elfData->programElf[indexOfSection1].section[0x2d]);
  printf("sec = %x\n", elfData->programElf[indexOfSection1].section[0x2e]);
  printf("sec = %x\n", elfData->programElf[indexOfSection1].section[0x2f]);
  endOfSection1Address = (uint32_t *)((elfData->programElf[indexOfSection1].section + elfData->sh[indexOfSection1].sh_size) - 1);
  printf("endOfSection1Address = %x\n", endOfSection1Address);
  // endOfSection1Address = (endOfSection1Address + 3) & 0xfffffffc;
  // printf("data = %x\n", elfData->programElf[indexOfSection1].section[0x2c]);
  // elfData->targetAddr = 0x08000000;
  // elfData2->targetAddr = endOfSection1Address + 1;
  
}






