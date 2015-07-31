#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Read_File.h"
#include "elf.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

ElfData *dataFromElf;

void initElfData(){
  dataFromElf = malloc(sizeof(ElfData));
}

/******************************************************************************
 * ELF Header
 *
 *  Operation:
 *          To read the information in the ELF Header
 *  
 *  Data:
 *          Information of the ELF Header allocate in the structure 
 *          of Elf32_Ehdr
 *
 *  Return:
 *          eh
 *          (The structure of Elf32_Ehdr with information of the ELF Header)
 *
 ******************************************************************************/
Elf32_Ehdr *getElfHeader(ElfData *dataFromElf){
  dataFromElf->eh = malloc(sizeof(Elf32_Ehdr));
  
  fread(dataFromElf->eh, sizeof(Elf32_Ehdr), 1, dataFromElf->myFile->file);
  
  return dataFromElf->eh;
}



/******************************************************************************
 * Program Header
 *
 *  Operation:
 *          To read the information in the Program Header with moving the file
 *          pointer with the e_phoff(Program_Header_Offset) in the Elf32_Ehdr
 *  
 *  Data:
 *          Information of the Program Header allocate in the structure 
 *          of Elf32_Phdr
 *
 *  Return:
 *          ph
 *          (The structure of Elf32_Phdr with information of the Program Header)
 *
 ******************************************************************************/
Elf32_Phdr *getProgramHeaders(ElfData *dataFromElf){
  int phSizeToMalloc = sizeof(Elf32_Phdr) * (dataFromElf->eh->e_phnum);
  dataFromElf->ph = malloc(phSizeToMalloc);

  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->eh->e_phoff);
  fread(dataFromElf->ph, phSizeToMalloc, 1, dataFromElf->myFile->file);
  
  return dataFromElf->ph;
}

/******************************************************************************
 * Section Header
 *
 *  Operation:
 *          To read the information in the Section Header with moving the file
 *          pointer with the e_shoff(Section_Header_Offset) in the Elf32_Ehdr
 *  
 *  Data:
 *          Information of the Section Header allocate in the structure 
 *          of Elf32_Shdr
 *
 *  Return:
 *          sh
 *          (The structure of Elf32_Shdr with information of the Section Header)
 *
 ******************************************************************************/
Elf32_Shdr *getSectionHeaders(ElfData *dataFromElf){
  int shSizeToMalloc = sizeof(Elf32_Shdr) * (dataFromElf->eh->e_shnum);
  dataFromElf->sh = malloc(shSizeToMalloc);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->eh->e_shoff);
  fread(dataFromElf->sh, shSizeToMalloc, 1, dataFromElf->myFile->file);
  
  return dataFromElf->sh;
}

/******************************************************************************
 * Symbol Table
 *
 *  Operation:
 *          To read the information in the Symbol Table with moving the file
 *          pointer with the sh_offset(Symbol_Table_Offset) in the Elf32_Shdr
 *  
 *  Data:
 *          Information of the Symbol Table allocate in the structure 
 *          of Elf32_Sym
 *
 *  Return:
 *          st
 *          (The structure of Elf32_Sym with information of the Symbol Table)
 *
 ******************************************************************************/
Elf32_Sym *getSymbolTables(ElfData *dataFromElf){
  int i, totalSymTabByte, entriesOfSymTab;
  int stSizeToMalloc;
  
  for(i = 0; dataFromElf->sh[i].sh_type != SHT_SYMTAB; i++);
  totalSymTabByte = dataFromElf->sh[i+1].sh_offset - dataFromElf->sh[i].sh_offset;
  dataFromElf->st = malloc(totalSymTabByte);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[i].sh_offset);
  fread(dataFromElf->st, totalSymTabByte, 1, dataFromElf->myFile->file);
  
  return dataFromElf->st;
  
}

/******************************************************************************
 * Get Section Info Name Using Index
 *
 *  Operation:
 *          To read the information of name in the section header with moving 
 *          the file pointer with the sh_offset(Symbol_Table_Offset) of String 
 *          Table add with sh[index].sh_name in the Elf32_Shdr. Index is the  
 *          index for Section Header.
 *  
 *  Data:
 *          Information of the Section Name allocate with the size of String 
 *          Table type in the Section Header
 *
 *  Return:
 *          names
 *
 ******************************************************************************/
_Elf32_Shdr *getSectionInfoNameUsingIndex(ElfData *dataFromElf, int index){
  char *names;
  int i;
  
  for(i = 0; dataFromElf->sh[i].sh_type != SHT_STRTAB; i++);
  names= malloc(dataFromElf->sh[i].sh_size);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[i].sh_offset + dataFromElf->sh[index].sh_name);
  fread(names, dataFromElf->sh[i].sh_size, 1, dataFromElf->myFile->file);
  
  return (_Elf32_Shdr*)names;
}

