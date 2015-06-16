#include "unity.h"
#include "Get_File_Header.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}

void test_read_ELF_File_Header(void){
  InStream *myFile;
  Elf32_Ehdr *e;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  read_ELF_File_Header(myFile, &e);
  
  TEST_ASSERT_EQUAL_HEX8(ELFMAG0, e->e_ident[EI_MAG0]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG1, e->e_ident[EI_MAG1]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG2, e->e_ident[EI_MAG2]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG3, e->e_ident[EI_MAG3]);
  TEST_ASSERT_EQUAL_HEX8(ELFCLASS32, e->e_ident[EI_CLASS]);
  TEST_ASSERT_EQUAL_HEX8(ELFDATA2LSB, e->e_ident[EI_DATA]);
  TEST_ASSERT_EQUAL_HEX8(EV_CURRENT, e->e_ident[EI_VERSION]);
  TEST_ASSERT_EQUAL_HEX8(ELFOSABI_SYSV, e->e_ident[EI_OSABI]);
  TEST_ASSERT_EQUAL_HEX8(0, e->e_ident[EI_ABIVERSION]);
  TEST_ASSERT_EQUAL_HEX8(0, e->e_ident[EI_PAD]);
  TEST_ASSERT_EQUAL_HEX8(0, e->e_ident[10]);
  TEST_ASSERT_EQUAL_HEX8(0, e->e_ident[11]);
  TEST_ASSERT_EQUAL_HEX8(0, e->e_ident[12]);
  TEST_ASSERT_EQUAL_HEX8(0, e->e_ident[13]);
  TEST_ASSERT_EQUAL_HEX8(0, e->e_ident[14]);
  TEST_ASSERT_EQUAL_HEX8(0, e->e_ident[15]);
  
  TEST_ASSERT_EQUAL_HEX16(ET_EXEC, e->e_type);
  TEST_ASSERT_EQUAL_HEX16(0x0028, e->e_machine);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e->e_version);
  TEST_ASSERT_EQUAL_HEX32(0x08000fed, e->e_entry);
  TEST_ASSERT_EQUAL_HEX32(0x00000034, e->e_phoff);
  TEST_ASSERT_EQUAL_HEX32(0x00013168, e->e_shoff);
  TEST_ASSERT_EQUAL_HEX32(0x05000202, e->e_flags);
  TEST_ASSERT_EQUAL_HEX16(0x0034, e->e_ehsize);
  TEST_ASSERT_EQUAL_HEX16(0x0020, e->e_phentsize);
  TEST_ASSERT_EQUAL_HEX16(0x0003, e->e_phnum);
  TEST_ASSERT_EQUAL_HEX16(0x0028, e->e_shentsize);
  TEST_ASSERT_EQUAL_HEX16(0x0016, e->e_shnum);
  TEST_ASSERT_EQUAL_HEX16(0x0013, e->e_shstrndx);
  
  closeFileInTxt(myFile);
}