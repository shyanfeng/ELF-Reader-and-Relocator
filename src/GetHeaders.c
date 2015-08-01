#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Read_File.h"
#include "elf.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

ElfData *dataFromElf;

void initElfData(){
  dataFromElf = malloc(sizeof(ElfData));
}

/******************************************************************************
 * ELF Header
 *
 *  Operation:
 *          To read the information in the ELF Header
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *  
 *  Data:
 *          Information of the ELF Header allocate in the structure 
 *          of Elf32_Ehdr
 *
 *  Return:
 *          eh
 *          (The structure of Elf32_Ehdr with information of the ELF Header)
 *
 ******************************************************************************/
Elf32_Ehdr *getElfHeader(ElfData *dataFromElf){
  dataFromElf->eh = malloc(sizeof(Elf32_Ehdr));
  
  fread(dataFromElf->eh, sizeof(Elf32_Ehdr), 1, dataFromElf->myFile->file);
  
  return dataFromElf->eh;
}

/******************************************************************************
 * Program Header
 *
 *  Operation:
 *          To read the information in the Program Header by moving the file
 *          pointer to the e_phoff(Program_Header_Offset) in the Elf32_Ehdr
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *  
 *  Data:
 *          Information of the Program Header allocate in the structure 
 *          of Elf32_Phdr
 *
 *  Return:
 *          ph
 *          (The structure of Elf32_Phdr with information of the Program Header)
 *
 ******************************************************************************/
Elf32_Phdr *getProgramHeaders(ElfData *dataFromElf){
  int phSizeToMalloc = sizeof(Elf32_Phdr) * (dataFromElf->eh->e_phnum);
  dataFromElf->ph = malloc(phSizeToMalloc);

  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->eh->e_phoff);
  fread(dataFromElf->ph, phSizeToMalloc, 1, dataFromElf->myFile->file);
  
  return dataFromElf->ph;
}

/******************************************************************************
 * Section Header
 *
 *  Operation:
 *          To read the information in the Section Header by moving the file
 *          pointer to the e_shoff(Section_Header_Offset) in the Elf32_Ehdr
 *  
 *  Input:
 *          dataFromElf(ElfData structure)
 *  Data:
 *          Information of the Section Header allocate in the structure 
 *          of Elf32_Shdr
 *
 *  Return:
 *          sh
 *          (The structure of Elf32_Shdr with information of the Section Header)
 *
 ******************************************************************************/
Elf32_Shdr *getSectionHeaders(ElfData *dataFromElf){
  int shSizeToMalloc = sizeof(Elf32_Shdr) * (dataFromElf->eh->e_shnum);
  dataFromElf->sh = malloc(shSizeToMalloc);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->eh->e_shoff);
  fread(dataFromElf->sh, shSizeToMalloc, 1, dataFromElf->myFile->file);
  
  return dataFromElf->sh;
}

/******************************************************************************
 * Symbol Tables
 *
 *  Operation:
 *          To read the information in the Symbol Table by moving the file
 *          pointer to the sh_offset(Symbol_Table_Offset) in the Elf32_Shdr
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *  
 *  Data:
 *          Information of the Symbol Table allocate in the structure 
 *          of Elf32_Sym
 *
 *  Return:
 *          st
 *          (The structure of Elf32_Sym with information of the Symbol Table)
 *
 ******************************************************************************/
Elf32_Sym *getSymbolTables(ElfData *dataFromElf){
  int i, totalSymTab, entriesOfSymTab;
  int stSizeToMalloc;
  
  for(i = 0; dataFromElf->sh[i].sh_type != SHT_SYMTAB; i++);
  totalSymTab = dataFromElf->sh[i+1].sh_offset - dataFromElf->sh[i].sh_offset;
  dataFromElf->st = malloc(totalSymTab);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[i].sh_offset);
  fread(dataFromElf->st, totalSymTab, 1, dataFromElf->myFile->file);
  
  return dataFromElf->st;
}

