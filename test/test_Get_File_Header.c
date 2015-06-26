#include "unity.h"
#include "Get_File_Header.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}
// File Header
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

// Program Header
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

// Section Header
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
  
}
/*
// Symbol Table
void test_getSymbolTables(void){
  InStream *myFile;
  Elf32_Sym *st[290];
  Elf32_Ehdr *e2;
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  getElfHeader(myFile, &e2);
  getSymbolTables(myFile, st, &e2);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[0]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[0]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[0]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_NOTYPE), st[0]->st_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[0]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0000, st[0]->st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[1]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000000, st[1]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[1]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), st[1]->st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[1]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0001, st[1]->st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[2]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x080001ac, st[2]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[2]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), st[2]->st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[2]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, st[2]->st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[7]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x10000000, st[7]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[7]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), st[7]->st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[7]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0007, st[7]->st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[14]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[14]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[14]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_SECTION), st[14]->st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[14]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0x000e, st[14]->st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000001, st[19]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[19]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[19]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FILE), st[19]->st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[19]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0xfff1, st[19]->st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000001e, st[26]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x0800103c, st[26]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[26]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_NOTYPE), st[26]->st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[26]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, st[26]->st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000006c, st[29]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[29]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[29]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FILE), st[29]->st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[29]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0xfff1, st[29]->st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000077, st[30]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08001040, st[30]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[30]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_OBJECT), st[30]->st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[30]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, st[30]->st_shndx);
  
  TEST_ASSERT_EQUAL_HEX32(0x000001ef, st[101]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000efd, st[101]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000014, st[101]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FUNC), st[101]->st_info);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_VISIBILITY(STV_DEFAULT), st[101]->st_other);
  TEST_ASSERT_EQUAL_HEX16(0x0002, st[101]->st_shndx);
  
  closeFileInTxt(myFile);
  
}

void test_getSymbolTable(void){
  InStream *myFile;
  Elf32_Sym *st[290];
  
  myFile = openFile("test/ELF_File/Test01.elf", "rb+");
  inStreamMoveFilePtr(myFile, 0x13b28);
  getSymbolTable(myFile, &st[101]);
  
  TEST_ASSERT_EQUAL_HEX32(0x000001ef, st[101]->st_name);
  TEST_ASSERT_EQUAL_HEX32(0x08000efd, st[101]->st_value);
  TEST_ASSERT_EQUAL_HEX32(0x00000014, st[101]->st_size);
  TEST_ASSERT_EQUAL_HEX32(ELF32_ST_INFO(STB_LOCAL, STT_FUNC), st[101]->st_info);
  TEST_ASSERT_EQUAL_HEX32(0x00000000, st[101]->st_other);
  TEST_ASSERT_EQUAL_HEX32(0x00000002, st[101]->st_shndx);
  
  
  
  closeFileInTxt(myFile);
  
}

*/
