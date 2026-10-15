#include "./random.h"
#include "../define_emansis.h"
#include <cstdint>
#include <cfloat>
#include <cmath>
#include <algorithm>

#pragma region random functions

//TODO:重构，将所有类型的随机数生成都更改为u64的外层封装
//TODO:设计为计数模式，使用计数超过64位后立即对计数对其位置的种子进行xorshift,否则只增加计数并获取对应位置的种子

int8_t  emansis::random::Random::rand_i8    (int8_t     lower, int8_t   upper) noexcept { *((int8_t*)m_seed.data() + m_uUsedIndex) += 1; return typeOf_rand(lower, upper, static_cast<int8_t>UNMASK_BIT8_FULL_TRUE, 3, 2, 5); }
int8_t  emansis::random::Random::rand       (int8_t     lower, int8_t   upper) noexcept { return rand_i8    (lower, upper); }
uint8_t emansis::random::Random::rand_u8    (uint8_t    lower, uint8_t  upper) noexcept { *((uint8_t*)m_seed.data() + m_uUsedIndex) += 1; return typeOf_rand(lower, upper, static_cast<uint8_t>UNMASK_BIT8_FULL_TRUE, 3, 2, 5); }
uint8_t emansis::random::Random::rand       (uint8_t    lower, uint8_t  upper) noexcept { return rand_u8    (lower, upper); }

int16_t     emansis::random::Random::rand_i16   (int16_t    lower, int16_t  upper) noexcept { return typeOf_rand(lower, upper, static_cast<int16_t>UNMASK_BIT16_FULL_TRUE, 2, 1, 4); }
int16_t     emansis::random::Random::rand       (int16_t    lower, int16_t  upper) noexcept { return rand_i16   (lower, upper); }
uint16_t    emansis::random::Random::rand_u16   (uint16_t   lower, uint16_t upper) noexcept { return typeOf_rand(lower, upper, static_cast<uint16_t>UNMASK_BIT16_FULL_TRUE, 2, 1, 4); }
uint16_t    emansis::random::Random::rand       (uint16_t   lower, uint16_t upper) noexcept { return rand_u16   (lower, upper); }

int32_t     emansis::random::Random::rand_i32   (int32_t    lower, int32_t  upper) noexcept { *((int32_t*)(m_seed.data() + m_uUsedIndex)) *= 7; return typeOf_rand(lower, upper, static_cast<int32_t>UNMASK_BIT32_FULL_TRUE, 2, 4, 21); }
int32_t     emansis::random::Random::rand       (int32_t    lower, int32_t  upper) noexcept { return rand_i32   (lower, upper); }
uint32_t    emansis::random::Random::rand_u32   (uint32_t   lower, uint32_t upper) noexcept { *((uint32_t*)(m_seed.data() + m_uUsedIndex)) *= 7; return typeOf_rand(lower, upper, static_cast<uint32_t>UNMASK_BIT32_FULL_TRUE, 2, 4, 21); }
uint32_t    emansis::random::Random::rand       (uint32_t   lower, uint32_t upper) noexcept { return rand_u32   (lower, upper); }

int64_t     emansis::random::Random::rand_i64   (int64_t    lower, int64_t  upper) noexcept { *((int64_t*)(m_seed.data()) + m_uUsedIndex) *= 37; return typeOf_rand(lower, upper, static_cast<int64_t>UNMASK_BIT64_FULL_TRUE, 3, 25, 4); }
int64_t     emansis::random::Random::rand       (int64_t    lower, int64_t  upper) noexcept { return rand_i64   (lower, upper); }
uint64_t    emansis::random::Random::rand_u64   (uint64_t   lower, uint64_t upper) noexcept { *((uint64_t*)(m_seed.data()) + m_uUsedIndex) *= 37; return typeOf_rand(lower, upper, static_cast<uint64_t>UNMASK_BIT64_FULL_TRUE, 3, 25, 4); }
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

emansis::random::Random::Random(InitSeed_Type seedValue) : m_uUsedIndex(-1), m_uUpdatedIndex(-1) { seed(seedValue); }

bool emansis::random::Random::isSeedValid() { return !m_seed.empty(); }


//TODO:测试新写的接口