/******************************************************************************
 * Get Section Info Name Using Index
 *
 *  Operation:
 *          To read the information of name in the section header by moving 
 *          the file pointer to the sh_offset(Symbol_Table_Offset) of String 
 *          Table add with sh[index].sh_name in the Elf32_Shdr. Index is the  
 *          index for Section Header
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Section index)
 *  
 *  Data:
 *          Information of the Section Name allocate with the size of String 
 *          Table type in the Section Header
 *
 *  Return:
 *          names
 *
 ******************************************************************************/
char *getSectionInfoNameUsingIndex(ElfData *dataFromElf, int index){
  char *names;
  int i;
  
  for(i = 0; dataFromElf->sh[i].sh_type != SHT_STRTAB; i++);
  names= malloc(dataFromElf->sh[i].sh_size);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[i].sh_offset + dataFromElf->sh[index].sh_name);
  fread(names, dataFromElf->sh[i].sh_size, 1, dataFromElf->myFile->file);
  
  return names;
}

/******************************************************************************
 * Get Section Info Using Index
 *
 *  Operation:
 *          To read the information of section in the section header by moving
 *          the file pointer to the sh[index].sh_offset(Symbol_Table_Offset)  
 *          in the Elf32_Shdr. Index is the index for Section Header
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Section index)
 *
 *  Data:
 *          Information of the Section allocate with the size of String 
 *          Table type in the Section Header
 *
 *  Return:
 *          sectInfo
 *
 ******************************************************************************/
uint32_t *getSectionInfoUsingIndex(ElfData *dataFromElf, int index){
  uint32_t *sectInfo = malloc(dataFromElf->sh[index].sh_size);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[index].sh_offset);
  fread(sectInfo, dataFromElf->sh[index].sh_size, 1, dataFromElf->myFile->file);

  return sectInfo;
}

/******************************************************************************
 * Get All Section Info
 *
 *  Operation:
 *          To read the information of section and name in the section header 
 *          with the two function created which are getSectionInfoUsingIndex
 *          and getSectionInfoNameUsingIndex.
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *  
 *  Data:
 *          Information of the Section allocate with the size of _Elf32_Shdr 
 *          multiply with e_shnum in the ELF Header
 *
 *  Return:
 *          getShInfo
 *          (The structure of _Elf32_Shdr)
 *
 ******************************************************************************/
_Elf32_Shdr *getAllSectionInfo(ElfData *dataFromElf){
  dataFromElf->programElf = malloc(dataFromElf->eh->e_shnum * sizeof(_Elf32_Shdr));
  int i;
  
  for(i = 0; i < dataFromElf->eh->e_shnum; i++){
    dataFromElf->programElf[i].section = (char *)getSectionInfoUsingIndex(dataFromElf, i);
    dataFromElf->programElf[i].name = (char *)getSectionInfoNameUsingIndex(dataFromElf, i);
  }
  
  return dataFromElf->programElf;
}

/******************************************************************************
 * Get Section Index From Section Name
 *
 *  Operation:
 *          To get the index of section in section header from the section name
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *  
 *  Data:
 *          The index of section
 *
 *  Return:
 *          index(Name Matched)
 *          -1 (Not Matched)
 *
 ******************************************************************************/
int getIndexOfSectionByName(ElfData *dataFromElf, char *name){
  int index;
  
  dataFromElf->programElf = getAllSectionInfo(dataFromElf); 
  
  for(index = 0; index < dataFromElf->eh->e_shnum; index++){
    if(strcmp(dataFromElf->programElf[index].name , name) == 0){
      return index;
    }
  }
  
  return -1;
}

/******************************************************************************
 * Get Section Address From Section Index
 *
 *  Operation:
 *          To get the address of section in function getAllSectionInfo from  
 *          the section index
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Section index)
 *  
 *  Data:
 *          The address of section
 *
 *  Return:
 *          secAddress
 *
 ******************************************************************************/
