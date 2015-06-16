#ifndef Get_File_Header_H
#define Get_File_Header_H

#include <stdio.h>
#include "unity.h"

#include "Read_File.h"
#include "elf.h"

// Elf32_Ehdr create_ELF_Header();
void read_ELF_File_Header(InStream *getId, Elf32_Ehdr **e);

/*
// File Identifier
void getElfMagic(InStream *getId, int byteSize, Elf32_Ehdr *e);
void getElfClass(InStream *getId, Elf32_Ehdr *e);
void getElfData(InStream *getId, Elf32_Ehdr *e);
void getElfVERSION(InStream *getId, Elf32_Ehdr *e);
void getElfOSABI(InStream *getId, Elf32_Ehdr *e);
void getElfABIVersion(InStream *getId, Elf32_Ehdr *e);
void getElfPAD(InStream *getId, Elf32_Ehdr *e);

// Type
void getElfType(InStream *getId, Elf32_Ehdr *e);

// Machine
void getElfMachine(InStream *getId, Elf32_Ehdr *e);

// Original Version
void getElfOriVersion(InStream *getId, Elf32_Ehdr *e);

// Entry Point Addres
void getElfEntryPointAddress(InStream *getId, Elf32_Ehdr *e);

// Start of Program Header
void getElfStartOfProgramHeader(InStream *getId, Elf32_Ehdr *e);

// Start of Section Header
void getElfStartOfSectionHeader(InStream *getId, Elf32_Ehdr *e);

// Flag
void getElfFlag(InStream *getId, Elf32_Ehdr *e);

// Size of Header
void getElfSizeOfHeader(InStream *getId, Elf32_Ehdr *e);

// Program Header Size
void getElfProgramHeaderSize(InStream *getId, Elf32_Ehdr *e);

// Number of Program Header
void getElfNumberOfProgramHeader(InStream *getId, Elf32_Ehdr *e);

// Size of Section Header
void getElfSectionHeaderSize(InStream *getId, Elf32_Ehdr *e);

// Number of Section Header
void getElfNumberOfSectionHeader(InStream *getId, Elf32_Ehdr *e);

// Section header string table index
void getElfSectionHeaderStringTableIndex(InStream *getId, Elf32_Ehdr *e);
*/
#endif // Get_File_Header_H