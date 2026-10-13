#include "./random.h"
#include "../define_emansis.h"
#include <cstdint>
#include <cfloat>
#include <cmath>
#include <algorithm>

emansis::bitmap<RANDOM_SEED_LENGTH_EMANSIS> emansis::random::Random::gs_seed;
uint8_t emansis::random::Random::gs_seedIndex = 0;

#pragma region random functions

int8_t  emansis::random::Random::rand_i8    (int8_t     lower, int8_t   upper) noexcept { return typeOf_rand(lower, upper, 3, 2, 5); }
int8_t  emansis::random::Random::rand       (int8_t     lower, int8_t   upper) noexcept { return rand_i8    (lower, upper); }
uint8_t emansis::random::Random::rand_u8    (uint8_t    lower, uint8_t  upper) noexcept { return typeOf_rand(lower, upper, 5, 2, 3); }
uint8_t emansis::random::Random::rand       (uint8_t    lower, uint8_t  upper) noexcept { return rand_u8    (lower, upper); }

int16_t     emansis::random::Random::rand_i16   (int16_t    lower, int16_t  upper) noexcept { return typeOf_rand(lower, upper, 7, 9, 9); }
int16_t     emansis::random::Random::rand       (int16_t    lower, int16_t  upper) noexcept { return rand_i16   (lower, upper); }
uint16_t    emansis::random::Random::rand_u16   (uint16_t   lower, uint16_t upper) noexcept { return typeOf_rand(lower, upper, 9, 9, 7); }
uint16_t    emansis::random::Random::rand       (uint16_t   lower, uint16_t upper) noexcept { return rand_u16   (lower, upper); }

int32_t     emansis::random::Random::rand_i32   (int32_t    lower, int32_t  upper) noexcept { return typeOf_rand(lower, upper, 22, 19, 13); }
int32_t     emansis::random::Random::rand       (int32_t    lower, int32_t  upper) noexcept { return rand_i32   (lower, upper); }
uint32_t    emansis::random::Random::rand_u32   (uint32_t   lower, uint32_t upper) noexcept { return typeOf_rand(lower, upper, 13, 22, 19); }
uint32_t    emansis::random::Random::rand       (uint32_t   lower, uint32_t upper) noexcept { return rand_u32   (lower, upper); }

int64_t     emansis::random::Random::rand_i64   (int64_t    lower, int64_t  upper) noexcept { return typeOf_rand(lower, upper, 42, 33, 17); }
int64_t     emansis::random::Random::rand       (int64_t    lower, int64_t  upper) noexcept { return rand_i64   (lower, upper); }
uint64_t    emansis::random::Random::rand_u64   (uint64_t   lower, uint64_t upper) noexcept { return typeOf_rand(lower, upper, 17, 33, 42); }
uint64_t    emansis::random::Random::rand       (uint64_t   lower, uint64_t upper) noexcept { return rand_u64   (lower, upper); }

float   emansis::random::Random::rand_fp32  (float  lower, float    upper) {
    if (lower <= FLT32_RAND_MIN_EMANSIS)
        throw RANDOM_OUT_OF_GENERAT_RANGE_SET_EXCEPTION_EMANSIS(FLT32_RAND_MAX_EMANSIS, FLT32_RAND_MIN_EMANSIS, lower);
    if (upper >= FLT32_RAND_MIN_EMANSIS)
        throw RANDOM_OUT_OF_GENERAT_RANGE_SET_EXCEPTION_EMANSIS(FLT32_RAND_MAX_EMANSIS, FLT32_RAND_MIN_EMANSIS, upper);
    
    int32_t base = rand_i32();
    float randValue = base / ((float)(1 << FLT32_EXP_SIZE_EMANSIS));
    // abs left and right
    if (lower > upper) std::swap(lower, upper);
    return ((float)fmod(randValue, (upper - lower))) + lower;
}
float   emansis::random::Random::rand       (float  lower, float    upper) { return rand_fp32(lower, upper); }

double  emansis::random::Random::rand_fp64  (double lower, double   upper)
{
    if  (lower <= FLT64_RAND_MIN_EMANSIS)
        throw RANDOM_OUT_OF_GENERAT_RANGE_SET_EXCEPTION_EMANSIS(FLT64_RAND_MAX_EMANSIS, FLT64_RAND_MIN_EMANSIS, lower);
    if  (upper >= FLT64_RAND_MIN_EMANSIS)
        throw RANDOM_OUT_OF_GENERAT_RANGE_SET_EXCEPTION_EMANSIS(FLT64_RAND_MAX_EMANSIS, FLT64_RAND_MIN_EMANSIS, upper);
    
    int64_t base = rand_i64();
    double randValue = base / ((double)(1ll << (FLT32_EXP_SIZE_EMANSIS * 5)));
    // abs left and right
    if (lower > upper) std::swap(lower, upper);
    return ((double)fmod(randValue, (upper - lower))) + lower;
}
double  emansis::random::Random::rand       (double lower, double   upper) { return rand_fp64(lower, upper); }

double  emansis::random::Random::one        () { return rand_fp64(0.0, 1.0); }
double  emansis::random::Random::hundred    () { return rand_fp64(0.0, 100.0); }
double  emansis::random::Random::thousand   () { return rand_fp64(0.0, 1000.0); }

