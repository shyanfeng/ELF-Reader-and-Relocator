#include "unity.h"
#include "GetHeaders.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"
#include "ProgramElf.h"
#include <stdlib.h>

void setUp(void){}

void tearDown(void){}
/******************************************************************
 *
 *                            ELF Header
 *
 ******************************************************************/
void test_getElfHeader(void){
  InStream *myFile;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  
  TEST_ASSERT_EQUAL_HEX8(ELFMAG0, eh->e_ident[EI_MAG0]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG1, eh->e_ident[EI_MAG1]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG2, eh->e_ident[EI_MAG2]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG3, eh->e_ident[EI_MAG3]);
  TEST_ASSERT_EQUAL_HEX8(ELFCLASS32, eh->e_ident[EI_CLASS]);
  TEST_ASSERT_EQUAL_HEX8(ELFDATA2LSB, eh->e_ident[EI_DATA]);
  TEST_ASSERT_EQUAL_HEX8(EV_CURRENT, eh->e_ident[EI_VERSION]);
  TEST_ASSERT_EQUAL_HEX8(ELFOSABI_SYSV, eh->e_ident[EI_OSABI]);
  TEST_ASSERT_EQUAL_HEX8(0, eh->e_ident[EI_ABIVERSION]);
  TEST_ASSERT_EQUAL_HEX8(0, eh->e_ident[EI_PAD]);
  TEST_ASSERT_EQUAL_HEX8(0, eh->e_ident[10]);
  TEST_ASSERT_EQUAL_HEX8(0, eh->e_ident[11]);
  TEST_ASSERT_EQUAL_HEX8(0, eh->e_ident[12]);
  TEST_ASSERT_EQUAL_HEX8(0, eh->e_ident[13]);
  TEST_ASSERT_EQUAL_HEX8(0, eh->e_ident[14]);
  TEST_ASSERT_EQUAL_HEX8(0, eh->e_ident[15]);
  
  TEST_ASSERT_EQUAL_HEX16(ET_EXEC, eh->e_type);
  TEST_ASSERT_EQUAL_HEX16(0x0028, eh->e_machine);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, eh->e_version);
  TEST_ASSERT_EQUAL_HEX32(0x08000fed, eh->e_entry);
  TEST_ASSERT_EQUAL_HEX32(0x00000034, eh->e_phoff);
  TEST_ASSERT_EQUAL_HEX32(0x00013168, eh->e_shoff);
  TEST_ASSERT_EQUAL_HEX32(0x05000202, eh->e_flags);
  TEST_ASSERT_EQUAL_HEX16(0x0034, eh->e_ehsize);
  TEST_ASSERT_EQUAL_HEX16(0x0020, eh->e_phentsize);
  TEST_ASSERT_EQUAL_HEX16(0x0003, eh->e_phnum);
  TEST_ASSERT_EQUAL_HEX16(0x0028, eh->e_shentsize);
  TEST_ASSERT_EQUAL_HEX16(0x0016, eh->e_shnum);
  TEST_ASSERT_EQUAL_HEX16(0x0013, eh->e_shstrndx);
  
  closeFileInTxt(myFile);
}

/******************************************************************
 *
 *                          Program Header
 *
 ******************************************************************/
void test_GetProgramHeaders(void){
  InStream *myFile;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Phdr *ph = getProgramHeaders(myFile, eh);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, ph[0].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, ph[0].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, ph[0].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, ph[0].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, ph[0].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, ph[0].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RWX, ph[0].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, ph[0].p_align);

  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, ph[1].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010000, ph[1].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000000, ph[1].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x0800106c, ph[1].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, ph[1].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, ph[1].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, ph[1].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, ph[1].p_align);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, ph[2].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, ph[2].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, ph[2].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, ph[2].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, ph[2].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000648, ph[2].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, ph[2].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, ph[2].p_align);
  
  closeFileInTxt(myFile);
}

/******************************************************************
 *
 *                        Section Header
 *
 ******************************************************************/
