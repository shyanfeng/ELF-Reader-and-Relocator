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
void read_ELF_File_Header(InStream *getId, Elf32_Ehdr **e){
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
Elf32_Phdr *getProgramHeader(InStream *getId, int index){
  Elf32_Phdr *e = malloc(sizeof(Elf32_Phdr));
  uint32_t moveFilePtr;
  moveFilePtr = index * 32;
  moveFilePtr = 52 + index;
  
  inStreamMoveFilePtr(getId, moveFilePtr);
  fread(e, sizeof(Elf32_Phdr), 1, getId->file);
  
}
 
void loop_for_program_header_size(InStream *getId, Elf32_Phdr **e, Elf32_Ehdr **e2){
  int i;
  int startPosition;

  
  inStreamMoveFilePtr(getId, (*e2)->e_phoff);
  
  for(i = 0; i < (*e2)->e_phnum; i++){
    read_ELF_Program_Header(getId, e, 0);
    e += sizeof(Elf32_Phdr *)/4;
   }
  
}

void read_ELF_Program_Header(InStream *getId, Elf32_Phdr **e, int i){
  *e = malloc(sizeof(Elf32_Phdr));
  Elf32_Phdr *a = &(*e)[8];
  
  fread((*e), sizeof(Elf32_Phdr), 1, getId->file);

}

/******************************************************
 *
 *
 *      Section Header
 *
 *
 ******************************************************/

void loop_for_section_header_size(InStream *getId, Elf32_Shdr **e, Elf32_Ehdr **e2){
  int i;
  int startPosition;
  uint32_t positionOfSectionHeader;
  
  positionOfSectionHeader = (*e2)->e_shoff;
  positionOfSectionHeader = positionOfSectionHeader - (*e2)->e_ehsize;

  startPosition = movCurrent(getId, positionOfSectionHeader);

  for(i = 0; i < (*e2)->e_shnum; i++){
    read_ELF_Section_Header(getId, e, 0);
    e += sizeof(Elf32_Shdr *)/4;
   }
  
}


void read_ELF_Section_Header(InStream *getId, Elf32_Shdr **e, int i){
  *e = malloc(sizeof(Elf32_Shdr));
  Elf32_Shdr *a = &(*e)[10];
  
  fread((*e), sizeof(Elf32_Shdr), 1, getId->file);

}

