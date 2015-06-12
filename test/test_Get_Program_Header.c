#include "unity.h"
#include "Get_Program_Header.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}
/*
void test_getProgramHeaderSegmentType(void){
  InStream *myFile;
  Elf32_Phdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getProgramHeaderSegmentType(myFile, &e); // Type
  printf("%x", e.p_type);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e.p_type);
  
  closeFileInTxt(myFile);

}

void test_getProgramHeaderSegmentOffset(void){
  InStream *myFile;
  Elf32_Phdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getProgramHeaderSegmentOffset(myFile, &e); // Type
  printf("%x", e.p_offset);
  
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e.p_offset);
  
  closeFileInTxt(myFile);

}

void test_getProgramHeaderSegmentVirtualAddress(void){
  InStream *myFile;
  Elf32_Phdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getProgramHeaderSegmentVirtualAddress(myFile, &e); // Type
  printf("%x", e.p_vaddr);
  
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e.p_vaddr);
  
  closeFileInTxt(myFile);

}

void test_getProgramHeaderSegmentPhysicalAddress(void){
  InStream *myFile;
  Elf32_Phdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getProgramHeaderSegmentPhysicalAddress(myFile, &e); // Type
  printf("%x", e.p_paddr);
  
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e.p_paddr);
  
  closeFileInTxt(myFile);

}

void test_getProgramHeaderSegmentFileSize(void){
  InStream *myFile;
  Elf32_Phdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getProgramHeaderSegmentFileSize(myFile, &e); // Type
  printf("%x", e.p_filesz);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e.p_filesz);
  
  closeFileInTxt(myFile);

}

void test_getProgramHeaderSegmentSizeInMemory(void){
  InStream *myFile;
  Elf32_Phdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getProgramHeaderSegmentSizeInMemory(myFile, &e); // Type
  printf("%x", e.p_memsz);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e.p_memsz);
  
  closeFileInTxt(myFile);

}

void test_getProgramHeaderSegmentFlag(void){
  InStream *myFile;
  Elf32_Phdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getProgramHeaderSegmentFlag(myFile, &e); // Type
  printf("%x", e.p_flags);
  
  TEST_ASSERT_EQUAL_HEX32(PF_RWE, e.p_flags);
  
  closeFileInTxt(myFile);

}

void test_getProgramHeaderSegmentAlignment(void){
  InStream *myFile;
  Elf32_Phdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getProgramHeaderSegmentAlignment(myFile, &e); // Type
  printf("%x", e.p_align);
  
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e.p_align);
  
  closeFileInTxt(myFile);

}

*/

