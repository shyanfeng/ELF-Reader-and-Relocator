#include "unity.h"
#include "GetHeaders.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"
#include "ProgramElf.h"
#include <stdlib.h>

void setUp(void){
  initElfData();
}

void tearDown(void){}
/******************************************************************
 *
 *                            ELF Header
 *
 ******************************************************************/
void test_getElfHeader(void){
  dataFromElf->myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  
  TEST_ASSERT_EQUAL_HEX8(ELFMAG0, dataFromElf->eh->e_ident[EI_MAG0]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG1, dataFromElf->eh->e_ident[EI_MAG1]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG2, dataFromElf->eh->e_ident[EI_MAG2]);
  TEST_ASSERT_EQUAL_HEX8(ELFMAG3, dataFromElf->eh->e_ident[EI_MAG3]);
  TEST_ASSERT_EQUAL_HEX8(ELFCLASS32, dataFromElf->eh->e_ident[EI_CLASS]);
  TEST_ASSERT_EQUAL_HEX8(ELFDATA2LSB, dataFromElf->eh->e_ident[EI_DATA]);
  TEST_ASSERT_EQUAL_HEX8(EV_CURRENT, dataFromElf->eh->e_ident[EI_VERSION]);
  TEST_ASSERT_EQUAL_HEX8(ELFOSABI_SYSV, dataFromElf->eh->e_ident[EI_OSABI]);
  TEST_ASSERT_EQUAL_HEX8(0, dataFromElf->eh->e_ident[EI_ABIVERSION]);
  TEST_ASSERT_EQUAL_HEX8(0, dataFromElf->eh->e_ident[EI_PAD]);
  TEST_ASSERT_EQUAL_HEX8(0, dataFromElf->eh->e_ident[10]);
  TEST_ASSERT_EQUAL_HEX8(0, dataFromElf->eh->e_ident[11]);
  TEST_ASSERT_EQUAL_HEX8(0, dataFromElf->eh->e_ident[12]);
  TEST_ASSERT_EQUAL_HEX8(0, dataFromElf->eh->e_ident[13]);
  TEST_ASSERT_EQUAL_HEX8(0, dataFromElf->eh->e_ident[14]);
  TEST_ASSERT_EQUAL_HEX8(0, dataFromElf->eh->e_ident[15]);
  
  TEST_ASSERT_EQUAL_HEX16(ET_EXEC, dataFromElf->eh->e_type);
  TEST_ASSERT_EQUAL_HEX16(0x0028, dataFromElf->eh->e_machine);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, dataFromElf->eh->e_version);
  TEST_ASSERT_EQUAL_HEX32(0x08000fed, dataFromElf->eh->e_entry);
  TEST_ASSERT_EQUAL_HEX32(0x00000034, dataFromElf->eh->e_phoff);
  TEST_ASSERT_EQUAL_HEX32(0x00013168, dataFromElf->eh->e_shoff);
  TEST_ASSERT_EQUAL_HEX32(0x05000202, dataFromElf->eh->e_flags);
  TEST_ASSERT_EQUAL_HEX16(0x0034, dataFromElf->eh->e_ehsize);
  TEST_ASSERT_EQUAL_HEX16(0x0020, dataFromElf->eh->e_phentsize);
  TEST_ASSERT_EQUAL_HEX16(0x0003, dataFromElf->eh->e_phnum);
  TEST_ASSERT_EQUAL_HEX16(0x0028, dataFromElf->eh->e_shentsize);
  TEST_ASSERT_EQUAL_HEX16(0x0016, dataFromElf->eh->e_shnum);
  TEST_ASSERT_EQUAL_HEX16(0x0013, dataFromElf->eh->e_shstrndx);
  
  closeFileInTxt(dataFromElf->myFile);
}

/******************************************************************
 *
 *                          Program Header
 *
 ******************************************************************/
void test_GetProgramHeaders(void){
  dataFromElf->myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->ph = getProgramHeaders(dataFromElf);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, dataFromElf->ph[0].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, dataFromElf->ph[0].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, dataFromElf->ph[0].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, dataFromElf->ph[0].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, dataFromElf->ph[0].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x0000106c, dataFromElf->ph[0].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RWX, dataFromElf->ph[0].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, dataFromElf->ph[0].p_align);

  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, dataFromElf->ph[1].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010000, dataFromElf->ph[1].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000000, dataFromElf->ph[1].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x0800106c, dataFromElf->ph[1].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, dataFromElf->ph[1].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000440, dataFromElf->ph[1].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, dataFromElf->ph[1].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, dataFromElf->ph[1].p_align);
  
  TEST_ASSERT_EQUAL_HEX32(PT_LOAD, dataFromElf->ph[2].p_type);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, dataFromElf->ph[2].p_offset);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, dataFromElf->ph[2].p_vaddr);
  TEST_ASSERT_EQUAL_HEX32(0x20000440, dataFromElf->ph[2].p_paddr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->ph[2].p_filesz);
  TEST_ASSERT_EQUAL_HEX32(0x00000648, dataFromElf->ph[2].p_memsz);
  TEST_ASSERT_EQUAL_HEX32(PF_RW, dataFromElf->ph[2].p_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, dataFromElf->ph[2].p_align);
  
  closeFileInTxt(dataFromElf->myFile);
}