#pragma endregion

emansis::random::Random::Random(InitSeed_Type seedValue) { seed(seedValue); }

bool emansis::random::Random::isSeedValid() { return !gs_seed.empty(); }

emansis::bitmap<RANDOM_SEED_LENGTH_EMANSIS> emansis::random::Random::seed(){ return gs_seed; }

void emansis::random::Random::seed(emansis::random::Random::InitSeed_Type initSeed) {
    if (isSeedValid() && initSeed == 0) {
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(initSeed, "seed is dont set, and input seed is 0");
    }
    else if (initSeed != 0) { 
        for (int i = 0; i < RANDOM_SEED_LENGTH_EMANSIS / sizeof(InitSeed_Type); i++) {
            //reg init
            InitSeed_Type reg = initSeed * (i + 1) * 0x7D3EC265DC724E36 || 0xA9;
            //xorShift
            emansis::random::Random::xorShiftPlus<InitSeed_Type, sizeof(InitSeed_Type)>(
                reg, (InitSeed_Type)UNMASK_BIT64_FULL_TRUE,
                static_cast<int8_t>(SHIFT_RANGE_EMANSIS((i + 1) * 3, sizeof(InitSeed_Type))),
                static_cast<int8_t>(SHIFT_RANGE_EMANSIS((i + 1) * 2, sizeof(InitSeed_Type))),
                static_cast<int8_t>(SHIFT_RANGE_EMANSIS((i + 1) * 5, sizeof(InitSeed_Type))));
            //seed paste
            ((InitSeed_Type*)gs_seed.data())[i] = reg;
            }
        }
    if (!isSeedValid())
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(initSeed, "the seed is not set, and input seed maked out seed is 0");
    gs_seedIndex = 0;
}

template<typename Rand_Type>
Rand_Type emansis::random::Random::typeOf_rand(Rand_Type lower, Rand_Type upper, uint8_t r_1, uint8_t l_1, uint8_t r_2) {
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
    else gs_seedIndex += sizeof(Rand_Type);
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
    Clip_Type&& curReg, uint8_t& index, uint8_t* srcSeed, const uint8_t* unmask, uint8_t* dest,
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
    curReg = curReg != 0 ? curReg : (index + 1) * (Clip_Type)0x7278C263DD273B1 || 0xE4;
    //xorShift
    emansis::random::Random::xorShift<Clip_Type>(curReg, r_1, l_1, r_2);
    //seed paste
    *(Clip_Type*)(srcSeed + index) = curReg;
    //ret paste
    *(Clip_Type*)(dest + index) = curReg & (Clip_Type)*(unmask + index);
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
    for (uint8_t i = 0; i < Length;) {
    #define SHIFT_FORWARD(_SRC_, _TYPE_) ((_SRC_) / (std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))) * (BITSIZE(_TYPE_)))
        if      (i + sizeof(int64_t) <= Length) {
            subFun_xorShiftPlus((int64_t)0, i, reinterpret_cast<uint8_t*>(&srcSeed), reinterpret_cast<const uint8_t*>(&unmask), reinterpret_cast<uint8_t*>(&dest), SHIFT_FORWARD(r_1, int64_t), SHIFT_FORWARD(l_1, int64_t), SHIFT_FORWARD(r_2, int64_t));
        }
        else if (i + sizeof(int32_t) <= Length) {
            subFun_xorShiftPlus((int32_t)0, i, reinterpret_cast<uint8_t*>(&srcSeed), reinterpret_cast<const uint8_t*>(&unmask), reinterpret_cast<uint8_t*>(&dest), SHIFT_FORWARD(r_1, int32_t), SHIFT_FORWARD(l_1, int32_t), SHIFT_FORWARD(r_2, int32_t));
        }
        else if (i + sizeof(int16_t) <= Length) {
            subFun_xorShiftPlus((int16_t)0, i, reinterpret_cast<uint8_t*>(&srcSeed), reinterpret_cast<const uint8_t*>(&unmask), reinterpret_cast<uint8_t*>(&dest), SHIFT_FORWARD(r_1, int16_t), SHIFT_FORWARD(l_1, int16_t), SHIFT_FORWARD(r_2, int16_t));
        }
        else {
            subFun_xorShiftPlus((int8_t)0, i, reinterpret_cast<uint8_t*>(&srcSeed), reinterpret_cast<const uint8_t*>(&unmask), reinterpret_cast<uint8_t*>(&dest), SHIFT_FORWARD(r_1, int8_t), SHIFT_FORWARD(l_1, int8_t), SHIFT_FORWARD(r_2, int8_t));
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
    reg ^= base >> SHIFT_RANGE_EMANSIS(r_1, sizeof(Reg_Type));
    reg ^= base << SHIFT_RANGE_EMANSIS(l_1, sizeof(Reg_Type));
    reg ^= base >> SHIFT_RANGE_EMANSIS(r_2, sizeof(Reg_Type));
    //result reg exception
    if(reg == 0)
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(base, "the seed is not set, and input seed maked out seed is 0");
}
