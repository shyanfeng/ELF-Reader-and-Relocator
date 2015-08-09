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
  ElfData *elfData = openElfFile("test/Relocation_File/add.o");
  elfData->rel = getRelocation(elfData);
  
  TEST_ASSERT_EQUAL_HEX32(0x0000002c, elfData->rel[0].r_offset);
  TEST_ASSERT_EQUAL_HEX32(0x0000110a, elfData->rel[0].r_info);
  
  closeFileInTxt(elfData->myFile);
}


// get Relocate symbol
void test_getRelSymbol_with_index_0(void){
  ElfData *elfData = openElfFile("test/Relocation_File/add.o");
  elfData->rel = getRelocation(elfData);
  
  TEST_ASSERT_EQUAL_STRING("minus", getRelSymbolName(elfData, 0));
  
  closeFileInTxt(elfData->myFile);
}

// get Relocate type
void test_getRelType_with_index_1_should_return_R_ARM_ABS32(void){
  ElfData *elfData = openElfFile("test/Relocation_File/add.o");
  elfData->rel = getRelocation(elfData);
  
  TEST_ASSERT_EQUAL(R_ARM_THM_CALL, getRelType(elfData, 0));
  
  closeFileInTxt(elfData->myFile);
}

void test_generateBLInstruction_with_bl(void){
  ElfData *elfData = openElfFile("test/Relocation_File/add.o");
  elfData->rel = getRelocation(elfData);
  
  uint32_t *blInstruction = generateBLInstruction(elfData, ".text");
  TEST_ASSERT_EQUAL_HEX32(0xf7fffffe, blInstruction[0]);
  
  closeFileInTxt(elfData->myFile);
}


void test_extractBlArguments_from_bl(void){
  ElfData *elfData = openElfFile("test/Relocation_File/add.o");
  elfData->rel = getRelocation(elfData);
  
  BlArguments blArgs;
  uint32_t addressToCall;
  addressToCall = extractBlArguments(elfData, &blArgs);
  
  TEST_ASSERT_EQUAL_HEX32(0x01fffffc, addressToCall);
  
  closeFileInTxt(elfData->myFile);
}



 
 

