#include "unity.h"
#include "Get_File_Header.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}

void test_getElfMagic(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfMagic(myFile, 4, &e); // Magic
  // printf("%x", e.e_ident[0]);
  // printf("%x", e.e_ident[1]);
  // printf("%x", e.e_ident[2]);
  // printf("%x", e.e_ident[3]);
  
  TEST_ASSERT_EQUAL_HEX8(ELFMAG0, e.e_ident[EI_MAG0]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG1, e.e_ident[EI_MAG1]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG2, e.e_ident[EI_MAG2]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG3, e.e_ident[EI_MAG3]);
  
  closeFileInTxt(myFile);
}

void test_getElfClass(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfClass(myFile, &e); // Class
  // printf("%x", e.e_ident[EI_CLASS]);
  
  TEST_ASSERT_EQUAL_HEX8(ELFCLASS32, e.e_ident[EI_CLASS]);
  
  closeFileInTxt(myFile);
}

void test_getElfData(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfData(myFile, &e); // Data
  // printf("%x", e.e_ident[EI_DATA]);
  
  TEST_ASSERT_EQUAL_HEX8(ELFDATA2LSB, e.e_ident[EI_DATA]);
  
  closeFileInTxt(myFile);
}

void test_getElfVERSION(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfVERSION(myFile, &e); // Version
  // printf("%x", e.e_ident[EI_VERSION]);
  
  TEST_ASSERT_EQUAL_HEX8(EV_CURRENT, e.e_ident[EI_VERSION]);
  
  closeFileInTxt(myFile);
}

void test_getElfOSABI(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfOSABI(myFile, &e); // OSABI
  // printf("%x", e.e_ident[EI_OSABI]);
  
  TEST_ASSERT_EQUAL_HEX8(ELFOSABI_SYSV, e.e_ident[EI_OSABI]);

  closeFileInTxt(myFile);
}

void test_getElfABIVersion(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfABIVersion(myFile, &e); // ABIVersion
  // printf("%x", e.e_ident[EI_ABIVERSION]);
  
  TEST_ASSERT_EQUAL_HEX8(0, e.e_ident[EI_ABIVERSION]);

  closeFileInTxt(myFile);
}

void test_getElfPAD(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfPAD(myFile, &e); // Pad
  // printf("%x", e.e_ident[9]);
  // printf("%x", e.e_ident[10]);
  // printf("%x", e.e_ident[11]);
  // printf("%x", e.e_ident[12]);
  // printf("%x", e.e_ident[13]);
  // printf("%x", e.e_ident[14]);
  // printf("%x", e.e_ident[15]);
  
  TEST_ASSERT_EQUAL_HEX8(0, e.e_ident[9]);
  TEST_ASSERT_EQUAL_HEX8(0, e.e_ident[10]);
  TEST_ASSERT_EQUAL_HEX8(0, e.e_ident[11]);
  TEST_ASSERT_EQUAL_HEX8(0, e.e_ident[12]);
  TEST_ASSERT_EQUAL_HEX8(0, e.e_ident[13]);
  TEST_ASSERT_EQUAL_HEX8(0, e.e_ident[14]);
  TEST_ASSERT_EQUAL_HEX8(0, e.e_ident[15]);

  closeFileInTxt(myFile);
}

void test_getElfType(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfType(myFile, &e); // Type
  // printf("%x", e.e_type);

  TEST_ASSERT_EQUAL_HEX16(ET_EXEC, e.e_type);

  closeFileInTxt(myFile);
}

void test_getElfMachine(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfMachine(myFile, &e); // Machine
  // printf("%x", e.e_machine);
  
  TEST_ASSERT_EQUAL_HEX16(0x0028, e.e_machine);

  closeFileInTxt(myFile);
}

void test_getElfOriVersion(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfOriVersion(myFile, &e); // Machine
  // printf("%x", e.e_version);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e.e_version);

  closeFileInTxt(myFile);
}

void test_getElfEntryPointAddress(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfEntryPointAddress(myFile, &e); // Machine
  // printf("%x", e.e_entry);
  
  TEST_ASSERT_EQUAL_HEX32(0x08000fed, e.e_entry);

  closeFileInTxt(myFile);
}

void test_getElfStartOfProgramHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfStartOfProgramHeader(myFile, &e); // Machine
  // printf("%x", e.e_phoff);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000034, e.e_phoff);

  closeFileInTxt(myFile);
}

void test_getElfStartOfSectionHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfStartOfSectionHeader(myFile, &e); // Machine
  // printf("%x", e.e_shoff);
  
  TEST_ASSERT_EQUAL_HEX32(0x00013168, e.e_shoff);

  closeFileInTxt(myFile);
}

void test_getElfFlag(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfFlag(myFile, &e); // Machine
  // printf("%x", e.e_flags);
  
  TEST_ASSERT_EQUAL_HEX32(0x05000202, e.e_flags);

  closeFileInTxt(myFile);
}

void test_getElfSizeOfHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfSizeOfHeader(myFile, &e); // Machine
  // printf("%x", e.e_ehsize);
  
  TEST_ASSERT_EQUAL_HEX16(0x0034, e.e_ehsize);

  closeFileInTxt(myFile);
}

void test_getElfProgramHeaderSize(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfProgramHeaderSize(myFile, &e); // Machine
  // printf("%x", e.e_phentsize);
  
  TEST_ASSERT_EQUAL_HEX16(0x0020, e.e_phentsize);

  closeFileInTxt(myFile);
}

void test_getElfNumberOfProgramHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfNumberOfProgramHeader(myFile, &e); // Machine
  // printf("%x", e.e_phnum);
  
  TEST_ASSERT_EQUAL_HEX16(0x0003, e.e_phnum);

  closeFileInTxt(myFile);
}

void test_getElfSectionHeaderSize(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfSectionHeaderSize(myFile, &e); // Machine
  // printf("%x", e.e_shentsize);
  
  TEST_ASSERT_EQUAL_HEX16(0x0028, e.e_shentsize);

  closeFileInTxt(myFile);
}

void test_getElfNumberOfSectionHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfNumberOfSectionHeader(myFile, &e); // Machine
  // printf("%x", e.e_shnum);
  
  TEST_ASSERT_EQUAL_HEX16(0x0016, e.e_shnum);

  closeFileInTxt(myFile);
}

void test_getElfSectionHeaderStringTableIndex(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfSectionHeaderStringTableIndex(myFile, &e); // Machine
  // printf("%x", e.e_shstrndx);
  
  TEST_ASSERT_EQUAL_HEX16(0x0013, e.e_shstrndx);

  closeFileInTxt(myFile);
}

