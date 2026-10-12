#include "./randomException.h"
#include "../exception/pointerException.h"
#include <iostream>

void throwException() {
    int i = 0;
    // throw NULL_POINTER_EXCEPTION_EMANSIS("233");
    // throw emansis::random::Exception(-1, "123", 0, "para", __FILE__, __LINE__);
    // throw emansis::random::RandomException(-1, "?", 0, __FILE__, __LINE__, std::string("123") + std::string("456"));
    // throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(0, 
    //     std::string("Max shift size[")  + STR_INT8_VAR_EMANSIS(i)   +
    //     std::string("] set")            + std::string(PATCH_VAR_NAME_EMANSIS(i))    +
    //     std::string(":[")               + STR_INT8_VAR_EMANSIS(i)   +
    //     std::string("]")                );

    // auto str1 = CSTR_INT8_VAR_EMANSIS(i);
    // auto str2 = (std::string(VTOCSTR_EMANSIS(100, "0x%hhX")).c_str());
    // const char* ch1 = "abc";

    //throw BITMAP_OUT_OF_RANGE_BITMAP_EXCEPTION_EMANSIS(323, 128);
    
    // throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(0, 100, i);
    // throw RANDOM_ZERO_OF_LENGTH_EXCEPTION_EMANSIS(void);
    // throw RANDOM_OUT_OF_GENERAT_RANGE_SET_EXCEPTION_EMANSIS(100.0, 0.0, 780.98);
}

void testException() {
    // try { throwException(); }

    // catch(emansis::exception::Exception& e) {
    //     std::cout << e.what() << std::endl;
    // }
}



void testRandom() {
    //TODO:test random functions
    std::cout << "111" << std::endl;

}

int main() {
    testRandom();
    testException();

    
    
}