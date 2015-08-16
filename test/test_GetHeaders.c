#include "unity.h"
#include "GetHeaders.h"
#include "Read_File.h"
#include "Relocator.h"
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
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX8(ELFMAG0, elfData->eh->e_ident[EI_MAG0]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG1, elfData->eh->e_ident[EI_MAG1]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG2, elfData->eh->e_ident[EI_MAG2]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG3, elfData->eh->e_ident[EI_MAG3]);
  TEST_ASSERT_EQUAL_HEX8(ELFCLASS32, elfData->eh->e_ident[EI_CLASS]);
  TEST_ASSERT_EQUAL_HEX8(ELFDATA2LSB, elfData->eh->e_ident[EI_DATA]);
  TEST_ASSERT_EQUAL_HEX8(EV_CURRENT, elfData->eh->e_ident[EI_VERSION]);
  TEST_ASSERT_EQUAL_HEX8(ELFOSABI_SYSV, elfData->eh->e_ident[EI_OSABI]);
  TEST_ASSERT_EQUAL_HEX8(0, elfData->eh->e_ident[EI_ABIVERSION]);
  TEST_ASSERT_EQUAL_HEX8(0, elfData->eh->e_ident[EI_PAD]);
  TEST_ASSERT_EQUAL_HEX8(0, elfData->eh->e_ident[10]);
  TEST_ASSERT_EQUAL_HEX8(0, elfData->eh->e_ident[11]);
  TEST_ASSERT_EQUAL_HEX8(0, elfData->eh->e_ident[12]);
  TEST_ASSERT_EQUAL_HEX8(0, elfData->eh->e_ident[13]);
  TEST_ASSERT_EQUAL_HEX8(0, elfData->eh->e_ident[14]);
  TEST_ASSERT_EQUAL_HEX8(0, elfData->eh->e_ident[15]);
  
  TEST_ASSERT_EQUAL_HEX16(ET_EXEC, elfData->eh->e_type);
  TEST_ASSERT_EQUAL_HEX16(0x0028, elfData->eh->e_machine);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, elfData->eh->e_version);
  TEST_ASSERT_EQUAL_HEX32(0x08000fed, elfData->eh->e_entry);
  TEST_ASSERT_EQUAL_HEX32(0x00000034, elfData->eh->e_phoff);
  TEST_ASSERT_EQUAL_HEX32(0x00013168, elfData->eh->e_shoff);
  TEST_ASSERT_EQUAL_HEX32(0x05000202, elfData->eh->e_flags);
  TEST_ASSERT_EQUAL_HEX16(0x0034, elfData->eh->e_ehsize);
  TEST_ASSERT_EQUAL_HEX16(0x0020, elfData->eh->e_phentsize);
  TEST_ASSERT_EQUAL_HEX16(0x0003, elfData->eh->e_phnum);
  TEST_ASSERT_EQUAL_HEX16(0x0028, elfData->eh->e_shentsize);
  TEST_ASSERT_EQUAL_HEX16(0x0016, elfData->eh->e_shnum);
  TEST_ASSERT_EQUAL_HEX16(0x0013, elfData->eh->e_shstrndx);
  
  closeFileInTxt(elfData->myFile);
}

/******************************************************************
 *
 *                          Program Header
 *
 ******************************************************************/
void test_GetProgramHeaders(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, elfData->ph[0].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, elfData->ph[0].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, elfData->ph[0].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, elfData->ph[0].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, elfData->ph[0].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, elfData->ph[0].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RWX, elfData->ph[0].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, elfData->ph[0].p_align);

  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, elfData->ph[1].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010000, elfData->ph[1].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000000, elfData->ph[1].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x0800106c, elfData->ph[1].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, elfData->ph[1].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, elfData->ph[1].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, elfData->ph[1].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, elfData->ph[1].p_align);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, elfData->ph[2].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, elfData->ph[2].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, elfData->ph[2].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, elfData->ph[2].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->ph[2].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000648, elfData->ph[2].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, elfData->ph[2].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, elfData->ph[2].p_align);
  
  closeFileInTxt(elfData->myFile);
}

/******************************************************************
 *
 *                        Section Header
 *
 ******************************************************************/
