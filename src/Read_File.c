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
char *readFileInTxt(InStream *getByte, char *buffer){
  
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

uint32_t movStart(InStream *getFile, long int posStart){
  int startPos;
  
  startPos = fseek(getFile->file, posStart, SEEK_SET);
  
  if(startPos == 1){
    Throw(ERR_RANGE_OFFSET);
  }else{
    return startPos;
  }
  
}

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
  return ptrPosition;

}

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
