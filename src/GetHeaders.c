#include "GetHeaders.h"
#include "Read_File.h"
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

void printSectionHeaderStringTables(InStream *myFile, Elf32_Ehdr *eh, Elf32_Shdr *sh){
  char *SectNames;
  int i, j;
  
  for(i = 0; sh[i].sh_type != SHT_STRTAB; i++);
  SectNames = malloc(sh[i].sh_size);
  
  for(j = 0; j < eh->e_shnum; j++){
    inStreamMoveFilePtr(myFile, sh[i].sh_offset + sh[j].sh_name);
    fread(SectNames, sh[i].sh_size, 1, myFile->file);
    printf("%s\n", SectNames);
  }
  
}

void printStringTables(InStream *myFile, Elf32_Ehdr *eh, Elf32_Shdr *sh, Elf32_Sym *st){
  char *SectNames;
  int i, j;
  
  for(i = 0; i < eh->e_shnum - 1; i++);
  SectNames = malloc(sh[i].sh_size);

  for(j = 0; j < 100; j++){
    inStreamMoveFilePtr(myFile, sh[i].sh_offset + st[j].st_name);
    fread(SectNames, sh[i].sh_size, 1, myFile->file);
    printf("%s\n", SectNames);
  }
  
}






