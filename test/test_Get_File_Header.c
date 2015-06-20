#include "unity.h"
#include "Get_File_Header.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}
// File Header
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

// Program Header
void test_GetProgramHeader(void){
  InStream *myFile;
  
  Elf32_Phdr *ph = getProgramHeader(myFile, 0);
  
  
}


void test_loop_for_program_header_size(void){
  InStream *myFile;
  Elf32_Phdr *e[3];
  Elf32_Ehdr *e2;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  read_ELF_File_Header(myFile, &e2);
  loop_for_program_header_size(myFile, e, &e2);

  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, e[0]->p_type);
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


// Section Header
void test_loop_for_section_header_size(void){
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
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_WRITE, e[4]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001060, e[4]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009060, e[4]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, e[4]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[4]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[4]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, e[4]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[4]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000041, e[5]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_FINI_ARRAY, e[5]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_WRITE, e[5]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001068, e[5]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009068, e[5]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, e[5]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[5]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[5]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, e[5]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[5]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000004d, e[6]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[6]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_WRITE, e[6]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x20000000, e[6]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010000, e[6]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, e[6]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[6]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[6]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, e[6]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[6]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000053, e[7]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[7]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_WRITE, e[7]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x10000000, e[7]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, e[7]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[7]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[7]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[7]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e[7]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[7]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000005b, e[8]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_NOBITS, e[8]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_WRITE, e[8]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, e[8]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, e[8]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000048, e[8]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[8]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[8]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, e[8]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[8]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000060, e[9]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_NOBITS, e[9]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_WRITE, e[9]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x20000488, e[9]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, e[9]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000600, e[9]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[9]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[9]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e[9]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[9]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000072, e[10]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_ARM_ATTRIBUTES, e[10]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[10]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[10]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, e[10]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x0000002a, e[10]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[10]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[10]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e[10]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[10]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000082, e[11]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[11]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[11]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[11]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x0001046a, e[11]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00001315, e[11]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[11]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[11]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e[11]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[11]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000008e, e[12]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[12]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[12]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[12]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x0001177f, e[12]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000479, e[12]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[12]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[12]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e[12]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[12]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000009c, e[13]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[13]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[13]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[13]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00011bf8, e[13]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000088, e[13]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[13]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[13]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, e[13]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[13]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x000000ab, e[14]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[14]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[14]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[14]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00011c80, e[14]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000993, e[14]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[14]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[14]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e[14]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[14]->sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x000000b7, e[15]->sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[15]->sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHT_MERGE_STRING, e[15]->sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[15]->sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00012613, e[15]->sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000693, e[15]->sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[15]->sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, e[15]->sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e[15]->sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, e[15]->sh_entsize);
  
  // TEST_ASSERT_EQUAL_HEX32(0x000000b7, e[16]->sh_name);
  // TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, e[16]->sh_type);
  // TEST_ASSERT_EQUAL_HEX32(SHT_MERGE_STRING, e[16]->sh_flags);
  // TEST_ASSERT_EQUAL_HEX32(0x00000000, e[16]->sh_addr);
  // TEST_ASSERT_EQUAL_HEX32(0x00012613, e[16]->sh_offset);
  // TEST_ASSERT_EQUAL_HEX32(0x00000693, e[16]->sh_size);
  // TEST_ASSERT_EQUAL_HEX32(0x00000000, e[16]->sh_link);
  // TEST_ASSERT_EQUAL_HEX32(0x00000000, e[16]->sh_info);
  // TEST_ASSERT_EQUAL_HEX32(0x00000001, e[16]->sh_addralign);
  // TEST_ASSERT_EQUAL_HEX32(0x00000001, e[16]->sh_entsize);
  
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