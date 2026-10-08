#pragma once

/*
 *  0x00000000
 *  ...->保留字段
 *  0x000FFFFF
*/
#pragma region retained identify
#define ID_RETAINED_LOW         0x00000000
#define ID_RETAINED_HEI         0x000FFFFF
#define ID_RETAINED(_OFFSET_) ((ID_RETAINED_LOW) + (_OFFSET_))

    #define ID_UNKNOWN_ID ID_RETAINED(ID_RETAINED_HEI)

#pragma endregion