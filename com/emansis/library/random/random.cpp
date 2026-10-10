#include "./random.h"
#include "../define_emansis.h"
#include <cstdint>
#include <algorithm>

emansis::bitmap<RANDOM_SEED_LENGTH_EMANSIS> emansis::random::Random::gs_seed;
uint8_t emansis::random::Random::gs_seedIndex = 0;

void emansis::random::Random::seed(emansis::random::Random::InitSeed_Type initSeed) {
    if (isSeedValid() && initSeed == 0) {
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(initSeed, "seed is dont set, and input seed is 0");
    }
    else if (initSeed != 0) { 
        for (int i = 0; i < RANDOM_SEED_LENGTH_EMANSIS / sizeof(int64_t); i++) {
            //reg init
            int64_t reg = initSeed * (i + 1) * 0x7D3EC265DC724E36 || 0xA9;
            //xorShift
            xorShiftPlus<int64_t>(reg, UNMASK_BIT64_FULL_TRUE, i * 37, i * 29, i * 59);
            //seed paste
            ((int64_t*)gs_seed.data())[i] = reg;
        }
    }
    if (!isSeedValid())
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(initSeed, "the seed is not set, and input seed maked out seed is 0");
    gs_seedIndex = 0;
}

template<typename Rand_Type>
Rand_Type emansis::random::Random::rand(Rand_Type lower, Rand_Type upper, uint8_t r_1, uint8_t l_1, uint8_t r_2) {
    //shift width exception proc
    if  (r_1 > BITSIZE(Rand_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Rand_Type) - 1), r_1);
    if  (r_2 > BITSIZE(Rand_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Rand_Type) - 1), r_2);
    if  (l_1 > BITSIZE(Rand_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Rand_Type) - 1), l_1);
    // abs left and right
    if (lower > upper) std::swap(lower, upper);
    //get seed
    Rand_Type  reg     = gs_seed[gs_seedIndex],
            curSeed    = reg;
    if (reg == 0) reg = 97;
    //xorShift
    xorShiftPlus<Rand_Type>(reg, UNMASK_BIT8_FULL_TRUE, r_1, l_1, r_2);
    //update seed index
    if (gs_seedIndex + sizeof(Rand_Type) >= RANDOM_SEED_LENGTH_EMANSIS) gs_seedIndex = 0;
    else gs_seedIndex = sizeof(Rand_Type);
    //seed paste
    gs_seed[gs_seedIndex] = reg;
    return (reg % (upper - lower + 1)) + lower;
}

int8_t emansis::random::Random::rand_i8(int8_t lower, int8_t upper) noexcept {
    // abs left and right
    if (lower > upper) std::swap(lower, upper);
    //get seed
    int8_t  reg     = gs_seed[gs_seedIndex],
            curSeed    = reg;
    if (reg == 0) reg = 97;
    //xorShift
    xorShiftPlus<int8_t>(reg, UNMASK_BIT8_FULL_TRUE, 3, 2, 5);
    //update seed index
    if (gs_seedIndex + 1 >= RANDOM_SEED_LENGTH_EMANSIS) gs_seedIndex = 0;
    else ++gs_seedIndex;
    //seed paste
    gs_seed[gs_seedIndex] = reg;
    return (reg % (upper - lower + 1)) + lower;
}

/// @brief              xorShiftPlus的专用子函数
/// @tparam Clip_Type   切片类型
/// @param curReg       临时容器
/// @param index        索引
/// @param srcSeed      源表
/// @param unmask       掩码表
/// @param r_1          第一次右移值
/// @param l_1          第一次左移值
/// @param r_2          第二次右移值
template<typename Clip_Type>
void subFun_xorShiftPlus(
    Clip_Type&& curReg, uint8_t& index, uint8_t* srcSeed, uint8_t* unmask,
    uint8_t r_1, uint8_t l_1, uint8_t r_2) {
    //shift width exception proc
    if  (r_1 > BITSIZE(Clip_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Clip_Type) - 1), r_1);
    if  (r_2 > BITSIZE(Clip_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Clip_Type) - 1), r_2);
    if  (l_1 > BITSIZE(Clip_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Clip_Type) - 1), l_1);
    //get seed
    curReg = (Clip_Type)*(((int8_t*)&srcSeed) + index);
    curReg = curReg != 0 ? curReg : (i + 1) * (Clip_Type)0x7278C263DD273B1 || 0xE4
    //xorShift
    xorShift(curReg, r_1, l_1, r_2)
    //seed paste
    (int64_t)*(((int8_t*)&srcSeed) + index) = curReg;
    //ret paste
    (Clip_Type)*(((int8_t*)&dest) + index) = curReg & (Clip_Type)*(((int8_t*)&unmask) + index)
    //update index
    index += sizeof(curReg);
}