int getSectionAddress(ElfData *dataFromElf, int index){
  int secAddress;
 
  dataFromElf->programElf = getAllSectionInfo(dataFromElf); 
  
  secAddress = (int)dataFromElf->programElf[index].section;
  
  return secAddress;
}

/******************************************************************************
 * Get Section Size From Section Index
 *
 *  Operation:
 *          To get the size of section in section header from the section 
 *          index
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Section index)
 *  
 *  Data:
 *          The size of section
 *
 *  Return:
 *          sectionSize
 *
 ******************************************************************************/
int getSectionSize(ElfData *dataFromElf, int index){
  int sectionSize;
  sectionSize = dataFromElf->sh[index].sh_size;
  
  return sectionSize;
}

/******************************************************************************
 * Get Physical Address From Program Header Index
 *
 *  Operation:
 *          To get the physical address in program header from the program 
 *          header index
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Section index)
 *  
 *  Data:
 *          The physical address
 *
 *  Return:
 *          phyAddr
 *
 ******************************************************************************/
uint32_t getSectionPhysicalAddress(ElfData *dataFromElf, int index){
  uint32_t phyAddr;
  
  phyAddr = dataFromElf->ph[index].p_paddr;
  
  return phyAddr;
}

/******************************************************************************
 * Get Virtual Address From Program Header Index
 *
 *  Operation:
 *          To get the virtual address in program header from the program 
 *          header index
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Section index)
 *  
 *  Data:
 *          The virtual address
 *
 *  Return:
 *          virAddr
 *
 ******************************************************************************/
uint32_t getSectionVirtualAddress(ElfData *dataFromElf, int index){
  uint32_t virAddr;
  
  virAddr = dataFromElf->ph[index].p_vaddr;
  
  return virAddr;
}

/******************************************************************************
 * Section Executable Check
 *
 *  Operation:
 *          To check the program header available for executable from flag
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Program Header index)
 *
 *  Return:
 *          1(Available)
 *          0(Not Available)
 *
 ******************************************************************************/
int isSectionExecutable(ElfData *dataFromElf, int index){
  int flag;
  flag = dataFromElf->ph[index].p_flags;
  
  if((flag & PF_X) == 1){
    return 1;
  }else{
    return 0;
  }
}

/******************************************************************************
 * Section Writeable Check
 *
 *  Operation:
 *          To check the program header available for writeable from flag
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Program Header index)
 *
 *  Return:
 *          1(Available)
 *          0(Not Available)
 *
 ******************************************************************************/
int isSectionWriteable(ElfData *dataFromElf, int index){
  int flag;
  flag = dataFromElf->ph[index].p_flags;
  
  if((flag & PF_W) == 2){
    return 1;
  }else{
    return 0;
  }
}

/******************************************************************************
 * Section Readable Check
 *
 *  Operation:
 *          To check the program header available for readable from flag
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Program Header index)
 *
 *  Return:
 *          1(Available)
 *          0(Not Available)
 *
 ******************************************************************************/
int isSectionReadable(ElfData *dataFromElf, int index){
  int flag;
  flag = dataFromElf->ph[index].p_flags;
  
  if((flag & PF_R) == 4){
    return 1;
  }else{
    return 0;
  }
}

/******************************************************************************
 * Get Symbol Table Size From Name
 *
 *  Operation:
 *          To get symbol table size by moving the pointer to sh[i].sh_offset 
 *          plus st[j].st_name
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          name(Symbol Table name)
 *  
 *  Data:
 *          The size of symbol table
 *
 *  Return:
 *          st[j].st_size(Matched)
 *          -1(Not matched)
 *
 ******************************************************************************/
