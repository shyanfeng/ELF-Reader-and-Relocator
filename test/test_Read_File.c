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
  // printf("Return string : %s\n", &(getRead));
  
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
  
  // while(feof(myFile->file) != 1){
    // getRead = byteSelection(myFile, 1);
  // }
  
  // TEST_ASSERT_EQUAL(0x464c457f, getRead);
  // TEST_ASSERT_EQUAL(0x00010101, getRead);
  // TEST_ASSERT_EQUAL(0x00000000, getRead);
  // TEST_ASSERT_EQUAL(0x00000000, getRead);
  // TEST_ASSERT_EQUAL(0x00280002, getRead);
  // TEST_ASSERT_EQUAL(0x00000001, getRead);
  // TEST_ASSERT_EQUAL(0x08000fed, getRead);
  
  TEST_ASSERT_EQUAL(0x00000034, getRead);
  
  closeFileInTxt(myFile);
}

void test_mov_start_elf_file(void){
  InStream *myFile;
  long int startPosition;
  long int endPosition;
  int ptrPosition;
  uint32_t getRead;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  startPosition = movStart(myFile, 33216);
  getRead = byteSelection(myFile, 4);
  // printf("startPosition : %d, read = %x\n", startPosition, getRead);
  
  getRead = byteSelection(myFile, 4);
  // printf("read = %x\n", getRead);
  
  getRead = byteSelection(myFile, 4);
  // printf("read = %x\n", getRead);
  
  getRead = byteSelection(myFile, 4);
  // printf("read = %x\n", getRead);
  
  endPosition = moveEnd(myFile->file, -54014);
  getRead = byteSelection(myFile, 1);
  // printf("position: %d, getRead: %x\n", endPosition, getRead);	
  TEST_ASSERT_EQUAL(0, endPosition);
  
  closeFileInTxt(myFile);
}

void test_seek_file(void){
  InStream *myFile;
  int pos;
  char ret;
  long int currentPosition;
  long int endPosition;
  uint32_t getRead;

  myFile = openFile("test/Data/Message.txt", "rb+");
  pos = moveStart(myFile->file, 8);
  currentPosition = ftell(myFile->file);
  getRead = byteSelection(myFile, 1);
  // printf("ptr : %d", currentPosition);
  TEST_ASSERT_EQUAL(0, pos);
  
  pos = moveEnd(myFile->file, -1);
  TEST_ASSERT_EQUAL(0, pos);
  
  closeFileInTxt(myFile);
}

void test_getElfMagic(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  int curPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfMagic(myFile, 4, &e); // Magic
  printf("%x", e.e_ident[0]);
  printf("%x", e.e_ident[1]);
  printf("%x", e.e_ident[2]);
  printf("%x", e.e_ident[3]);
  
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
  printf("%x", e.e_ident[EI_CLASS]);
  
  TEST_ASSERT_EQUAL_HEX8(ELFCLASS32, e.e_ident[EI_CLASS]);
  
  closeFileInTxt(myFile);
}

void test_getElfData(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfData(myFile, &e); // Data
  printf("%x", e.e_ident[EI_DATA]);
  
  TEST_ASSERT_EQUAL_HEX8(ELFDATA2LSB, e.e_ident[EI_DATA]);
  
  closeFileInTxt(myFile);
}

void test_getElfVERSION(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfVERSION(myFile, &e); // Version
  printf("%x", e.e_ident[EI_VERSION]);
  
  TEST_ASSERT_EQUAL_HEX8(EV_CURRENT, e.e_ident[EI_VERSION]);
  
  closeFileInTxt(myFile);
}

void test_getElfOSABI(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfOSABI(myFile, &e); // OSABI
  printf("%x", e.e_ident[EI_OSABI]);
  
  TEST_ASSERT_EQUAL_HEX8(ELFOSABI_SYSV, e.e_ident[EI_OSABI]);

  closeFileInTxt(myFile);
}

