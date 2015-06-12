#ifndef Read_File_H
#define Read_File_H

#include <stdio.h>
#include "unity.h"

#include "elf.h"

typedef struct InStream InStream;

#define moveStart(filePtr, offset) fseek(filePtr, offset, SEEK_SET)
#define readADDR(filePtr, offset, y, return) fseek(filePtr, offset, SEEK_SET); return = fgetc(y->file);
#define moveCurrent(filePtr, offset) fseek(filePtr, offset, SEEK_CUR)
#define moveEnd(filePtr, offset) fseek(filePtr, offset, SEEK_END)


struct InStream{
  FILE *file;
  char *filename;
  uint8_t byteIndex;
  uint32_t bitIndex;
};

InStream *openFile(char *fileDirectory, char *mode);
void *closeFileInTxt(InStream *fileDirectory);
char *readFileInTxt(InStream *getByte, char *buffer);

uint32_t readBit(InStream *getBit);
uint32_t readBits(InStream *getBit, int bitSize);
uint32_t oneByte(InStream *getByte);
uint32_t twoByte(InStream *getByte);
uint32_t fourByte(InStream *getByte);
uint32_t byteSelection(InStream *getByte, int inputByte);

uint32_t movStart(InStream *getFile, long int posStart);
uint32_t movCurrent(InStream *getFile, long int posStart);
uint32_t movEnd(InStream *getFile, long int posEnd);
uint32_t posPtr(InStream *getFile);

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

#endif // Read_File_H
