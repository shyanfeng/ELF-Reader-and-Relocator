#ifndef Get_Program_Header_H
#define Get_Program_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"

// Type of Program Header
void getProgramHeaderSegmentType(InStream *getId, Elf32_Phdr *e);

// Offset of Program Header
void getProgramHeaderSegmentOffset(InStream *getId, Elf32_Phdr *e);

// Virtual Address of Program Header
void getProgramHeaderSegmentVirtualAddress(InStream *getId, Elf32_Phdr *e);

// Physical Address of Program Header
void getProgramHeaderSegmentPhysicalAddress(InStream *getId, Elf32_Phdr *e);

// Segment File Size of Program Header
void getProgramHeaderSegmentFileSize(InStream *getId, Elf32_Phdr *e);

// Segment Size in Memory
void getProgramHeaderSegmentSizeInMemory(InStream *getId, Elf32_Phdr *e);

// Segment Flag
void getProgramHeaderSegmentFlag(InStream *getId, Elf32_Phdr *e);

// Segmeng Align
void getProgramHeaderSegmentAlignment(InStream *getId, Elf32_Phdr *e);

#endif // Get_Program_Header_H