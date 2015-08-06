#include "unity.h"
#include "GetHeaders.h"
#include "Read_File.h"
#include "CException.h"
#include "ErrorCode.h"
#include "ProgramElf.h"
#include <stdlib.h>
#include "Relocator.h"

void setUp(void){}

void tearDown(void){}

/*******************************************************************
 *
 *                  Info and Offset of Relocation
 *
 *******************************************************************/
void test_getRelocation(void){
  ElfData dataFromElf;
  dataFromElf.myFile = openFile("test/Relocation_File/add.o", "rb+");
  dataFromElf.eh = getElfHeader(&dataFromElf);
  dataFromElf.sh = getSectionHeaders(&dataFromElf);
  dataFromElf.rel = getRelocation(&dataFromElf);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000006, dataFromElf.rel[0].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000702, dataFromElf.rel[0].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000000c, dataFromElf.rel[1].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000a02, dataFromElf.rel[1].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000011, dataFromElf.rel[2].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000a02, dataFromElf.rel[2].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x00000015, dataFromElf.rel[3].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000202, dataFromElf.rel[3].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000001d, dataFromElf.rel[4].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000902, dataFromElf.rel[4].r_info);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000002c, dataFromElf.rel[5].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x00000202, dataFromElf.rel[5].r_info);
  
  closeFileInTxt(dataFromElf.myFile);
}

// get Relocate symbol
void test_getRelSymbol_with_index_0(void){
  ElfData dataFromElf;
  dataFromElf.myFile = openFile("test/Relocation_File/add.o", "rb+");
  dataFromElf.eh = getElfHeader(&dataFromElf);
  dataFromElf.sh = getSectionHeaders(&dataFromElf);
  dataFromElf.rel = getRelocation(&dataFromElf);
  dataFromElf.st = getSymbolTables(&dataFromElf);
  
  TEST_ASSERT_EQUAL_STRING(".debug_abbrev", getRelSymbolName(&dataFromElf, 0));
  
  closeFileInTxt(dataFromElf.myFile);
}

void test_getRelSymbol_with_index_3(void){
  ElfData dataFromElf;
  dataFromElf.myFile = openFile("test/Relocation_File/add.o", "rb+");
  dataFromElf.eh = getElfHeader(&dataFromElf);
  dataFromElf.sh = getSectionHeaders(&dataFromElf);
  dataFromElf.rel = getRelocation(&dataFromElf);
  dataFromElf.st = getSymbolTables(&dataFromElf);
  
  TEST_ASSERT_EQUAL_STRING(".text", getRelSymbolName(&dataFromElf, 3));
  
  closeFileInTxt(dataFromElf.myFile);
}

// get Relocate type
void test_getRelType_with_index_1_should_return_R_ARM_ABS32(void){
  ElfData dataFromElf;
  dataFromElf.myFile = openFile("test/Relocation_File/add.o", "rb+");
  dataFromElf.eh = getElfHeader(&dataFromElf);
  dataFromElf.sh = getSectionHeaders(&dataFromElf);
  dataFromElf.rel = getRelocation(&dataFromElf);
  
  TEST_ASSERT_EQUAL(R_ARM_ABS32, getRelType(&dataFromElf, 1));
  
  closeFileInTxt(dataFromElf.myFile);
}

void test_generateBLInstruction_with_bl(void){
  ElfData dataFromElf;
  dataFromElf.myFile = openFile("test/Relocation_File/main.o", "rb+");
  dataFromElf.eh = getElfHeader(&dataFromElf);
  dataFromElf.sh = getSectionHeaders(&dataFromElf);
  dataFromElf.rel = getRelocation(&dataFromElf);
  
  uint32_t *blInstruction = generateBLInstruction(&dataFromElf, ".text");
  TEST_ASSERT_EQUAL_HEX32(0xf7fffffe, blInstruction[0]);
  
  closeFileInTxt(dataFromElf.myFile);
}

void test_extractBlArguments_from_bl(void){
  ElfData dataFromElf;
  dataFromElf.myFile = openFile("test/Relocation_File/main.o", "rb+");
  dataFromElf.eh = getElfHeader(&dataFromElf);
  dataFromElf.sh = getSectionHeaders(&dataFromElf);
  dataFromElf.rel = getRelocation(&dataFromElf);
  
  BlArguments blArgs;
  uint32_t addressToCall;
  addressToCall = extractBlArguments(&dataFromElf, &blArgs);
  
  TEST_ASSERT_EQUAL_HEX32(0x01fffffc, addressToCall);
  
  closeFileInTxt(dataFromElf.myFile);
}



