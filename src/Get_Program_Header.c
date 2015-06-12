#include "Get_Program_Header.h"
#include "Read_File.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

void getProgramHeaderSegmentType(InStream *getId, Elf32_Phdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 52);
  e->p_type = byteSelection(getId, 4);
}

void getProgramHeaderSegmentOffset(InStream *getId, Elf32_Phdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 56);
  e->p_offset = byteSelection(getId, 4);
}

void getProgramHeaderSegmentVirtualAddress(InStream *getId, Elf32_Phdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 60);
  e->p_vaddr = byteSelection(getId, 4);
}

void getProgramHeaderSegmentPhysicalAddress(InStream *getId, Elf32_Phdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 64);
  e->p_paddr = byteSelection(getId, 4);
}

void getProgramHeaderSegmentFileSize(InStream *getId, Elf32_Phdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 68);
  e->p_filesz = byteSelection(getId, 4);
}

void getProgramHeaderSegmentSizeInMemory(InStream *getId, Elf32_Phdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 72);
  e->p_memsz = byteSelection(getId, 4);
}

void getProgramHeaderSegmentFlag(InStream *getId, Elf32_Phdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 76);
  e->p_flags = byteSelection(getId, 4);
}

void getProgramHeaderSegmentAlignment(InStream *getId, Elf32_Phdr *e){
  int startPosition;
  startPosition = movCurrent(getId, 80);
  e->p_align = byteSelection(getId, 4);
}





