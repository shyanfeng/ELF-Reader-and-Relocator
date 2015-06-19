#include "Get_Program_Header.h"
#include "Get_File_Header.h"
#include "Read_File.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

void loop_for_program_header_size(InStream *getId, Elf32_Phdr **e, Elf32_Ehdr **e2){
  int i;
  
  for(i = 0; i < (*e2)->e_phnum; i++){
    read_ELF_Program_Header(getId, e, 0);
    e += sizeof(Elf32_Phdr *)/4;
   }
  
}

void read_ELF_Program_Header(InStream *getId, Elf32_Phdr **e, int i){
  *e = malloc(sizeof(Elf32_Phdr));
  Elf32_Phdr *a = &(*e)[8];
  
  (*e)[i].p_type = byteSelection(getId, 4);
  (*e)[i].p_offset = byteSelection(getId, 4);
  (*e)[i].p_vaddr = byteSelection(getId, 4);
  (*e)[i].p_paddr = byteSelection(getId, 4);
  (*e)[i].p_filesz = byteSelection(getId, 4);
  (*e)[i].p_memsz = byteSelection(getId, 4);
  (*e)[i].p_flags = byteSelection(getId, 4);
  (*e)[i].p_align = byteSelection(getId, 4);

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