void test_getSectionHeaders(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[0].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_NULL, elfData->sh[0].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[0].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[0].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[0].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[0].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[0].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[0].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[0].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[0].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000001b, elfData->sh[1].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, elfData->sh[1].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC, elfData->sh[1].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, elfData->sh[1].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, elfData->sh[1].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x000001ac, elfData->sh[1].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[1].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[1].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, elfData->sh[1].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[1].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000027, elfData->sh[2].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, elfData->sh[2].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_EXECINSTR_ALLOC, elfData->sh[2].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x080001ac, elfData->sh[2].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000081ac, elfData->sh[2].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000eac, elfData->sh[2].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[2].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[2].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, elfData->sh[2].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[2].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000002d, elfData->sh[3].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, elfData->sh[3].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC, elfData->sh[3].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001058, elfData->sh[3].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009058, elfData->sh[3].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, elfData->sh[3].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[3].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[3].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, elfData->sh[3].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[3].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000072, elfData->sh[10].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_ARM_ATTRIBUTES, elfData->sh[10].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[10].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[10].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, elfData->sh[10].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x0000002a, elfData->sh[10].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[10].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[10].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, elfData->sh[10].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[10].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x000000ab, elfData->sh[14].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, elfData->sh[14].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[14].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[14].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00011c80, elfData->sh[14].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000993, elfData->sh[14].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[14].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[14].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, elfData->sh[14].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[14].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000011, elfData->sh[19].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_STRTAB, elfData->sh[19].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[19].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[19].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00013080, elfData->sh[19].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x000000e6, elfData->sh[19].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[19].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[19].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, elfData->sh[19].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[19].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000001, elfData->sh[20].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_SYMTAB, elfData->sh[20].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[20].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[20].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000134d8, elfData->sh[20].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00001220, elfData->sh[20].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000015, elfData->sh[20].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x0000008c, elfData->sh[20].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, elfData->sh[20].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000010, elfData->sh[20].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000009, elfData->sh[21].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_STRTAB, elfData->sh[21].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[21].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[21].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000146f8, elfData->sh[21].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000dd6, elfData->sh[21].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[21].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[21].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, elfData->sh[21].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->sh[21].sh_entsize);
  
  closeFileInTxt(elfData->myFile);
}

/******************************************************************
 *
 *                            Symbol Table
 *
 ******************************************************************/
void test_getSymbolTables(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[0].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[0].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[0].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_NOTYPE), elfData->st[0].st_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[0].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0000, elfData->st[0].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[1].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, elfData->st[1].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[1].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), elfData->st[1].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), elfData->st[1].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0001, elfData->st[1].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[2].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x080001ac, elfData->st[2].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[2].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), elfData->st[2].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), elfData->st[2].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, elfData->st[2].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[14].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[14].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[14].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), elfData->st[14].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), elfData->st[14].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x000e, elfData->st[14].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000006c, elfData->st[29].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[29].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[29].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FILE), elfData->st[29].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), elfData->st[29].st_other);
  TEST_ASSERT_EQUAL_HEX16(0xfff1, elfData->st[29].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000077, elfData->st[30].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08001040, elfData->st[30].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, elfData->st[30].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_OBJECT), elfData->st[30].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), elfData->st[30].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, elfData->st[30].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x000001ef, elfData->st[101].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000efd, elfData->st[101].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000014, elfData->st[101].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FUNC), elfData->st[101].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), elfData->st[101].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, elfData->st[101].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x000002ed, elfData->st[120].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x20000018, elfData->st[120].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000428, elfData->st[120].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_OBJECT), elfData->st[120].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), elfData->st[120].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0006, elfData->st[120].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000042a, elfData->st[144].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000551, elfData->st[144].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000214, elfData->st[144].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_GLOBAL, STT_FUNC), elfData->st[144].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), elfData->st[144].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, elfData->st[144].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000dbe, elfData->st[289].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x0800103d, elfData->st[289].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000002, elfData->st[289].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_WEAK, STT_FUNC), elfData->st[289].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), elfData->st[289].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, elfData->st[289].st_shndx);
  
  closeFileInTxt(elfData->myFile);
}

/******************************************************************
 *
 *                Get Section Info Using Index
 *
 *****************************************************************/
void test_getSectionInfoUsingIndex_to_get_the_section_info(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  uint32_t *getSectionInfo = getSectionInfoUsingIndex(elfData, 2);
  
  TEST_ASSERT_EQUAL_HEX32(0x4c05b510, getSectionInfo[0]);
  TEST_ASSERT_EQUAL_HEX32(0xb9337823, getSectionInfo[1]);
  TEST_ASSERT_EQUAL_HEX32(0x23018000, getSectionInfo[4]);
  TEST_ASSERT_EQUAL_HEX32(0xb9036803, getSectionInfo[13]);
  
  closeFileInTxt(elfData->myFile);
}

/******************************************************************
 *
 *                       Info of Section and Name
 *
 ******************************************************************/