uint32_t getSymbolTableSizeUsingName(ElfData *dataFromElf, char *name){
  char *SectNames;
  int i, j;
  
  for(i = 0; i < dataFromElf->eh->e_shnum - 1; i++);
  SectNames = malloc(dataFromElf->sh[i].sh_size);

  for(j = 0; j < 290; j++){
    inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[i].sh_offset + dataFromElf->st[j].st_name);
    fread(SectNames, dataFromElf->sh[i].sh_size, 1, dataFromElf->myFile->file);
    if(strcmp(SectNames , name) == 0){
      return dataFromElf->st[j].st_size;
    }
  }
  
  return -1;
}

/******************************************************************************
 * Get Symbol Table Address From Name
 *
 *  Operation:
 *          To get symbol table address by moving the pointer to sh[i].sh_offset 
 *          plus st[j].st_name
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          name(Symbol Table name)
 *  
 *  Data:
 *          The address of symbol table
 *
 *  Return:
 *          st[j].st_value(Matched)
 *          -1(Not matched)
 *
 ******************************************************************************/
uint32_t getSymbolTableAddressUsingName(ElfData *dataFromElf, char *name){
  char *SectNames;
  int i, j;
  
  for(i = 0; i < dataFromElf->eh->e_shnum - 1; i++);
  SectNames = malloc(dataFromElf->sh[i].sh_size);

  for(j = 0; j < 290; j++){
    inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[i].sh_offset + dataFromElf->st[j].st_name);
    fread(SectNames, dataFromElf->sh[i].sh_size, 1, dataFromElf->myFile->file);
    if(strcmp(SectNames , name) == 0){
      return dataFromElf->st[j].st_value;
    }
  }
  
  return -1;
}

/******************************************************************************
 * Relocation
 *
 *  Operation:
 *          To read the information in the Relocation by moving the file
 *          pointer to the sh_offset(Relocation_Offset) in the Elf32_Shdr
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *  
 *  Data:
 *          Information of the Relation allocate in the structure 
 *          of Elf32_Sym
 *
 *  Return:
 *          rel
 *          (The structure of Elf32_Rel)
 *
 ******************************************************************************/
Elf32_Rel *getRelocation(ElfData *dataFromElf){
  int i, rel_Entries, sizeToMalloc;
  
  for(i = 0; dataFromElf->sh[i].sh_type != SHT_REL; i++);
  rel_Entries = dataFromElf->sh[i].sh_size / 8;
  sizeToMalloc = rel_Entries * sizeof(Elf32_Rel);
  dataFromElf->rel = malloc(sizeToMalloc);
  
  inStreamMoveFilePtr(dataFromElf->myFile, dataFromElf->sh[i].sh_offset);
  fread(dataFromElf->rel, sizeToMalloc, 1, dataFromElf->myFile->file);

  return dataFromElf->rel;
}

/******************************************************************************
 * Get Relocation Symbol Name
 *
 *  Operation:
 *          To get the symbol name in the Relocation 
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Relocation index)
 *  
 *  Data:
 *          Symbol name of relocation
 *
 *  Return:
 *          dataFromElf->programElf
 *          (symbol name)
 *
 ******************************************************************************/
char *getRelSymbolName(ElfData *dataFromElf, int index){
  int symbolIndex, sectIndex;

  symbolIndex = ELF32_R_SYM(dataFromElf->rel[index].r_info);
  sectIndex = dataFromElf->st[symbolIndex].st_shndx;
  
  dataFromElf->programElf = (_Elf32_Shdr *)getSectionInfoNameUsingIndex(dataFromElf, sectIndex);
  
  return (char *)dataFromElf->programElf;
}

/******************************************************************************
 * Get Relocation Type
 *
 *  Operation:
 *          To get the type in the Relocation 
 *
 *  Input:
 *          dataFromElf(ElfData structure)
 *          index(Relocation index)
 *  
 *  Data:
 *          Type of relocation
 *
 *  Return:
 *          sectType
 *          (relocation type)
 *
 ******************************************************************************/
uint32_t getRelType(ElfData *dataFromElf, int index){
  int sectType;
  
  sectType = ELF32_R_TYPE(dataFromElf->rel[index].r_info);
  
  return sectType;
}


