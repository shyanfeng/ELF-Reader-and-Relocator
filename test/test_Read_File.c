#include "unity.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}

void test_open_exist_file(void){
  InStream *myFile;
  
  myFile = openFile("test/Data/FirstTry.txt", "rb");
  closeFileInTxt(myFile);
  
  TEST_ASSERT_NOT_NULL(myFile->file);
  
}

void test_open_file_not_exist_should_throw_error(void){
  InStream *myFile;
  ErrorCode e;
  
  Try{
    myFile = openFile("test/Data/ABC.txt", "rb");
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST, e);
  }
  
}

void test_read_file_in_txt(void){
  InStream *myFile;
  char getRead[100];

  myFile = openFile("test/Data/SecondTry.txt", "rb");
  
  readFileInTxt(myFile, getRead);
  printf("Return string : %s\n", &(getRead));
  
  closeFileInTxt(myFile);
  
}


void test_read_bit_byteIndex_3(void){
  InStream *myFile;
  int getRead;
  
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

void test_read_bits(void){
  InStream *myFile;
  int getRead;
  
  myFile = openFile("test/Data/FirstTry.txt", "rb");
  getRead = readBits(myFile, 16);
  printf("%x", getRead);
  
  TEST_ASSERT_EQUAL(0x4241, getRead);
  
  closeFileInTxt(myFile);
}