void test_getSectionHeaders(void){
  InStream *myFile;

  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[0].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_NULL, sh[0].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[0].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[0].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[0].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[0].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[0].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[0].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[0].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[0].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000001b, sh[1].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, sh[1].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC, sh[1].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, sh[1].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, sh[1].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x000001ac, sh[1].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[1].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[1].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, sh[1].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[1].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000027, sh[2].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, sh[2].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_EXECINSTR_ALLOC, sh[2].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x080001ac, sh[2].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000081ac, sh[2].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000eac, sh[2].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[2].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[2].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, sh[2].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[2].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000002d, sh[3].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, sh[3].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC, sh[3].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001058, sh[3].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009058, sh[3].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, sh[3].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[3].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[3].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, sh[3].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[3].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000035, sh[4].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_INIT_ARRAY, sh[4].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_WRITE, sh[4].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001060, sh[4].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009060, sh[4].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, sh[4].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[4].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[4].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, sh[4].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[4].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000041, sh[5].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_FINI_ARRAY, sh[5].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_WRITE, sh[5].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001068, sh[5].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009068, sh[5].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, sh[5].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[5].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[5].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, sh[5].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[5].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000004d, sh[6].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, sh[6].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC_WRITE, sh[6].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x20000000, sh[6].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010000, sh[6].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, sh[6].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[6].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[6].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, sh[6].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[6].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000072, sh[10].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_ARM_ATTRIBUTES, sh[10].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[10].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[10].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, sh[10].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x0000002a, sh[10].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[10].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[10].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, sh[10].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[10].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x000000ab, sh[14].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, sh[14].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[14].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[14].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00011c80, sh[14].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000993, sh[14].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[14].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[14].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, sh[14].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[14].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000011, sh[19].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_STRTAB, sh[19].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[19].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[19].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00013080, sh[19].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x000000e6, sh[19].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[19].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[19].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, sh[19].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[19].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000001, sh[20].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_SYMTAB, sh[20].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[20].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[20].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000134d8, sh[20].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00001220, sh[20].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000015, sh[20].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x0000008c, sh[20].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, sh[20].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000010, sh[20].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000009, sh[21].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_STRTAB, sh[21].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[21].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[21].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000146f8, sh[21].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000dd6, sh[21].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[21].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[21].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, sh[21].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, sh[21].sh_entsize);
  
  closeFileInTxt(myFile);
}

/******************************************************************
 *
 *                            Symbol Table
 *
 ******************************************************************/
void test_getSymbolTables(void){
  InStream *myFile;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  Elf32_Sym *st = getSymbolTables(myFile, eh, sh);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[0].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[0].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[0].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_NOTYPE), st[0].st_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[0].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0000, st[0].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[1].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, st[1].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[1].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), st[1].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[1].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0001, st[1].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[2].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x080001ac, st[2].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[2].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), st[2].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[2].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, st[2].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[14].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[14].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[14].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), st[14].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[14].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x000e, st[14].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000006c, st[29].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[29].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[29].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FILE), st[29].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[29].st_other);
  TEST_ASSERT_EQUAL_HEX16(0xfff1, st[29].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000077, st[30].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08001040, st[30].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[30].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_OBJECT), st[30].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[30].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, st[30].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x000001ef, st[101].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000efd, st[101].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000014, st[101].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FUNC), st[101].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[101].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, st[101].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x000002ed, st[120].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x20000018, st[120].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000428, st[120].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_OBJECT), st[120].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[120].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0006, st[120].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000042a, st[144].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000551, st[144].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000214, st[144].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_GLOBAL, STT_FUNC), st[144].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[144].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, st[144].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000dbe, st[289].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x0800103d, st[289].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000002, st[289].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_WEAK, STT_FUNC), st[289].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[289].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, st[289].st_shndx);
  
  closeFileInTxt(myFile);
}

/******************************************************************
 *
 *                       Info of Section and Name
 *
 ******************************************************************/
void test_getAllSectionInfo_of_name_and_section(void){
  InStream *myFile;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  _Elf32_Shdr *getShInfoName = getAllSectionInfo(myFile, sh, eh);
  
  TEST_ASSERT_EQUAL_STRING(".isr_vector", getShInfoName[1].name);
  TEST_ASSERT_EQUAL_STRING(".init_array", getShInfoName[4].name);
  TEST_ASSERT_EQUAL_STRING(".ccmram", getShInfoName[7].name);
  
  closeFileInTxt(myFile);
}

/*******************************************************************
 *
 *                      Get index by name
 *
 *******************************************************************/
