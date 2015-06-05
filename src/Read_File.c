#include "Read_File.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"
// #include "elf.h"

InStream *openFile(char *fileDirectory, char *mode){
  InStream *myFile = (InStream *)malloc(sizeof(InStream));
  
  myFile->file = fopen(fileDirectory, mode);
  
  if(myFile->file == NULL){
    Throw(ERR_FILE_NOT_EXIST);
  }
  
  myFile->filename = fileDirectory;
  myFile->byteIndex = 0;
  myFile->bitIndex = 0;

  return myFile;

}

void *closeFileInTxt(InStream *fileDirectory){
  fclose(fileDirectory->file);
  free(fileDirectory);
}
/*********************************************
 *    Try out fread
 *********************************************/
char *readFileInTxt(InStream *getByte, char *buffer){
  
  fread((buffer), sizeof(buffer), 1, getByte->file);
  //printf("%s\n", buffer);

  return buffer;
}

uint32_t readBit(InStream *getBit){
  int returnBit = 0;
  uint32_t mask = 1;
  
  returnBit = (getBit->byteIndex >> getBit->bitIndex) & mask;
  getBit->bitIndex--;
// printf("%x\n", returnBit);
  return returnBit;
  
}

uint32_t readBits(InStream *getBit, int bitSize){
  uint32_t readChar;
  uint32_t returnBits = 0;
  int i;
  getBit->bitIndex = bitSize - 1;
  
  for(i = bitSize; i > 0; i--){
    if(feof(getBit->file) != 1){
      fread(&(getBit->byteIndex), 1, 1, getBit->file);
    }
    // printf("fread: %x\n", getBit->byteIndex);
    readChar = readBit(getBit);
    returnBits = returnBits | (readChar << (i - 1));
    // printf("read char: %x\n", readChar);
    // printf("return bits: %x\n", returnBits);
  }
    // printf("returnBit %x\n", returnBits);
  // returnBits = returnBits & 0xffff;
  return returnBits;
}