/******************************************************************
 *
 *                        Section Header
 *
 ******************************************************************/
void test_getSectionHeaders(void){
  dataFromElf->myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[0].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_NULL, dataFromElf->sh[0].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[0].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[0].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[0].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[0].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[0].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[0].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[0].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[0].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000001b, dataFromElf->sh[1].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, dataFromElf->sh[1].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC, dataFromElf->sh[1].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, dataFromElf->sh[1].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00008000, dataFromElf->sh[1].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x000001ac, dataFromElf->sh[1].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[1].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[1].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, dataFromElf->sh[1].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[1].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000027, dataFromElf->sh[2].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, dataFromElf->sh[2].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_EXECINSTR_ALLOC, dataFromElf->sh[2].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x080001ac, dataFromElf->sh[2].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000081ac, dataFromElf->sh[2].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000eac, dataFromElf->sh[2].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[2].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[2].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, dataFromElf->sh[2].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[2].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000002d, dataFromElf->sh[3].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, dataFromElf->sh[3].sh_type);
  TEST_ASSERT_EQUAL_HEX32(SHF_ALLOC, dataFromElf->sh[3].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x08001058, dataFromElf->sh[3].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00009058, dataFromElf->sh[3].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000008, dataFromElf->sh[3].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[3].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[3].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, dataFromElf->sh[3].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[3].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000072, dataFromElf->sh[10].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_ARM_ATTRIBUTES, dataFromElf->sh[10].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[10].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[10].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00010440, dataFromElf->sh[10].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x0000002a, dataFromElf->sh[10].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[10].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[10].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, dataFromElf->sh[10].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[10].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x000000ab, dataFromElf->sh[14].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_PROGBITS, dataFromElf->sh[14].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[14].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[14].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00011c80, dataFromElf->sh[14].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000993, dataFromElf->sh[14].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[14].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[14].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, dataFromElf->sh[14].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[14].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000011, dataFromElf->sh[19].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_STRTAB, dataFromElf->sh[19].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[19].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[19].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x00013080, dataFromElf->sh[19].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x000000e6, dataFromElf->sh[19].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[19].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[19].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, dataFromElf->sh[19].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[19].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000001, dataFromElf->sh[20].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_SYMTAB, dataFromElf->sh[20].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[20].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[20].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000134d8, dataFromElf->sh[20].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00001220, dataFromElf->sh[20].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000015, dataFromElf->sh[20].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x0000008c, dataFromElf->sh[20].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000004, dataFromElf->sh[20].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000010, dataFromElf->sh[20].sh_entsize);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000009, dataFromElf->sh[21].sh_name);
  TEST_ASSERT_EQUAL_HEX32(SHT_STRTAB, dataFromElf->sh[21].sh_type);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[21].sh_flags);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[21].sh_addr);
  TEST_ASSERT_EQUAL_HEX32(0x000146f8, dataFromElf->sh[21].sh_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000dd6, dataFromElf->sh[21].sh_size);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[21].sh_link);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[21].sh_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000001, dataFromElf->sh[21].sh_addralign);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->sh[21].sh_entsize);
  
  closeFileInTxt(dataFromElf->myFile);
}

/******************************************************************
 *
 *                            Symbol Table
 *
 ******************************************************************/
