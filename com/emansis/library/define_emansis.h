#pragma once

#include <cstdio>
#include <utility>

#ifndef VTOA_BUFFER_EMANSIS
    #ifndef VTOA_BUFFER_SIZE_EMANSIS
    #define VTOA_BUFFER_SIZE_EMANSIS 64
    char emansis_g_bufferVtoABufr[VTOA_BUFFER_SIZE_EMANSIS] = "\0";
    #define VTOA_BUFFER_EMANSIS (emansis_g_bufferVtoABufr)
    #endif
#endif

#ifndef PATCH_VAR_NAME_EMANSIS
#define PATCH_VAR_NAME_EMANSIS(_VAR_) (""#_VAR_"")
#endif

#ifndef VTOSTR_EMANSIS
#define VTOSTR_EMANSIS(_VAR_, _FORMATE_TAG_) (sprintf(VTOA_BUFFER_EMANSIS, "%lld", _VAR_), (const char*)VTOA_BUFFER_EMANSIS)

    #ifndef STR_INT64_VAR_EMANSIS
    #define STR_INT64_VAR_EMANSIS(_VAR_) (""VTOSTR_EMANSIS(_VAR_, "0x%llX")"")
    #endif
    #ifndef STR_INT32_VAR_EMANSIS
    #define STR_INT32_VAR_EMANSIS(_VAR_) (""VTOSTR_EMANSIS(_VAR_, "0x%X")"")
    #endif
    #ifndef STR_INT16_VAR_EMANSIS
    #define STR_INT16_VAR_EMANSIS(_VAR_) (""VTOSTR_EMANSIS(_VAR_, "0x%hX")"")
    #endif
    #ifndef STR_INT8_VAR_EMANSIS
    #define STR_INT8_VAR_EMANSIS(_VAR_) (""VTOSTR_EMANSIS(_VAR_, "0x%hhX")"")
    #endif
    #ifndef STR_FP64_VAR_EMANSIS
    #define STR_FP64_VAR_EMANSIS(_VAR_) (""VTOSTR_EMANSIS(_VAR_, "%llF")"")
    #endif
    #ifndef STR_FP32_VAR_EMANSIS
    #define STR_FP32_VAR_EMANSIS(_VAR_) (""VTOSTR_EMANSIS(_VAR_, "%lF")"")
    #endif

#endif

#define BITSIZE_BYTE 8
#define BITSIZE(_VAR_) (sizeof(_VAR_) * BITSIZE_BYTE)

#define UNMASK_BIT64_FULL_TRUE  ((unsigned long long)0xFFFFFFFFFFFFFFFF)
#define UNMASK_BIT64_FULL_FALSE ((unsigned long long)0x0000000000000000)

#define UNMASK_BIT32_FULL_TRUE  ((unsigned int)0xFFFFFFFF)
#define UNMASK_BIT32_FULL_FALSE ((unsigned int)0x00000000)

#define UNMASK_BIT16_FULL_TRUE  ((unsigned short)0xFFFF)
#define UNMASK_BIT16_FULL_FALSE ((unsigned short)0x0000)

#define UNMASK_BIT8_FULL_TRUE   ((unsigned char)0xFF)
#define UNMASK_BIT8_FULL_FALSE  ((unsigned char)0x00)