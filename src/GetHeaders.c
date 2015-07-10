#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Read_File.h"
#include "elf.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"
/******************************************************
 *
 *
 *      File Header
 *
 *
 ******************************************************/
Elf32_Ehdr *getElfHeader(InStream *myFile){
  Elf32_Ehdr *eh = malloc(sizeof(Elf32_Ehdr));
  
  fread(eh, sizeof(Elf32_Ehdr), 1, myFile->file);
  
  return eh;
}

/******************************************************
 *
 *
 *      Program Header
 *
 *
 ******************************************************/
Elf32_Phdr *getProgramHeaders(InStream *myFile, Elf32_Ehdr *eh){
  int phSizeToMalloc = sizeof(Elf32_Phdr) * (eh->e_phnum);
  Elf32_Phdr *ph = malloc(phSizeToMalloc);

  inStreamMoveFilePtr(myFile, eh->e_phoff);
  fread(ph, phSizeToMalloc, 1, myFile->file);
  
  return ph;
}

/******************************************************
 *
 *
 *      Section Header
 *
 *
 ******************************************************/
Elf32_Shdr *getSectionHeaders(InStream *myFile, Elf32_Ehdr *eh){
  int shSizeToMalloc = sizeof(Elf32_Shdr) * (eh->e_shnum);
  Elf32_Shdr *sh = malloc(shSizeToMalloc);
  
  inStreamMoveFilePtr(myFile, eh->e_shoff);
  fread(sh, shSizeToMalloc, 1, myFile->file);
  
  return sh;
}

/******************************************************
 *
 *
 *      Symbol Table
 *
 *
 ******************************************************/
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

/********************************************************
 *
 *  Read the section name
 *
 *******************************************************/
_Elf32_Shdr *getSectionInfoName(InStream *myFile, Elf32_Shdr *sh, int index){
  char *names;
  int i;
  _Elf32_Shdr *getShInfo = malloc(sizeof(_Elf32_Shdr));
  
  for(i = 0; sh[i].sh_type != SHT_STRTAB; i++);
  names= malloc(sh[i].sh_size);
  
  inStreamMoveFilePtr(myFile, sh[i].sh_offset + sh[index].sh_name);
  fread(names, sh[i].sh_size, 1, myFile->file);
  getShInfo->name = names;
  
  return getShInfo;
}

/********************************************************
 *
 *  Read the section from the offset and size with index 
 *  and name from getSectionInfoName()
 *
 *******************************************************/
_Elf32_Shdr *getSectionInfoUsingIndex(InStream *myFile, Elf32_Shdr *sh, int index){
  _Elf32_Shdr *getShInfo, *getShInfoName;
  uint8_t *sect = malloc(sh[index].sh_size);
  
  inStreamMoveFilePtr(myFile, sh[index].sh_offset);
  fread(sect, sh[index].sh_size, 1, myFile->file);
  getShInfo->section = (char *)&sh[index].sh_offset;
  
  getShInfoName = getSectionInfoName(myFile, sh, index);
  getShInfo->name = getShInfoName->name;
  
  return getShInfo;
}