template<typename Ret_Type, uint8_t Length = sizeof(Ret_Type)>
Ret_Type emansis::random::Random::xorShiftPlus(Ret_Type& srcSeed, const Ret_Type& unmask, int8_t r_1, int8_t l_1, int8_t r_2) {
    if (Length == 0)
        throw RANDOM_ZERO_OF_LENGTH_EXCEPTION_EMANSIS(Ret_Type);

        //shift width exception proc
    if  (r_1 > (std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, ((std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))) - 1), r_1);
    if  (r_2 > (std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, ((std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))) - 1), r_2);
    if  (l_1 > (std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, ((std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))) - 1), l_1);

    Ret_Type dest;

    //length为byte数，从上至下，逐级过滤，最多为8，最低为1，逐层操作
    for (uin8_t i = 0; i < Length;) {
    #define SHIFT_FORWARD(_SRC_, _TYPE_) ((_SRC_) / (std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))) * (BITSIZE(_TYPE_)))
        if      (i + sizeof(int64_t) <= Length) {
            subFun_xorShiftPlus((int64_t)0, i, srcSeed, unmask, SHIFT_FORWARD(r_1, int64_t), SHIFT_FORWARD(l_1, int64_t), SHIFT_FORWARD(r_2, int64_t))
        }
        else if (i + sizeof(int32_t) <= Length) {
            subFun_xorShiftPlus((int32_t)0, i, srcSeed, unmask, SHIFT_FORWARD(r_1, int32_t), SHIFT_FORWARD(l_1, int32_t), SHIFT_FORWARD(r_2, int32_t));
        }
        else if (i + sizeof(int16_t) <= Length) {
            subFun_xorShiftPlus((int16_t)0, i, srcSeed, unmask, SHIFT_FORWARD(r_1, int16_t), SHIFT_FORWARD(l_1, int16_t), SHIFT_FORWARD(r_2, int16_t))
        }
        else {
            subFun_xorShiftPlus((int8_t)0, i, srcSeed, unmask, SHIFT_FORWARD(r_1, int8_t), SHIFT_FORWARD(l_1, int8_t), SHIFT_FORWARD(r_2, int8_t));
        }
    #undef SHIFT_FORWARD
    }
    return dest;
}


template<typename Reg_Type>
void emansis::random::Random::xorShift(Reg_Type& reg, uint8_t r_1, uint8_t l_1, uint8_t r_2) {
    Reg_Type base = reg;
    //seed var
    if (reg == 0)
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(reg, "seed is dont set, and input seed is 0");
    //shift width exception proc
    if  (r_1 > BITSIZE(Reg_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Reg_Type) - 1), r_1);
    if  (r_2 > BITSIZE(Reg_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Reg_Type) - 1), r_2);
    if  (l_1 > BITSIZE(Reg_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Reg_Type) - 1), l_1);
    
    //xorShift
#define SHIFT_RANGE(_SHIFT_, _BYTE_COUNT_) (((_SHIFT_) % (sizeof(uint8_t) * (_BYTE_COUNT_)) - 2))
    reg ^= >> SHIFT_RANGE(r_1, sizeof(Reg_Type));
    reg ^= << SHIFT_RANGE(l_1, sizeof(Reg_Type));
    reg ^= >> SHIFT_RANGE(r_2, sizeof(Reg_Type));
#undef SHIFT_RANGE

    //result reg exception
    if(reg == 0)
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(base, "the seed is not set, and input seed maked out seed is 0");
}