void test_getSymbolTables(void){
  dataFromElf->myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  dataFromElf->st = getSymbolTables(dataFromElf);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[0].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[0].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[0].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_NOTYPE), dataFromElf->st[0].st_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[0].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0000, dataFromElf->st[0].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[1].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, dataFromElf->st[1].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[1].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), dataFromElf->st[1].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), dataFromElf->st[1].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0001, dataFromElf->st[1].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[2].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x080001ac, dataFromElf->st[2].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[2].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), dataFromElf->st[2].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), dataFromElf->st[2].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, dataFromElf->st[2].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[14].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[14].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[14].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), dataFromElf->st[14].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), dataFromElf->st[14].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x000e, dataFromElf->st[14].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000006c, dataFromElf->st[29].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[29].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[29].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FILE), dataFromElf->st[29].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), dataFromElf->st[29].st_other);
  TEST_ASSERT_EQUAL_HEX16(0xfff1, dataFromElf->st[29].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000077, dataFromElf->st[30].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08001040, dataFromElf->st[30].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, dataFromElf->st[30].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_OBJECT), dataFromElf->st[30].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), dataFromElf->st[30].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, dataFromElf->st[30].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x000001ef, dataFromElf->st[101].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000efd, dataFromElf->st[101].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000014, dataFromElf->st[101].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FUNC), dataFromElf->st[101].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), dataFromElf->st[101].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, dataFromElf->st[101].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x000002ed, dataFromElf->st[120].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x20000018, dataFromElf->st[120].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000428, dataFromElf->st[120].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_OBJECT), dataFromElf->st[120].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), dataFromElf->st[120].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0006, dataFromElf->st[120].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000042a, dataFromElf->st[144].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000551, dataFromElf->st[144].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000214, dataFromElf->st[144].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_GLOBAL, STT_FUNC), dataFromElf->st[144].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), dataFromElf->st[144].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, dataFromElf->st[144].st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000dbe, dataFromElf->st[289].st_name);
  TEST_ASSERT_EQUAL_HEX32(0x0800103d, dataFromElf->st[289].st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000002, dataFromElf->st[289].st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_WEAK, STT_FUNC), dataFromElf->st[289].st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), dataFromElf->st[289].st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, dataFromElf->st[289].st_shndx);
  
  closeFileInTxt(dataFromElf->myFile);
}

/******************************************************************
 *
 *                       Info of Section and Name
 *
 ******************************************************************/
void test_getAllSectionInfo_of_name_and_section(void){
  dataFromElf->myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  dataFromElf->programElf = getAllSectionInfo(dataFromElf);
  
  TEST_ASSERT_EQUAL_STRING(".isr_vector", dataFromElf->programElf[1].name);
  TEST_ASSERT_EQUAL_STRING(".init_array", dataFromElf->programElf[4].name);
  TEST_ASSERT_EQUAL_STRING(".ccmram", dataFromElf->programElf[7].name);
  
  closeFileInTxt(dataFromElf->myFile);
}

/*******************************************************************
 *
 *                      Get index by name
 *
 *******************************************************************/
void test_getIndexOfSectionByName_with_isr_vector(void){
  dataFromElf->myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  
  TEST_ASSERT_EQUAL(1, getIndexOfSectionByName(dataFromElf, ".isr_vector"));
  
  closeFileInTxt(dataFromElf->myFile);
}

void test_getIndexOfSectionByName_invalid_not_found_should_return_neg_1(void){
  dataFromElf->myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  
  TEST_ASSERT_EQUAL(-1, getIndexOfSectionByName(dataFromElf, ".shouldFail"));
  
  closeFileInTxt(dataFromElf->myFile);
}
 
/*******************************************************************
 *
 *                      Get section size by index
 *
 *******************************************************************/
void test_getSectionSize_with_index_1(void){
  dataFromElf->myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  
  TEST_ASSERT_EQUAL(428, getSectionSize(dataFromElf, 1));
}

// get Relocate offset n info
void test_getRelocation(void){
  dataFromElf->myFile = openFile("test/Relocation_File/add.o", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  dataFromElf->rel = getRelocation(dataFromElf);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000006, dataFromElf->rel[0].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000702, dataFromElf->rel[0].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000000c, dataFromElf->rel[1].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000a02, dataFromElf->rel[1].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000011, dataFromElf->rel[2].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000a02, dataFromElf->rel[2].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000015, dataFromElf->rel[3].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000202, dataFromElf->rel[3].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000001d, dataFromElf->rel[4].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000902, dataFromElf->rel[4].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000002c, dataFromElf->rel[5].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000202, dataFromElf->rel[5].r_info);

}

// get Relocate symbol
void test_getRelSymbol_with_index_0(void){
  dataFromElf->myFile = openFile("test/Relocation_File/add.o", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  dataFromElf->rel = getRelocation(dataFromElf);
  dataFromElf->st = getSymbolTables(dataFromElf);
  
  TEST_ASSERT_EQUAL_STRING(".debug_abbrev", getRelSymbolName(dataFromElf, 0));
  
}

void test_getRelSymbol_with_index_3(void){
  dataFromElf->myFile = openFile("test/Relocation_File/add.o", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  dataFromElf->rel = getRelocation(dataFromElf);
  dataFromElf->st = getSymbolTables(dataFromElf);
  
  TEST_ASSERT_EQUAL_STRING(".text", getRelSymbolName(dataFromElf, 3));
  
}

// get Relocate type
void test_getRelType_with_index_1_should_return_R_ARM_ABS32(void){
  dataFromElf->myFile = openFile("test/Relocation_File/add.o", "rb+");
  dataFromElf->eh = getElfHeader(dataFromElf);
  dataFromElf->sh = getSectionHeaders(dataFromElf);
  dataFromElf->rel = getRelocation(dataFromElf);
  
  TEST_ASSERT_EQUAL(R_ARM_ABS32, getRelType(dataFromElf, 1));

}

