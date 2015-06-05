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
  // printf("%x\n", sizeof(buffer));

  return buffer;
}

uint32_t readBit(InStream *getBit){
  int returnBit = 0;
  uint32_t mask = 1;
  
  returnBit = (getBit->byteIndex >> getBit->bitIndex) & mask;
  getBit->bitIndex--;
  return returnBit;
  
}

uint32_t readBits(InStream *getBit, int bitSize){
  uint32_t readChar;
  uint32_t returnBits = 0;
  int i;
  getBit->bitIndex = bitSize - 1;
  
  for(i = bitSize; i > 0; i--){
    if(feof(getBit->file) != 1){
      fread(&(getBit->byteIndex), (sizeof(getBit->byteIndex)), 1, getBit->file);
    }
    readChar = readBit(getBit);
    returnBits = returnBits | (readChar << (i - 1));
  }
  return returnBits;
}

uint32_t oneByte(InStream *getByte){
  uint32_t returnBits;

  returnBits = readBits(getByte, 8);
  return returnBits;
}

uint32_t twoByte(InStream *getByte){
  uint32_t returnBits;

  returnBits = readBits(getByte, 16);
  return returnBits;
}

uint32_t fourByte(InStream *getByte){
  uint32_t returnBits;

  returnBits = readBits(getByte, 32);
  return returnBits;
}

uint32_t byteSelection(InStream *getByte, int inputByte){
  uint32_t returnBits;
  
  if(inputByte == 1){
    returnBits = oneByte(getByte);
  }else if(inputByte == 2){
    returnBits = twoByte(getByte);
  }else if(inputByte == 4){
    returnBits = fourByte(getByte);
  }else{
    Throw(ERR_BYTE_SELECTION);
  }
  
  return returnBits;
}


