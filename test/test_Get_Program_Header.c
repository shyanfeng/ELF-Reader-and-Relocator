#include "unity.h"
#include "Get_Program_Header.h"
#include "Get_File_Header.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}

void test_loop_for_program_header_size(void){
  InStream *myFile;
  Elf32_Phdr *e[3];
  Elf32_Ehdr *e2;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  read_ELF_File_Header(myFile, &e2);
  loop_for_program_header_size(myFile, e, &e2);

  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e[0]->p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[0]->p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[0]->p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e[0]->p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e[0]->p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e[0]->p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e[0]->p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RWX, e[0]->p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[0]->p_align);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e[1]->p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010000, e[1]->p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000000, e[1]->p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x0800106c, e[1]->p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, e[1]->p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, e[1]->p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, e[1]->p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[1]->p_align);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e[2]->p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, e[2]->p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, e[2]->p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, e[2]->p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[2]->p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000648, e[2]->p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, e[2]->p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[2]->p_align);
  
  closeFileInTxt(myFile);
}

void test_read_ELF_Program_Header(void){
  InStream *myFile;
  Elf32_Phdr *e[3];
  int startPosition;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  startPosition = movCurrent(myFile, 52);
  read_ELF_Program_Header(myFile, e, 0);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e[0]->p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[0]->p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e[0]->p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e[0]->p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e[0]->p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e[0]->p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RWX, e[0]->p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[0]->p_align);
  
  closeFileInTxt(myFile);
}

// without malloc
/*
void test_read_ELF_Program_Header(void){
  InStream *myFile;
  Elf32_Phdr e[3];
  int startPosition;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  startPosition = movCurrent(myFile, 52);
  read_ELF_Program_Header(myFile, e);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e[0].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[0].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e[0].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e[0].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e[0].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, e[0].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RWX, e[0].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[0].p_align);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e[1].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010000, e[1].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000000, e[1].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x0800106c, e[1].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, e[1].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, e[1].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, e[1].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[1].p_align);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e[2].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, e[2].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, e[2].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, e[2].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[2].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000648, e[2].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, e[2].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[2].p_align);
  
  closeFileInTxt(myFile);
  
}*/