void test_getElfABIVersion(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfABIVersion(myFile, &e); // ABIVersion
  printf("%x", e.e_ident[EI_ABIVERSION]);
  
  TEST_ASSERT_EQUAL_HEX8(0, e.e_ident[EI_ABIVERSION]);

  closeFileInTxt(myFile);
}

void test_getElfPAD(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfPAD(myFile, &e); // Pad
  printf("%x", e.e_ident[9]);
  printf("%x", e.e_ident[10]);
  printf("%x", e.e_ident[11]);
  printf("%x", e.e_ident[12]);
  printf("%x", e.e_ident[13]);
  printf("%x", e.e_ident[14]);
  printf("%x", e.e_ident[15]);
  
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
  printf("%x", e.e_type);

  
  TEST_ASSERT_EQUAL_HEX16(ET_EXEC, e.e_type);


  closeFileInTxt(myFile);
}

void test_getElfMachine(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfMachine(myFile, &e); // Machine
  printf("%x", e.e_machine);

  
  TEST_ASSERT_EQUAL_HEX16(0x0028, e.e_machine);

  closeFileInTxt(myFile);
}

void test_getElfOriVersion(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfOriVersion(myFile, &e); // Machine
  printf("%x", e.e_version);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e.e_version);

  closeFileInTxt(myFile);
}

void test_getElfEntryPointAddress(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfEntryPointAddress(myFile, &e); // Machine
  printf("%x", e.e_entry);
  
  TEST_ASSERT_EQUAL_HEX32(0x08000fed, e.e_entry);

  closeFileInTxt(myFile);
}

void test_getElfStartOfProgramHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfStartOfProgramHeader(myFile, &e); // Machine
  printf("%x", e.e_phoff);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000034, e.e_phoff);

  closeFileInTxt(myFile);
}

void test_getElfStartOfSectionHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfStartOfSectionHeader(myFile, &e); // Machine
  printf("%x", e.e_shoff);
  
  TEST_ASSERT_EQUAL_HEX32(0x00013168, e.e_shoff);

  closeFileInTxt(myFile);
}

void test_getElfFlag(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfFlag(myFile, &e); // Machine
  printf("%x", e.e_flags);
  
  TEST_ASSERT_EQUAL_HEX32(0x05000202, e.e_flags);

  closeFileInTxt(myFile);
}

void test_getElfSizeOfHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfSizeOfHeader(myFile, &e); // Machine
  printf("%x", e.e_ehsize);
  
  TEST_ASSERT_EQUAL_HEX16(0x0034, e.e_ehsize);

  closeFileInTxt(myFile);
}

void test_getElfProgramHeaderSize(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfProgramHeaderSize(myFile, &e); // Machine
  printf("%x", e.e_phentsize);
  
  TEST_ASSERT_EQUAL_HEX16(0x0020, e.e_phentsize);

  closeFileInTxt(myFile);
}

void test_getElfNumberOfProgramHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfNumberOfProgramHeader(myFile, &e); // Machine
  printf("%x", e.e_phnum);
  
  TEST_ASSERT_EQUAL_HEX16(0x0003, e.e_phnum);

  closeFileInTxt(myFile);
}

void test_getElfSectionHeaderSize(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfSectionHeaderSize(myFile, &e); // Machine
  printf("%x", e.e_shentsize);
  
  TEST_ASSERT_EQUAL_HEX16(0x0028, e.e_shentsize);

  closeFileInTxt(myFile);
}

void test_getElfNumberOfSectionHeader(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfNumberOfSectionHeader(myFile, &e); // Machine
  printf("%x", e.e_shnum);
  
  TEST_ASSERT_EQUAL_HEX16(0x0016, e.e_shnum);

  closeFileInTxt(myFile);
}

void test_getElfSectionHeaderStringTableIndex(void){
  InStream *myFile;
  Elf32_Ehdr e;
  int startPosition;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfSectionHeaderStringTableIndex(myFile, &e); // Machine
  printf("%x", e.e_shstrndx);
  
  TEST_ASSERT_EQUAL_HEX16(0x0013, e.e_shstrndx);

  closeFileInTxt(myFile);
}

