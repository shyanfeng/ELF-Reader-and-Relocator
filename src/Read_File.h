#ifndef Read_File_H
#define Read_File_H

#include <stdio.h>
// #include "unity.h"

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
/*
char *readFileInTxt(InStream *getByte, char *buffer);
uint32_t readBit(InStream *getBit);
uint32_t readBits(InStream *getBit, int bitSize);
uint32_t oneByte(InStream *getByte);
uint32_t twoByte(InStream *getByte);
uint32_t fourByte(InStream *getByte);
uint32_t byteSelection(InStream *getByte, int inputByte);
*/
uint32_t inStreamMoveFilePtr(InStream *myFile, long int offset);
uint32_t posPtr(InStream *myFile);

#endif // Read_File_H
