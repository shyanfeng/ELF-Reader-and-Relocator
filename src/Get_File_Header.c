#include "Get_File_Header.h"
#include "Read_File.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

void read_ELF_File_Header(InStream *getId, Elf32_Ehdr **e){
  *e = malloc(sizeof(Elf32_Ehdr));
  int i;

  for(i = 0; i < 16; i++){
    (*e)->e_ident[i] =  byteSelection(getId, 1);
  }
  
  (*e)->e_type = byteSelection(getId, 2);
  (*e)->e_machine = byteSelection(getId, 2);
  (*e)->e_version = byteSelection(getId, 4);
  (*e)->e_entry = byteSelection(getId, 4);
  (*e)->e_phoff = byteSelection(getId, 4);
  (*e)->e_shoff = byteSelection(getId, 4);
  (*e)->e_flags = byteSelection(getId, 4);
  (*e)->e_ehsize = byteSelection(getId, 2);
  (*e)->e_phentsize = byteSelection(getId, 2);
  (*e)->e_phnum = byteSelection(getId, 2);
  (*e)->e_shentsize = byteSelection(getId, 2);
  (*e)->e_shnum = byteSelection(getId, 2);
  (*e)->e_shstrndx = byteSelection(getId, 2);


}

