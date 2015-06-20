#include "Get_Program_Header.h"
#include "Get_File_Header.h"
#include "Read_File.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

void try1(Data *dataPtr){
  short int value;
  int value2;
  
  char buffer[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  
  dataPtr = (Data *)buffer;
  printf("%x\n", dataPtr);

  printf("second2 = %x\n", dataPtr->second2Byes);
  printf("first4 = %x\n", dataPtr->first4Bytes);
  
}

void try2(Data *dataPtr, InStream *getBit){
  dataPtr = malloc(sizeof(Data));
  printf("%x\n", sizeof(Data));
  short int value;
  int value2;
  
  fread((dataPtr), sizeof(Data), 1, getBit->file);

  printf("data = %x\n", dataPtr->first4Bytes);
}


void loop_for_program_header_size(InStream *getId, Elf32_Phdr **e, Elf32_Ehdr **e2){
  int i;
  int startPosition;
  uint32_t positionOfSectionHeader;
  
  positionOfSectionHeader = (*e2)->e_phoff;
  positionOfSectionHeader = positionOfSectionHeader - (*e2)->e_ehsize;
  
  
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

// without malloc
/*
void read_ELF_Program_Header(InStream *getId, Elf32_Phdr *e){
  int i;
  Elf32_Phdr *a = &e[8];
  

  for(i = 0; i < 3; i++){
    e[i].p_type = byteSelection(getId, 4);
    e[i].p_offset = byteSelection(getId, 4);
    e[i].p_vaddr = byteSelection(getId, 4);
    e[i].p_paddr = byteSelection(getId, 4);
    e[i].p_filesz = byteSelection(getId, 4);
    e[i].p_memsz = byteSelection(getId, 4);
    e[i].p_flags = byteSelection(getId, 4);
    e[i].p_align = byteSelection(getId, 4);
    // printf("Type[%d] = %x\n", i, e[i].p_type);
    // printf("Offset[%d] = %x\n", i, e[i].p_offset);
    // printf("Virtual address[%d] = %x\n", i, e[i].p_vaddr);
    // printf("Physical address[%d] = %x\n", i, e[i].p_paddr);
    // printf("File Size[%d] = %x\n", i, e[i].p_filesz);
    // printf("Memory Size[%d] = %x\n", i, e[i].p_memsz);
    // printf("Flags[%d] = %x\n", i, e[i].p_flags);
    // printf("Align[%d] = %x\n", i, e[i].p_align);
  }
  
}
*/




