#include "unity.h"
#include "Get_Program_Header.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}

void test_read_ELF_Program_Header(void){
  InStream *myFile;
  Elf32_Phdr *e;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  read_ELF_Program_Header(myFile, &e);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e->p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e->p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e->p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e->p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e->p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e->p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RWE, e->p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e->p_align);
  
}
