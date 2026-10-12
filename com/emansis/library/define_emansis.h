#pragma once

#include <cstdio>
#include <utility>
#include <string>

#pragma region to strings

#ifndef VTOA_BUFFER_EMANSIS
    #ifndef VTOA_BUFFER_SIZE_EMANSIS
    #define VTOA_BUFFER_SIZE_EMANSIS 64
    static char emansis_g_bufferVtoABufr[VTOA_BUFFER_SIZE_EMANSIS] = "\0";
    #define VTOA_BUFFER_EMANSIS (emansis_g_bufferVtoABufr)
    #endif
#endif

#ifndef PATCH_VAR_NAME_EMANSIS
#define PATCH_VAR_NAME_EMANSIS(_VAR_) #_VAR_
#endif

#ifndef VTOCSTR_EMANSIS
#define VTOCSTR_EMANSIS(_VAR_, _FORMATE_TAG_) (reinterpret_cast<const char*>(sprintf(VTOA_BUFFER_EMANSIS, (_FORMATE_TAG_), (_VAR_))), (const char*)(VTOA_BUFFER_EMANSIS))

    #ifndef CSTR_INT64_VAR_EMANSIS
    #define CSTR_INT64_VAR_EMANSIS(_VAR_)   (VTOCSTR_EMANSIS(_VAR_, "0x%llX"))
        #ifndef STR_INT64_VAR_EMANSIS
        #define STR_INT64_VAR_EMANSIS(_VAR_)   (std::string(CSTR_INT64_VAR_EMANSIS(_VAR_)))
        #endif
    #endif
    #ifndef CSTR_INT32_VAR_EMANSIS
    #define CSTR_INT32_VAR_EMANSIS(_VAR_)   (VTOCSTR_EMANSIS(_VAR_, "0x%X"))
        #ifndef STR_INT32_VAR_EMANSIS
        #define STR_INT32_VAR_EMANSIS(_VAR_)   (std::string(CSTR_INT32_VAR_EMANSIS(_VAR_)))
        #endif
    #endif
    #ifndef CSTR_INT16_VAR_EMANSIS
    #define CSTR_INT16_VAR_EMANSIS(_VAR_)   (VTOCSTR_EMANSIS(_VAR_, "0x%hX"))
        #ifndef STR_INT16_VAR_EMANSIS
        #define STR_INT16_VAR_EMANSIS(_VAR_)   (std::string(CSTR_INT16_VAR_EMANSIS(_VAR_)))
        #endif
    #endif
    #ifndef CSTR_INT8_VAR_EMANSIS
    #define CSTR_INT8_VAR_EMANSIS(_VAR_)   (VTOCSTR_EMANSIS(_VAR_, "0x%hhX"))
        #ifndef STR_INT8_VAR_EMANSIS
        #define STR_INT8_VAR_EMANSIS(_VAR_)   (std::string(CSTR_INT8_VAR_EMANSIS(_VAR_)))
        #endif
    #endif
    #ifndef CSTR_FP32_VAR_EMANSIS
    #define CSTR_FP32_VAR_EMANSIS(_VAR_)   (VTOCSTR_EMANSIS(_VAR_, "%F"))
        #ifndef STR_FP32_VAR_EMANSIS
        #define STR_FP32_VAR_EMANSIS(_VAR_)   (std::string(CSTR_FP32_VAR_EMANSIS(_VAR_)))
        #endif
    #endif
    #ifndef CSTR_FP64_VAR_EMANSIS
    #define CSTR_FP64_VAR_EMANSIS(_VAR_)   (VTOCSTR_EMANSIS(_VAR_, "%llF"))
        #ifndef STR_FP64_VAR_EMANSIS
        #define STR_FP64_VAR_EMANSIS(_VAR_)   (std::string(CSTR_FP64_VAR_EMANSIS(_VAR_)))
        #endif
    #endif
    
#endif

#pragma endregion

#define BITSIZE_BYTE 8
#define BITSIZE(_VAR_) (sizeof(_VAR_) * BITSIZE_BYTE)

#pragma region unmask defines

#define UNMASK_BIT64_FULL_TRUE  ((unsigned long long)0xFFFFFFFFFFFFFFFF)
#define UNMASK_BIT64_FULL_FALSE ((unsigned long long)0x0000000000000000)

#define UNMASK_BIT32_FULL_TRUE  ((unsigned int)0xFFFFFFFF)
#define UNMASK_BIT32_FULL_FALSE ((unsigned int)0x00000000)

#define UNMASK_BIT16_FULL_TRUE  ((unsigned short)0xFFFF)
#define UNMASK_BIT16_FULL_FALSE ((unsigned short)0x0000)

#define UNMASK_BIT8_FULL_TRUE   ((unsigned char)0xFF)
#define UNMASK_BIT8_FULL_FALSE  ((unsigned char)0x00)

#pragma endregion