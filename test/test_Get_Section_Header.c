#include "unity.h"
#include "Get_Section_Header.h"
#include "Get_Program_Header.h"
#include "Get_File_Header.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}

void test_loop_for_program_header_size(void){
  InStream *myFile;
  Elf32_Shdr *e[22];
  Elf32_Ehdr *e2;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  read_ELF_File_Header(myFile, &e2);
  loop_for_section_header_size(myFile, e, &e2);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_NULL, e[0]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000001b, e[1]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[1]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC, e[1]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, e[1]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, e[1]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x000001ac, e[1]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[1]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[1]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e[1]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[1]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000027, e[2]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[2]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_EXECINSTR_ALLOC, e[2]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x080001ac, e[2]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000081ac, e[2]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000eac, e[2]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[2]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[2]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, e[2]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[2]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000002d, e[3]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[3]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC, e[3]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001058, e[3]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009058, e[3]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, e[3]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[3]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[3]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, e[3]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[3]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000035, e[4]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_INIT_ARRAY, e[4]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_SHF_WRITE, e[4]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001060, e[4]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009060, e[4]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, e[4]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[4]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[4]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, e[4]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[4]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000041, e[5]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_FINI_ARRAY, e[5]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_SHF_WRITE, e[5]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001068, e[5]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009068, e[5]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, e[5]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[5]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[5]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, e[5]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[5]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000004d, e[6]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[6]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_SHF_WRITE, e[6]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x20000000, e[6]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010000, e[6]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, e[6]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[6]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[6]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, e[6]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[6]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000004d, e[6]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[6]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_SHF_WRITE, e[6]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x20000000, e[6]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010000, e[6]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, e[6]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[6]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[6]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, e[6]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[6]->sh_entsize);
  
  closeFileInTxt(myFile);
  
}

void test_Section_Header(void){
  InStream *myFile;
  Elf32_Shdr *e[22];
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  startPosition = movCurrent(myFile, 78184);
  read_ELF_Section_Header(myFile, e, 0);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_NULL, e[0]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[0]->sh_entsize);
  
  closeFileInTxt(myFile);
  
}