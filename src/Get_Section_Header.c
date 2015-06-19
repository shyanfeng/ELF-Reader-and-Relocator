#include "Get_Section_Header.h"
#include "Get_Program_Header.h"
#include "Get_File_Header.h"
#include "Read_File.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

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
  
  (*e)[i].sh_name = byteSelection(getId, 4);
  (*e)[i].sh_type = byteSelection(getId, 4);
  (*e)[i].sh_flags = byteSelection(getId, 4);
  (*e)[i].sh_addr = byteSelection(getId, 4);
  (*e)[i].sh_offset = byteSelection(getId, 4);
  (*e)[i].sh_size = byteSelection(getId, 4);
  (*e)[i].sh_link = byteSelection(getId, 4);
  (*e)[i].sh_info = byteSelection(getId, 4);
  (*e)[i].sh_addralign = byteSelection(getId, 4);
  (*e)[i].sh_entsize = byteSelection(getId, 4);

}