void test_getIndexOfSectionByName_with_isr_vector(void){
  InStream *myFile;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  int indexName;
  
  TEST_ASSERT_EQUAL(1, getIndexOfSectionByName(myFile, sh, eh, ".isr_vector"));
}

void test_getIndexOfSectionByName_invalid_not_found_should_return_neg_1(void){
  InStream *myFile;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  int indexName;
  
  TEST_ASSERT_EQUAL(-1, getIndexOfSectionByName(myFile, sh, eh, ".shouldFail"));
}

/*******************************************************************
 *
 *                      Get section address by index
 *
 *******************************************************************/
void test_getSectionAddress_with_index_1(void){
  InStream *myFile;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  
  TEST_ASSERT_EQUAL_HEX32(0x08000000, getSectionAddress(myFile, sh, 1));
}

void test_getSectionAddress_with_index_5(void){
  InStream *myFile;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  
  TEST_ASSERT_EQUAL_HEX32(0x08001068, getSectionAddress(myFile, sh, 5));
}
 
/*******************************************************************
 *
 *                      Get section size by index
 *
 *******************************************************************/
void test_getSectionSize_with_index_1(void){
  InStream *myFile;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  
  TEST_ASSERT_EQUAL(428, getSectionSize(myFile, sh, 1));
}

void test_getRelocation(void){
  InStream *myFile;
  
  myFile = openFile("test/Relocation_File/add.o", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  Elf32_Rel *rel = getRelocation(myFile, sh);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000006, rel[0].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000702, rel[0].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000000c, rel[1].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000a02, rel[1].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000011, rel[2].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000a02, rel[2].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000015, rel[3].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000202, rel[3].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000001d, rel[4].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000902, rel[4].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000002c, rel[5].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000202, rel[5].r_info);

}

void test_getRelSymbol_with_index_0(void){
  InStream *myFile;

  myFile = openFile("test/Relocation_File/add.o", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  Elf32_Rel *rel = getRelocation(myFile, sh);
  Elf32_Sym *st = getSymbolTables(myFile, eh, sh);
  
  TEST_ASSERT_EQUAL_STRING(".debug_abbrev", getRelSymbolName(myFile, sh, rel, st, 0));
  
}

void test_getRelSymbol_with_index_3(void){
  InStream *myFile;

  myFile = openFile("test/Relocation_File/add.o", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  Elf32_Rel *rel = getRelocation(myFile, sh);
  Elf32_Sym *st = getSymbolTables(myFile, eh, sh);
  
  TEST_ASSERT_EQUAL_STRING(".text", getRelSymbolName(myFile, sh, rel, st, 3));
  
}

void test_getRelType_with_index_1_should_return_R_ARM_ABS32(void){
  InStream *myFile;
  
  myFile = openFile("test/Relocation_File/add.o", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  Elf32_Rel *rel = getRelocation(myFile, sh);
  
  TEST_ASSERT_EQUAL(R_ARM_ABS32, getRelType(myFile, sh, rel, 1));

}

void test_getSectionData_with_index_1(void){
  InStream *myFile;
  int i;
  
  myFile = openFile("test/Relocation_File/add.o", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  uint32_t *getRead = getSectionData(myFile, sh, 1);
  
  TEST_ASSERT_EQUAL_HEX32(0xb083b480, getRead[0]);
  TEST_ASSERT_EQUAL_HEX32(0x6078af00, getRead[1]);
  TEST_ASSERT_EQUAL_HEX32(0x47707b04, getRead[6]);
}

void test_getSectionData_with_index_4(void){
  InStream *myFile;
  int i;
  
  myFile = openFile("test/Relocation_File/add.o", "rb+");
  Elf32_Ehdr *eh = getElfHeader(myFile);
  Elf32_Shdr *sh = getSectionHeaders(myFile, eh);
  uint32_t *getRead = getSectionData(myFile, sh, 4);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000057, getRead[0]);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, getRead[3]);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, getRead[7]);
  TEST_ASSERT_EQUAL_HEX32(0x03010064, getRead[9]);
  TEST_ASSERT_EQUAL_HEX32(0x6e690504, getRead[21]);
  TEST_ASSERT_EQUAL_HEX32(0x000074, getRead[22]);

}
