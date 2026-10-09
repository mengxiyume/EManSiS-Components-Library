#pragma once

/*
 *  0x00100000
 *  ...->异常编号段
 *  0x001FFFFF
*/
#pragma region error identify
#define IDE_EXCEPTION_LOW           0x00100000
#define IDE_EXCEPTION_HEI           0x001FFFFF
#define IDE_EXCEPTION_UNIT_WITH     0x00001000
#define IDE_EXCEPTION_UNIT(_OFFSET_) ((IDE_EXCEPTION_UNIT_WITH) * (_OFFSET_))
#define IDE_EXCEPTION(_OFFSET_) ((IDE_EXCEPTION_LOW) + (_OFFSET_))
/*
    *  0x00100000
    *  ...->异常保留字段
    *  0x00100FFF
    */
    #pragma region error retained
    #define IDE_EXCEPTION_RETAINED_LOW   IDE_EXCEPTION_UNIT(0x00)
    #define IDE_EXCEPTION_RETAINED_HEI   ((IDE_EXCEPTION_RETAINED_LOW) + (IDE_EXCEPTION_UNIT_WITH) - 1)
    #define IDE_EXCEPTION_RETAINED(_OFFSET_) (IDE_EXCEPTION((IDE_EXCEPTION_RETAINED_LOW) + (_OFFSET_)))

        #define IDE_UNKNOWN_EXCEPTION IDE_EXCEPTION_RETAINED(IDE_EXCEPTION_RETAINED_HEI)

    #pragma endregion

    /*
    *  0x00101000
    *  ...->指针异常段
    *  0x00101FFF
    */
    #pragma region error pointer
    #define IDE_EXCEPTION_POINTER_LOW   IDE_EXCEPTION_UNIT(0x01)
    #define IDE_EXCEPTION_POINTER_HEI   ((IDE_EXCEPTION_POINTER_LOW) + (IDE_EXCEPTION_UNIT_WITH) - 1)
    #define IDE_EXCEPTION_POINTER(_OFFSET_) (IDE_EXCEPTION((IDE_EXCEPTION_POINTER_LOW) + (_OFFSET_)))

        #define IDE_EXCEPTION_POINTER_NULLPOINTER IDE_EXCEPTION_POINTER(0x0)

    #pragma endregion

    /*
    *  0x00102000
    *  ...->随机数异常段
    *  0x00102FFF
    */
    #pragma region error random
    #define IDE_EXCEPTION_RANDOM_LOW   IDE_EXCEPTION_UNIT(0x02)
    #define IDE_EXCEPTION_RANDOM_HEI   ((IDE_EXCEPTION_RANDOM_LOW) + (IDE_EXCEPTION_UNIT_WITH) - 1)
    #define IDE_EXCEPTION_RANDOM(_OFFSET_) (IDE_EXCEPTION((IDE_EXCEPTION_RANDOM_LOW) + (_OFFSET_)))

        #define IDE_EXCEPTION_RANDOM_SEED_OF_ZERO IDE_EXCEPTION_RANDOM(0x0)
        
    #pragma endregion

    /*
    *  0x00103000 
    *  ...->位图异常段
    * 0x00103FFF
    */
    #pragma region error bitmap
    #define IDE_EXCEPTION_BITMAP_LOW   IDE_EXCEPTION_UNIT(0x03)
    #define IDE_EXCEPTION_BITMAP_HEI   ((IDE_EXCEPTION_BITMAP_LOW) + (IDE_EXCEPTION_UNIT_WITH) - 1)
    #define IDE_EXCEPTION_BITMAP(_OFFSET_) (IDE_EXCEPTION((IDE_EXCEPTION_BITMAP_LOW) + (_OFFSET_)))

        #define IDE_EXCEPTION_BITMAP_OUT_OF_RANGE IDE_EXCEPTION_BITMAP(0x0) 

    #pragma endregion
    
#pragma endregion