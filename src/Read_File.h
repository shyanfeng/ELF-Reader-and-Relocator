#ifndef Read_File_H
#define Read_File_H

#include <stdio.h>
#include "unity.h"

typedef struct InStream InStream;

struct InStream{
  FILE *file;
  char *filename;
  uint32_t byteIndex;
  uint32_t bitIndex;
};

InStream *openFile(char *fileDirectory, char *mode);
void *closeFileInTxt(InStream *fileDirectory);
char *readFileInTxt(InStream *getByte, char *buffer);
uint32_t readBit(InStream *getBit);
uint32_t readBits(InStream *getBit, int bitSize);

#endif // Read_File_H
