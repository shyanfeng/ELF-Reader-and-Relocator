#include "Get_File_Header.h"
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
/*void getSymbolTables(InStream *myFile, Elf32_Sym **e, Elf32_Ehdr **e2){
  int i;
  uint32_t positionOfSectionHeader;
  
  positionOfSectionHeader = (*e2)->e_shnum * (*e2)->e_shentsize;
  positionOfSectionHeader = (*e2)->e_shoff + positionOfSectionHeader;

  inStreamMoveFilePtr(myFile, positionOfSectionHeader);

  for(i = 0; i < 290; i++){
    getSymbolTable(myFile, e);
    e += sizeof(Elf32_Sym *)/4;
   }
  
}
 
void getSymbolTable(InStream *myFile, Elf32_Sym **e){
  *e = malloc(sizeof(Elf32_Sym));
  Elf32_Sym *a = &(*e)[6];
  
  fread((*e), sizeof(Elf32_Sym), 1, myFile->file);

}*/