#include "unity.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}

/*******************************************************************
 *
 *                      To open the file
 *
 *******************************************************************/
void test_open_exist_file(void){
  InStream *myFile;
  
  myFile = openFile("test/Data/FirstTry.txt", "rb");
  
  TEST_ASSERT_NOT_NULL(myFile->file);
  
  closeFileInTxt(myFile);
}
/*
void test_open_file_not_exist_should_throw_error(void){
  InStream *myFile;
  ErrorCode e;
  
  Try{
    myFile = openFile("test/Data/ABC.txt", "rb");
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST, e);
  }
  
  closeFileInTxt(myFile);
}*/

/*******************************************************************
 *
 *                    Move the file pointer
 *
 *******************************************************************/
void test_inStreamMoveFilePtr(void){
  InStream *myFile;
  long int startPosition;
  long int endPosition;
  int ptrPosition;
  uint32_t getRead;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  startPosition = inStreamMoveFilePtr(myFile, 33216);

  TEST_ASSERT_EQUAL(0, startPosition);
  
  closeFileInTxt(myFile);
}

/*
void test_read_bit_byteIndex_3(void){
  InStream *myFile;
  uint32_t getRead;
  
  myFile->byteIndex = 3;
  myFile->bitIndex = 0;
  
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(1, getRead);
  
  myFile->bitIndex = 1;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(1, getRead);
  
  myFile->bitIndex = 2;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
  myFile->bitIndex = 3;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
}

void test_read_bit_byteIndex_25(void){
  InStream *myFile;
  int getRead;
  
  myFile->byteIndex = 25;
  myFile->bitIndex = 0;
  
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(1, getRead);
  
  myFile->bitIndex = 1;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
  myFile->bitIndex = 2;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
  myFile->bitIndex = 3;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(1, getRead);
  
  myFile->bitIndex = 4;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(1, getRead);  
  
  myFile->bitIndex = 5;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
  myFile->bitIndex = 6;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
  myFile->bitIndex = 7;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
}

void test_read_bit_byteIndex_a(void){
  InStream *myFile;
  int getRead;
     
  myFile->byteIndex = 'a';
  myFile->bitIndex = 0;
  
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(1, getRead);
  
  myFile->bitIndex = 1;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
  myFile->bitIndex = 2;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
  myFile->bitIndex = 3;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
  myFile->bitIndex = 4;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);  
  
  myFile->bitIndex = 5;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(1, getRead);
  
  myFile->bitIndex = 6;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(1, getRead);
  
  myFile->bitIndex = 7;
  getRead = readBit(myFile);
  TEST_ASSERT_EQUAL(0, getRead);
  
}

void test_read_bits_a(void){
  InStream *myFile;
  int getRead;

  myFile = openFile("test/Data/FirstTry.txt", "rb");
  getRead = readBits(myFile, 8);

  TEST_ASSERT_EQUAL_HEX8(0x61, getRead);
  TEST_ASSERT_EQUAL(0b01100001 , getRead);
  
  closeFileInTxt(myFile);
}

void test_read_bits_ABCD(void){
  InStream *myFile;
  int getRead;

  myFile = openFile("test/Data/ThirdTry.txt", "rb");
  getRead = readBits(myFile, 16);

  TEST_ASSERT_EQUAL(0x4241, getRead);
  
  closeFileInTxt(myFile);
}

void test_read_bits_ABCDEFGH(void){
  InStream *myFile;
  int getRead;

  myFile = openFile("test/Data/SixthTry.txt", "rb");
  getRead = readBits(myFile, 32);

  TEST_ASSERT_EQUAL(0x44434241, getRead);
  
  closeFileInTxt(myFile);
}

void test_byteSelection_with_1_byte(void){
  InStream *myFile;
  int getRead;

  myFile = openFile("test/Data/FourthTry.txt", "rb");
  getRead = byteSelection(myFile, 1);
  TEST_ASSERT_EQUAL(0x43, getRead);
  
  closeFileInTxt(myFile);
}

void test_byteSelection_with_2_byte(void){
  InStream *myFile;
  int getRead;

  myFile = openFile("test/Data/ThirdTry.txt", "rb");
  getRead = byteSelection(myFile, 2);
  TEST_ASSERT_EQUAL(0x4241, getRead);
  
  closeFileInTxt(myFile);
}

void test_byteSelection_with_4_byte(void){
  InStream *myFile;
  uint32_t getRead;

  myFile = openFile("test/Data/FifthTry.txt", "rb");
  getRead = byteSelection(myFile, 4);
  TEST_ASSERT_EQUAL(0x44434241, getRead);
  
  closeFileInTxt(myFile);
}

void test_byteSelection_with_invalid_byte_should_throw_error(void){
  InStream *myFile;
  uint32_t getRead;
  ErrorCode e;
  
  Try{
    myFile = openFile("test/Data/FifthTry.txt", "rb");
    getRead = byteSelection(myFile, 8);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_BYTE_SELECTION, e);
  }
  
}

void test_binary_with_1_byte(void){
  InStream *myFile;
  uint32_t getRead;

  myFile = openFile("test/Data/BinaryTry.txt", "rb");
  getRead = byteSelection(myFile, 2);

  TEST_ASSERT_EQUAL(0x677f, getRead);
  
  closeFileInTxt(myFile);
}

void test_byteSelection_2_with_elf_file(void){
  InStream *myFile;
  uint32_t getRead;

  myFile = openFile("test/ELF_File/Test01.elf", "rb");
  getRead = byteSelection(myFile, 2);

  TEST_ASSERT_EQUAL(0x457f, getRead);
  
  closeFileInTxt(myFile);
}

void test_byteSelection_4_with_elf_file(void){
  InStream *myFile;
  uint32_t getRead;

  myFile = openFile("test/ELF_File/Test01.elf", "rb");
  getRead = byteSelection(myFile, 4);
  
  TEST_ASSERT_EQUAL(0x464c457f, getRead);
  
  closeFileInTxt(myFile);
}

void test_byteSelection_2_line_with_elf_file(void){
  InStream *myFile;
  uint32_t getRead;

  myFile = openFile("test/ELF_File/Test01.elf", "rb");
  
  getRead = byteSelection(myFile, 4);
  getRead = byteSelection(myFile, 4);
  getRead = byteSelection(myFile, 4);
  getRead = byteSelection(myFile, 4);
  getRead = byteSelection(myFile, 4);
  getRead = byteSelection(myFile, 4);
  getRead = byteSelection(myFile, 4);
  getRead = byteSelection(myFile, 4);
  
  TEST_ASSERT_EQUAL(0x00000034, getRead);
  
  closeFileInTxt(myFile);
}*/






