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
void getElfHeader(InStream *getId, Elf32_Ehdr **e){
  *e = malloc(sizeof(Elf32_Ehdr));
  int i;
  
  fread((*e), sizeof(Elf32_Ehdr), 1, getId->file);

}

/******************************************************
 *
 *
 *      Program Header
 *
 *
 ******************************************************/
Elf32_Phdr *getProgramHeaders(InStream *getId, Elf32_Ehdr *e2){
  Elf32_Phdr *ph, *temp;
  int i;
  // long int ptrPosition;
  // ptrPosition = posPtr(getId)
  
  for(i = 0; i < ((*e2).e_phnum); i++){
    // printf("ptr position = %d\n", ptrPosition);
    ph = getProgramHeader(getId, e2, i);
    if(i == 0){
      temp = ph;
    }
    // ph += sizeof(Elf32_Phdr)/4;
    // printf("ph = %d\n", ph);
  }
  printProgramHeader(temp);
  return temp;
}
 
Elf32_Phdr *getProgramHeader(InStream *getId, Elf32_Ehdr *e2, int index){
  Elf32_Phdr *e = malloc(sizeof(Elf32_Phdr));
  uint32_t moveFilePtr;
  uint32_t FilePtr;

  moveFilePtr = index * ((*e2).e_phentsize);//index x 32
  FilePtr = ((*e2).e_phoff) + moveFilePtr;//52 + index x 32

  inStreamMoveFilePtr(getId, FilePtr);
  fread(e, sizeof(Elf32_Phdr), 1, getId->file);
  
  return e;
  
}

void printProgramHeader(Elf32_Phdr *ph){
  printf("type = %x\n", ph->p_type);
  printf("offset = %x\n", ph->p_offset);
  printf("p_vaddr = %x\n", ph->p_vaddr);
  printf("p_paddr = %x\n", ph->p_paddr);
  printf("p_filesz = %x\n", ph->p_filesz);
  printf("p_memsz = %x\n", ph->p_memsz);
  printf("p_flags = %x\n", ph->p_flags);
  printf("p_align = %x\n", ph->p_align);
}

 /*
void getProgramHeaders(InStream *getId, Elf32_Phdr **e, Elf32_Ehdr **e2){
  int i;

  inStreamMoveFilePtr(getId, (*e2)->e_phoff);
  
  for(i = 0; i < (*e2)->e_phnum; i++){
    getProgramHeader(getId, e, 0);
    e += sizeof(Elf32_Phdr *)/4;
   }
  
}

void getProgramHeader(InStream *getId, Elf32_Phdr **e, int i){
  *e = malloc(sizeof(Elf32_Phdr));
  Elf32_Phdr *a = &(*e)[8];
  
  fread((*e), sizeof(Elf32_Phdr), 1, getId->file);

}*/

/******************************************************
 *
 *
 *      Section Header
 *
 *
 ******************************************************/

void getSectionHeaders(InStream *getId, Elf32_Shdr **e, Elf32_Ehdr **e2){
  int i;

  inStreamMoveFilePtr(getId, (*e2)->e_shoff);

  for(i = 0; i < (*e2)->e_shnum; i++){
    getSectionHeader(getId, e, 0);
    e += sizeof(Elf32_Shdr *)/4;
   }
  
}


void getSectionHeader(InStream *getId, Elf32_Shdr **e, int i){
  *e = malloc(sizeof(Elf32_Shdr));
  Elf32_Shdr *a = &(*e)[10];
  
  fread((*e), sizeof(Elf32_Shdr), 1, getId->file);

}

/******************************************************
 *
 *
 *      Symbol Table
 *
 *
 ******************************************************/
void getSymbolTables(InStream *getId, Elf32_Sym **e, Elf32_Ehdr **e2){
  int i;
  uint32_t positionOfSectionHeader;
  
  positionOfSectionHeader = (*e2)->e_shnum * (*e2)->e_shentsize;
  positionOfSectionHeader = (*e2)->e_shoff + positionOfSectionHeader;

  inStreamMoveFilePtr(getId, positionOfSectionHeader);

  for(i = 0; i < 290; i++){
    getSymbolTable(getId, e);
    e += sizeof(Elf32_Sym *)/4;
   }
  
}
 
 void getSymbolTable(InStream *getId, Elf32_Sym **e){
  *e = malloc(sizeof(Elf32_Sym));
  Elf32_Sym *a = &(*e)[6];
  
  fread((*e), sizeof(Elf32_Sym), 1, getId->file);

}