void emansis::random::Random::update(size_t curIndex)
{
    /*如果
    * 0~15，0~7用过了，cur位于8，used位于9，updated位于-1，判定需要更新0~7
    * 0~15，0~6用过了，cur位于7，used位于8，updated位于-1，判定不需要更新
    * 0~15，0~8用过了，cur位于9，used位于10，updated位于-1，判定需要更新0~7
    * 0~15，0~8用过了，cur位于15，used位于16，updated位于7，获取的数据超出已有范围，判定更新8~15，更新后used位于-1，cur位于0
    * 0~15，0~8用过了，cur位于16，used位于16，updated位于7，判定需要更新8~15，更新后used位于-1，cur位于0
    * 0~15，0~15用过了，cur位于16,used位于16，updated位于-1，判定需要更新0~15，更新后used位于-1，cur位于0
    */

    //对齐异常时需处理
    //如果updatedIndex + 1不为8的倍数,则强制对齐它
    m_uUpdatedIndex = (m_uUpdatedIndex + 1) / sizeof(InitSeed_Type) * sizeof(InitSeed_Type) - 1;
    
    //TODO:日志系统的加入
    //如果randomSeedLength不为8的整倍数时截断多余部分丢弃不使用-但是打印警告信息/输出至日志目前还没做这个系统
    //进行used越界修正，used包含了curIndex的长度信息，used越界代表着curIndex必定越界
    if (m_uUsedIndex >= RANDOM_SEED_LENGTH_EMANSIS / sizeof(InitSeed_Type) * sizeof(InitSeed_Type)) m_uUpdatedIndex = (size_t)-1;

    //处理数据-
    //如果
    //0~15，used在16及之后，更新到-1
    //0~15，used为-1时，updated如不为-1，则更新updated之后的所有数据，然后将updated复位至-1
    //0~31，used为16，cur为16，updated为-1，updated更新至15
    if      (m_uUsedIndex == (size_t)-1 && m_uUpdatedIndex != m_uUsedIndex) {
        //used为-1，update不为-1时更新updated+1至之后的范围
        updateRange(m_uUpdatedIndex + 1, RANDOM_SEED_LENGTH_EMANSIS);
        m_uUpdatedIndex = (size_t)-1;
    }
    else if (curIndex - m_uUpdatedIndex > 8)
        //cur距离updated大于8bit,更新updated到cur前的8bit对齐位
        m_uUpdatedIndex += updateRange(m_uUpdatedIndex + 1, curIndex / sizeof(InitSeed_Type) * sizeof(InitSeed_Type));
}

bool emansis::random::Random::checkUpdate(size_t curIndex)
{
    /*如果
    * 0~15，0~7用过了，cur位于8，used位于9，updated位于-1，判定需要更新0~7
    * 0~15，0~6用过了，cur位于7，used位于8，updated位于-1，判定不需要更新
    * 0~15，0~8用过了，cur位于9，used位于10，updated位于-1，判定需要更新0~7
    * 0~15，0~8用过了，cur位于15，used位于16，updated位于7，获取的数据超出已有范围，判定更新8~15，更新后used位于-1，cur位于0
    * 0~15，0~8用过了，cur位于16，used位于16，updated位于7，判定需要更新8~15，更新后used位于-1，cur位于0
    * 0~15，0~15用过了，cur位于16,used位于16，updated位于-1，判定需要更新0~15，更新后used位于-1，cur位于0
    */

    //used为-1时的处理
    if      (m_uUsedIndex == (size_t)-1)
        //used与update同为-1不用更新
        if  (m_uUpdatedIndex == m_uUsedIndex) return false;
        //used为-1，update不为-1时更新updated+1至之后的范围
        else return true;
    //cur距离updated大于8bit,更新updated到cur前的8bit对齐位
    if      (curIndex - m_uUpdatedIndex > 8) return true;
    else return false;
}

size_t emansis::random::Random::updateRange(size_t start, size_t end)
{
    //TODO: throw exception start biggerst end error
    //间隔必须为8的整数倍
    (end - start) & sizeof(InitSeed_Type) == 0;//不为整数倍时抛异常

    return end - start;
}

template <typename Get_Type>
const Get_Type& emansis::random::Random::get()
{
    //获取当前随机数
    size_t curIndex = m_uUsedIndex + 1;
    //更新占用标记
    m_uUsedIndex += sizeof(Get_Type);
    //更新不再占用的种子，如果cur能获取的种子长度不足时更新末尾的所有种子并将占用标记与更新标记复位
    checkUpdate(curIndex) && Update(m_uUsedIndex, sizeof(Get_Type))
    //如果更新了包含cur的种子，则将cur挪动到开头位置
    if (m_uUsedIndex == (size_t)-1) curIndex = 0; 
    //获取对应的随机数
    return *(Get_Type*)(m_seed.data() + curIndex);
}

emansis::bitmap<RANDOM_SEED_LENGTH_EMANSIS> emansis::random::Random::seed(){ return m_seed; }

