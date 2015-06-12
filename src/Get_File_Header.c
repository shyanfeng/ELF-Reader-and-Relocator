#include "Get_File_Header.h"
#include "Read_File.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

void getElfMagic(InStream *getId, int byteSize, Elf32_Ehdr *e){
  int i;
  int startPosition;
  startPosition = movStart(getId, 0);
  for(i = 0; i < byteSize; i++){
    e->e_ident[i] = byteSelection(getId, 1);
  }
}

void getElfClass(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 4);
  e->e_ident[EI_CLASS] = byteSelection(getId, 1);
}

void getElfData(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 5);
  e->e_ident[EI_DATA] = byteSelection(getId, 1);
}

void getElfVERSION(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 6);
  e->e_ident[EI_VERSION] = byteSelection(getId, 1);
}

void getElfOSABI(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 7);
  e->e_ident[EI_OSABI] = byteSelection(getId, 1);
}

void getElfABIVersion(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 8);
  e->e_ident[EI_ABIVERSION] = byteSelection(getId, 1);
}

void getElfPAD(InStream *getId, Elf32_Ehdr *e){
  int i;
  int startPosition;
  startPosition = movCurrent(getId, 9);
  
  for(i = 9; i < 16; i++){
    e->e_ident[i] = byteSelection(getId, 1);
  }
}

void getElfType(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 16);
  e->e_type = byteSelection(getId, 2);
}

void getElfMachine(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 18);
  e->e_machine = byteSelection(getId, 2);
}

void getElfOriVersion(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 20);
  e->e_version = byteSelection(getId, 4);
}

void getElfEntryPointAddress(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 24);
  e->e_entry = byteSelection(getId, 4);
}

void getElfStartOfProgramHeader(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 28);
  e->e_phoff = byteSelection(getId, 4);
}

void getElfStartOfSectionHeader(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 32);
  e->e_shoff = byteSelection(getId, 4);
}

void getElfFlag(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 36);
  e->e_flags = byteSelection(getId, 4);
}

void getElfSizeOfHeader(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 40);
  e->e_ehsize = byteSelection(getId, 2);
}

void getElfProgramHeaderSize(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 42);
  e->e_phentsize = byteSelection(getId, 2);
}

void getElfNumberOfProgramHeader(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 44);
  e->e_phnum = byteSelection(getId, 2);
}

void getElfSectionHeaderSize(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 46);
  e->e_shentsize = byteSelection(getId, 2);
}

void getElfNumberOfSectionHeader(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 48);
  e->e_shnum = byteSelection(getId, 2);
}

void getElfSectionHeaderStringTableIndex(InStream *getId, Elf32_Ehdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 50);
  e->e_shstrndx = byteSelection(getId, 2);
}
