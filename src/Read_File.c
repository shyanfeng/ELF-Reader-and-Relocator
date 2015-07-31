#include "Read_File.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"


InStream *openFile(char *fileDirectory, char *mode){
  InStream *myFile = (InStream *)malloc(sizeof(InStream));
  
  myFile->file = fopen(fileDirectory, mode);
  
  if(myFile->file == NULL){
    Throw(ERR_FILE_NOT_EXIST);
  }
  
  myFile->filename = fileDirectory;
  myFile->byteIndex = 0;
  myFile->bitIndex = 8;

  return myFile;

}

void *closeFileInTxt(InStream *fileDirectory){
  fclose(fileDirectory->file);
  free(fileDirectory);
}
/*********************************************
 *    Try out fread
 *********************************************/
/*char *readFileInTxt(InStream *getByte, char *buffer){
  
  fread((buffer), sizeof(buffer), 1, getByte->file);
  // printf("%x\n", sizeof(buffer));

  return buffer;
}

uint32_t readBit(InStream *getBit){
  int returnBit = 0;
  int mask = 1;
  
  returnBit = (getBit->byteIndex >> getBit->bitIndex) & mask;
  
  return returnBit;
}

uint32_t readBits(InStream *getBit, int bitSize){
  uint32_t readChar = 0;
  uint32_t returnBits = 0;
  int i;
  
  for(i = 0; i < bitSize; i++){
    while(getBit->bitIndex == 8){
      if(feof(getBit->file) != 1){
        fread(&(getBit->byteIndex), sizeof(getBit->byteIndex), 1, getBit->file);
      getBit->bitIndex = 0;
      }
    }
    readChar = readBit(getBit);
    returnBits = returnBits | (readChar << i);
    getBit->bitIndex++;
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
*/
uint32_t inStreamMoveFilePtr(InStream *getFile, long int offset){
  int startPos;
  
  startPos = fseek(getFile->file, offset, SEEK_SET);
  
  if(startPos == 1){
    Throw(ERR_RANGE_OFFSET);
  }else{
    return startPos;
  }
  
}
/*
uint32_t movCurrent(InStream *getFile, long int posStart){
  int currentPos;
  
  currentPos = fseek(getFile->file, posStart, SEEK_CUR);
  
  if(currentPos == 1){
    Throw(ERR_RANGE_OFFSET);
  }else{
    return currentPos;
  }
  
}

uint32_t movEnd(InStream *getFile, long int posEnd){
  int endPos;
  long int ptrPosition;
  
  endPos = fseek(getFile->file, posEnd, SEEK_END);
  
  if(endPos == 1){
    Throw(ERR_RANGE_OFFSET);
  }else{
    return endPos;
  }
  
}

uint32_t posPtr(InStream *getFile){
  long int ptrPosition;
  
  ptrPosition = ftell(getFile->file);
  printf("%x\n", ptrPosition);
  return ptrPosition;

}
*/