void emansis::random::Random::seed(emansis::random::Random::InitSeed_Type initSeed) {
    if (isSeedValid() && initSeed == 0) {
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(initSeed, "seed is dont set, and input seed is 0");
    }
    else if (initSeed != 0) { 
        for (int i = 0; i < RANDOM_SEED_LENGTH_EMANSIS / sizeof(InitSeed_Type); i++) {
            //reg init
            InitSeed_Type reg = (initSeed * (i + 1) * 0x7D3EC265DC724E35);
            reg = reg == 0 ? 0xA9 : reg;
            //xorShift
            emansis::random::Random::xorShiftPlus<InitSeed_Type, sizeof(InitSeed_Type)>(
                reg, (InitSeed_Type)UNMASK_BIT64_FULL_TRUE,
                static_cast<int8_t>(SHIFT_RANGE_EMANSIS(3, sizeof(InitSeed_Type))),
                static_cast<int8_t>(SHIFT_RANGE_EMANSIS(2, sizeof(InitSeed_Type))),
                static_cast<int8_t>(SHIFT_RANGE_EMANSIS(5, sizeof(InitSeed_Type))));
            //seed paste
            ((InitSeed_Type*)m_seed.data())[i] = reg;
            }
        }
    if (!isSeedValid())
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(initSeed, "the seed is not set, and input seed maked out seed is 0");
    m_uUsedIndex = 0;
}

template<typename Rand_Type>
Rand_Type emansis::random::Random::typeOf_rand(Rand_Type lower, Rand_Type upper, Rand_Type unmask, uint8_t r_1, uint8_t l_1, uint8_t r_2) {
    //shift width exception proc
    if  (r_1 > BITSIZE(Rand_Type))
    if  (r_1 > BITSIZE(Rand_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Rand_Type) - 1), r_1);
    if  (r_2 > BITSIZE(Rand_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Rand_Type) - 1), r_2);
    if  (l_1 > BITSIZE(Rand_Type))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(Rand_Type) - 1), l_1);
    // abs left and right
    if (lower == upper) return lower;
    if (lower > upper) std::swap(lower, upper);
    //get seed
    Rand_Type  reg     = *(Rand_Type*)(m_seed.data() + m_uUsedIndex),
            curSeed    = reg;
    if (reg == 0) reg = curSeed == 0 ? curSeed + 1 : curSeed;
    //xorShift
    xorShiftPlus<Rand_Type>(reg, unmask, r_1, l_1, r_2);
    //update seed index
    if (m_uUsedIndex + sizeof(Rand_Type) >= RANDOM_SEED_LENGTH_EMANSIS) m_uUsedIndex = 0;
    else m_uUsedIndex += sizeof(Rand_Type);
    //seed paste
    *(Rand_Type*)(m_seed.data() + m_uUsedIndex) = reg;
    return (reg % (upper - (lower + 1))) + lower;
}

template <typename Ret_Type, uint8_t Length = sizeof(Ret_Type)>
Ret_Type emansis::random::Random::xorShiftPlus(Ret_Type &srcSeed, const Ret_Type &unmask, int8_t r_1, int8_t l_1, int8_t r_2)
{
    if (Length == 0)
        throw RANDOM_ZERO_OF_LENGTH_EXCEPTION_EMANSIS(Ret_Type);

    //shift width exception proc
    if  (r_1 > (std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, ((std::min(BITSIZE(uint64_t), BITSIZE(Ret_Type))) - 1), r_1);
    if  (r_2 > (std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, ((std::min(BITSIZE(uint64_t), BITSIZE(Ret_Type))) - 1), r_2);
    if  (l_1 > (std::min(BITSIZE(int64_t), BITSIZE(Ret_Type))))
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, ((std::min(BITSIZE(uint64_t), BITSIZE(Ret_Type))) - 1), l_1);

    Ret_Type dest;

    //length为byte数，从上至下，逐级过滤，最多为8，最低为1，逐层操作
    for (uint8_t index = 0; index < Length;) {

        uint64_t& curReg = *(uint64_t*)((uint8_t*)(&srcSeed) + index);
        curReg = curReg != 0 ? curReg : (index + 1) * (uint64_t)0x7278C263DD273B1;
        //xorShift
        xorShift_u64(curReg, r_1, l_1, r_2);
        //ret paste
        *(uint64_t*)(&dest + index) = curReg & (uint64_t)*(uint64_t*)(&unmask + index);
        //update index
        index += sizeof(curReg);
    }
    return dest;
}

void emansis::random::Random::xorShift_u64(uint64_t& reg, uint8_t r_1, uint8_t l_1, uint8_t r_2) {
    uint64_t base = reg;
    //seed var
    if (reg == 0)
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(reg, "seed is dont set, and input seed is 0");
    //shift width exception proc
    if  (r_1 > BITSIZE(uint64_t) - 1)
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(uint64_t) - 1), r_1);
    if  (r_2 > BITSIZE(uint64_t) - 1)
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(uint64_t) - 1), r_2);
    if  (l_1 > BITSIZE(uint64_t) - 1)
        throw RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(NULL, (BITSIZE(uint64_t) - 1), l_1);
    
    //xorShift
    reg ^= reg >> SHIFT_RANGE_EMANSIS(r_1, sizeof(uint64_t));
    reg ^= reg << SHIFT_RANGE_EMANSIS(l_1, sizeof(uint64_t));
    reg ^= reg >> SHIFT_RANGE_EMANSIS(r_2, sizeof(uint64_t));
    //result reg exception
    if(reg == 0)
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(base, "the seed is not set, and input seed maked out seed is 0");
}