void test_getAllSectionInfo_of_name_and_section(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");

  TEST_ASSERT_EQUAL_STRING(".isr_vector", elfData->programElf[1].name);
  TEST_ASSERT_EQUAL_STRING(".text", elfData->programElf[2].name);
  TEST_ASSERT_EQUAL_HEX8(0x10, elfData->programElf[2].section[0]);       // First Byte of .text
  TEST_ASSERT_EQUAL_HEX8(0xb5, elfData->programElf[2].section[1]);       // Second Byte of .text
  TEST_ASSERT_EQUAL_HEX8(0x05, elfData->programElf[2].section[2]);       // Third Byte of .text
  TEST_ASSERT_EQUAL_HEX8(0x4c, elfData->programElf[2].section[3]);       // Forth Byte of .text
  TEST_ASSERT_EQUAL_HEX8(0x08, elfData->programElf[2].section[50]);      // Fifty Byte of .text
  TEST_ASSERT_EQUAL_HEX8(0x48, elfData->programElf[2].section[51]);      // Fifty One Byte of .text
  TEST_ASSERT_EQUAL_HEX8(0x47, elfData->programElf[2].section[3755]);    // Last Byte of .text
  TEST_ASSERT_EQUAL_STRING(".init_array", elfData->programElf[4].name);
  TEST_ASSERT_EQUAL_STRING(".ccmram", elfData->programElf[7].name);
  
  closeFileInTxt(elfData->myFile);
}

void test_getSectionHeaderAddrUsingIndex(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  uint32_t shAddr;
  
  shAddr = getSectionHeaderAddrUsingIndex(elfData, 0);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, shAddr);
  
  shAddr = getSectionHeaderAddrUsingIndex(elfData, 2);
  TEST_ASSERT_EQUAL_HEX32(0x080001ac, shAddr);
  
  shAddr = getSectionHeaderAddrUsingIndex(elfData, 14);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, shAddr);
  
  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *                      Get index by name
 *
 *******************************************************************/
void test_getIndexOfSectionByName_with_isr_vector(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL(1, getIndexOfSectionByName(elfData, ".isr_vector"));
  
  closeFileInTxt(elfData->myFile);
}

void test_getIndexOfSectionByName_invalid_not_found_should_return_neg_1(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL(-1, getIndexOfSectionByName(elfData, ".shouldFail"));
  
  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *                      Get section size by index
 *
 *******************************************************************/
void test_getSectionSize_with_index_1(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL(428, getSectionSize(elfData, 1));
  
  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *                      Get physical address by index
 *
 *******************************************************************/
void test_getSectionPhysicalAddress_with_index_1(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(0x0800106c, getSectionPhysicalAddress(elfData, 1));
  
  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *                      Get virtual address by index
 *
 *******************************************************************/
void test_getSectionVirtualAddress_with_index_1(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(0x20000000, getSectionVirtualAddress(elfData, 1));
  
  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *               Check Section Available fo Executable
 *
 *******************************************************************/
void test_isSectionExecutable_should_return_0(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(0, isSectionExecutable(elfData, 1));
  
  closeFileInTxt(elfData->myFile);
}

void test_isSectionExecutable_should_return_1(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(1, isSectionExecutable(elfData, 0));
  
  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *               Check Section Available fo Writeable
 *
 *******************************************************************/
void test_isSectionWriteable_should_return_1(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(1, isSectionWriteable(elfData, 2));
  
  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *               Check Section Available fo Readable
 *
 *******************************************************************/
void test_isSectionReadable_should_return_1(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(1, isSectionReadable(elfData, 2));
  
  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *                  Get Symbol Table Size From Name
 *
 *******************************************************************/
void test_getSymbolTableSizeUsingName_with_name_LoopCopyDataInit_should_return_size(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL(0, getSymbolTableSizeUsingName(elfData, "LoopCopyDataInit"));
  
  closeFileInTxt(elfData->myFile);
}

void test_getSymbolTableSizeUsingName_with_name_HAL_GPIO_DeInit_should_return_size(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL(532, getSymbolTableSizeUsingName(elfData, "HAL_GPIO_DeInit"));
  
  closeFileInTxt(elfData->myFile);
}

void test_getSymbolTableSizeUsingName_with_invalid_name_should_return_negative_1(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(-1, getSymbolTableSizeUsingName(elfData, "Invalid_name"));
  
  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *                  Get Symbol Table Address From Name
 *
 *******************************************************************/
void test_getSymbolTableAddressUsingName_with_currentTime_should_return_address(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(0x2000045c, getSymbolTableAddressUsingName(elfData, "currentTime"));

  closeFileInTxt(elfData->myFile);
}

void test_getSymbolTableAddressUsingName_with_invalid_name_should_return_negative_1(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_HEX32(-1, getSymbolTableAddressUsingName(elfData, "Invalid_name"));

  closeFileInTxt(elfData->myFile);
}

/*******************************************************************
 *
 *                  Get Symbol Table Name Using Index
 *
 *******************************************************************/
void test_getSymbolTableUsingIndex_with_index_289(void){
  ElfData *elfData = openElfFile("test/ELF_File/Test01.elf");
  
  TEST_ASSERT_EQUAL_STRING("DMA1_Stream3_IRQHandler", getSymbolTableNameUsingIndex(elfData, 289));

  closeFileInTxt(elfData->myFile);
}