/******************************************************************************
 * Get Section Info Using Index
 *
 *  Operation:
 *          To read the information of section in the section header with moving
 *          the file pointer with the sh[index].sh_offset(Symbol_Table_Offset)  
 *          in the Elf32_Shdr. Index is the index for Section Header.
 *  
 *  Data:
 *          Information of the Section allocate with the size of String 
 *          Table type in the Section Header
 *
 *  Return:
 *          sect
 *
 ******************************************************************************/
_Elf32_Shdr *getSectionInfoUsingIndex(ElfData *dataFromElf, int index){
  uint8_t *sect = malloc(dataFromElf->sh[index].sh_size);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[index].sh_offset);
  fread(sect, dataFromElf->sh[index].sh_size, 1, dataFromElf->myFile->file);

  return (_Elf32_Shdr*)sect;
}

/******************************************************************************
 * Get All Section Info
 *
 *  Operation:
 *          To read the information of section and name in the section header 
 *          with the two function created which are getSectionInfoUsingIndex
 *          and getSectionInfoNameUsingIndex.
 *  
 *  Data:
 *          Information of the Section allocate with the size of _Elf32_Shdr 
 *          multiply with e_shnum in the ELF Header
 *
 *  Return:
 *          getShInfo
 *          (The structure of _Elf32_Shdr)
 *
 ******************************************************************************/
_Elf32_Shdr *getAllSectionInfo(ElfData *dataFromElf){
  dataFromElf->programElf = malloc(dataFromElf->eh->e_shnum * sizeof(_Elf32_Shdr));
  int i;
  
  for(i = 0; i < dataFromElf->eh->e_shnum; i++){
    dataFromElf->programElf[i].section = (char *)getSectionInfoUsingIndex(dataFromElf, i);
    dataFromElf->programElf[i].name = (char *)getSectionInfoNameUsingIndex(dataFromElf, i);
  }
  
  return dataFromElf->programElf;
}

/******************************************************************************
 * Get Section Index From Section Name
 *
 *  Operation:
 *          To get the index of section in section header from the section name
 *  
 *  Data:
 *          The index of section
 *
 *  Return:
 *          index(Name Matched)
 *          -1 (Not Matched)
 *
 ******************************************************************************/
int getIndexOfSectionByName(ElfData *dataFromElf, char *name){
  int index;
  
  dataFromElf->programElf = getAllSectionInfo(dataFromElf); 
  
  for(index = 0; index < dataFromElf->eh->e_shnum; index++){
    if(strcmp(dataFromElf->programElf[index].name , name) == 0){
      return index;
    }
  }
  
  return -1;
}

/******************************************************************************
 * Get Section Address From Section Index
 *
 *  Operation:
 *          To get the address of section in section header from the section 
 *          index
 *  
 *  Data:
 *          The address of section
 *
 *  Return:
 *          secAddress
 *
 ******************************************************************************/
int getSectionAddress(ElfData *dataFromElf, int index){
  int secAddress;
 
  dataFromElf->programElf = getAllSectionInfo(dataFromElf); 
  
  secAddress = (int)dataFromElf->programElf[index].section;
  
  return secAddress;
}

/******************************************************************************
 * Get Section Size From Section Index
 *
 *  Operation:
 *          To get the size of section in section header from the section 
 *          index
 *  
 *  Data:
 *          The size of section
 *
 *  Return:
 *          sectionSize
 *
 ******************************************************************************/
int getSectionSize(ElfData *dataFromElf, int index){
  int sectionSize;
  sectionSize = dataFromElf->sh[index].sh_size;
  
  return sectionSize;
}

// get physical address 
uint32_t getSectionPhysicalAddress(ElfData *dataFromElf, int index){
  uint32_t phyAddr;
  
  phyAddr = dataFromElf->ph[index].p_paddr;
  
  return phyAddr;
}

// get virtual address 
uint32_t getSectionVirtualAddress(ElfData *dataFromElf, int index){
  uint32_t virAddr;
  
  virAddr = dataFromElf->ph[index].p_vaddr;
  
  return virAddr;
}


// int isSectionExecutable(ElfData *dataFromElf, int index){
  // if(dataFromElf->ph[0].p_flags )
// }


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

char *getRelSymbolName(ElfData *dataFromElf, int index){
  int symbolIndex, sectIndex;

  symbolIndex = ELF32_R_SYM(dataFromElf->rel[index].r_info);
  sectIndex = dataFromElf->st[symbolIndex].st_shndx;
  
  dataFromElf->programElf = getSectionInfoNameUsingIndex(dataFromElf, sectIndex);
  
  return (char *)dataFromElf->programElf;
}

uint32_t getRelType(ElfData *dataFromElf, int index){
  int sectType;
  
  sectType = ELF32_R_TYPE(dataFromElf->rel[index].r_info);
  
  return sectType;
}




