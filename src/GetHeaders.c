#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Read_File.h"
#include "elf.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"
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
Elf32_Ehdr *getElfHeader(InStream *myFile){
  Elf32_Ehdr *eh = malloc(sizeof(Elf32_Ehdr));
  
  fread(eh, sizeof(Elf32_Ehdr), 1, myFile->file);
  
  return eh;
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
Elf32_Phdr *getProgramHeaders(InStream *myFile, Elf32_Ehdr *eh){
  int phSizeToMalloc = sizeof(Elf32_Phdr) * (eh->e_phnum);
  Elf32_Phdr *ph = malloc(phSizeToMalloc);

  inStreamMoveFilePtr(myFile, eh->e_phoff);
  fread(ph, phSizeToMalloc, 1, myFile->file);
  
  return ph;
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
Elf32_Shdr *getSectionHeaders(InStream *myFile, Elf32_Ehdr *eh){
  int shSizeToMalloc = sizeof(Elf32_Shdr) * (eh->e_shnum);
  Elf32_Shdr *sh = malloc(shSizeToMalloc);
  
  inStreamMoveFilePtr(myFile, eh->e_shoff);
  fread(sh, shSizeToMalloc, 1, myFile->file);
  
  return sh;
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
Elf32_Sym *getSymbolTables(InStream *myFile, Elf32_Ehdr *eh, Elf32_Shdr *sh){
  int i, totalSymTabByte, entriesOfSymTab;
  int stSizeToMalloc;
  
  for(i = 0; sh[i].sh_type != SHT_SYMTAB; i++);
  totalSymTabByte = sh[i+1].sh_offset - sh[i].sh_offset;
  Elf32_Sym *st = malloc(totalSymTabByte);
  
  inStreamMoveFilePtr(myFile, sh[i].sh_offset);
  fread(st, totalSymTabByte, 1, myFile->file);
  
  return st;
  
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
_Elf32_Shdr *getSectionInfoNameUsingIndex(InStream *myFile, Elf32_Shdr *sh, int index){
  char *names;
  int i;
  
  for(i = 0; sh[i].sh_type != SHT_STRTAB; i++);
  names= malloc(sh[i].sh_size);
  
  inStreamMoveFilePtr(myFile, sh[i].sh_offset + sh[index].sh_name);
  fread(names, sh[i].sh_size, 1, myFile->file);
  
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
_Elf32_Shdr *getSectionInfoUsingIndex(InStream *myFile, Elf32_Shdr *sh, int index){
  _Elf32_Shdr *getShInfoUsingIndex, *getShInfoName;
  uint8_t *sect = malloc(sh[index].sh_size);
  
  inStreamMoveFilePtr(myFile, sh[index].sh_offset);
  fread(sect, sh[index].sh_size, 1, myFile->file);

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
_Elf32_Shdr *getAllSectionInfo(InStream *myFile, Elf32_Shdr *sh, Elf32_Ehdr *eh){
  _Elf32_Shdr *getShInfo = malloc(eh->e_shnum * sizeof(_Elf32_Shdr));
  int i, j;
  
  for(i = 0; i < eh->e_shnum; i++){
    getShInfo[i].section = (char *)getSectionInfoUsingIndex(myFile, sh, i);
    getShInfo[i].name = (char *)getSectionInfoNameUsingIndex(myFile, sh, i);
  }
  
  return getShInfo;
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
int getIndexOfSectionByName(InStream *myFile, Elf32_Shdr *sh, Elf32_Ehdr *eh, char *name){
  _Elf32_Shdr *getShIndexByName;
  int index;
  
  getShIndexByName = getAllSectionInfo(myFile, sh, eh); 
  
  for(index = 0; index < eh->e_shnum; index++){
    if(strcmp(getShIndexByName[index].name , name) == 0){
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
int getSectionAddress(InStream *myFile, Elf32_Shdr *sh, int index){
  int secAddress;
  secAddress = sh[index].sh_addr;
  
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
int getSectionSize(InStream *myFile, Elf32_Shdr *sh, int index){
  int sectionSize;
  sectionSize = sh[index].sh_size;
  
  return sectionSize;
}

Elf32_Rel *getRelocation(InStream *myFile, Elf32_Shdr *sh){
  int i, rel_Entries, sizeToMalloc;
  
  for(i = 0; sh[i].sh_type != SHT_REL; i++);
  rel_Entries = sh[i].sh_size / 8;
  sizeToMalloc = rel_Entries * sizeof(Elf32_Rel);
  Elf32_Rel *getRel = malloc(sizeToMalloc);
  
  inStreamMoveFilePtr(myFile, sh[i].sh_offset);
  fread(getRel, sizeToMalloc, 1, myFile->file);

  return getRel;
}

char *getRelSymbolName(InStream *myFile, Elf32_Shdr *sh, Elf32_Rel *getRel, Elf32_Sym *getSymTab, int index){
  int symbolIndex, sectIndex;

  symbolIndex = ELF32_R_SYM(getRel[index].r_info);
  sectIndex = getSymTab[symbolIndex].st_shndx;
  
  _Elf32_Shdr *getSectName = getSectionInfoNameUsingIndex(myFile, sh, sectIndex);
  
  return (char *)getSectName;
}

int getRelType(InStream *myFile, Elf32_Shdr *sh, Elf32_Rel *getRel, int index){
  int sectType;
  
  sectType = ELF32_R_TYPE(getRel[index].r_info);
  
  return sectType;
}

uint32_t *getSectionData(InStream *myFile, Elf32_Shdr *sh, int index){
  int *data = malloc(sh[index].sh_size);
  
  inStreamMoveFilePtr(myFile, sh[index].sh_offset);
  fread(data, sh[index].sh_size, 1, myFile->file);

  return data;
}





