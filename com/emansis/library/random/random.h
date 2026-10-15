#pragma once
#include "../../identify_tables/idt_exception.h"
#include "./randomException.h"
#include "../bitmap/bitmap"

#include <cstdint>
#include <cfloat>
#include <ctime>
#include <algorithm>

namespace emansis {
    namespace random {
    /// @brief 32位浮点数指数位从长度
    #define FLT32_EXP_SIZE_EMANSIS   8
    /// @brief 64位浮点数指数位从长度
    #define FLT64_EXP_SIZE_EMANSIS   11
    /// @brief 32位浮点数最小随机值
    #define FLT32_RAND_MAX_EMANSIS  (float)(INT32_MAX / (float)(1 << FLT32_EXP_SIZE_EMANSIS))
    /// @brief 32位浮点数最大随机值
    #define FLT32_RAND_MIN_EMANSIS  (float)(INT32_MIN / (float)(1 << FLT32_EXP_SIZE_EMANSIS))
    /// @brief 64位浮点数最小随机值
    #define FLT64_RAND_MAX_EMANSIS  (double)(INT64_MAX / (double)((long long)1 << (FLT32_EXP_SIZE_EMANSIS) * 5))
    /// @brief 64位浮点数最大随机值
    #define FLT64_RAND_MIN_EMANSIS  (double)(INT64_MIN / (double)((long long)1 << (FLT32_EXP_SIZE_EMANSIS) * 5))
    
        /// @brief 随机数生成器
        class Random {
        public:
            typedef int64_t InitSeed_Type;
        private:
        #define RANDOM_SEED_LENGTH_EMANSIS (sizeof(emansis::random::Random::InitSeed_Type) * 4) //初始种子库长度为8*4，未时编译可更改为更高
            /// @brief 随机数种子集
            bitmap<RANDOM_SEED_LENGTH_EMANSIS> m_seed;
            /// @brief 随机数种子索引
            uint8_t m_uSeedIndex;
        public:
            /// @brief              随机数生成器构造
            /// @param seedValue    初始种子-为0时不更新种子
            Random  (InitSeed_Type seedValue = (InitSeed_Type)time(nullptr));
            /// @brief              析构
            ~Random         () = default;
            /// @brief              设置随机种子
            /// @param initSeed      初始种子-为0时不更新种子
            void        seed        (InitSeed_Type initSeed);
            /// @brief              获取种子集
            /// @return             种子集的拷贝
            bitmap<RANDOM_SEED_LENGTH_EMANSIS> seed();
            /// @brief              8位随机数生成器
            /// @param lower        下限 默认'-128'
            /// @param upper        上限 默认'127'
            /// @return             上下限中间的随机值
            int8_t      rand_i8     (int8_t     lower = INT8_MIN,   int8_t  upper = INT8_MAX)  noexcept; 
            /// @brief              8位随机数生成器
            /// @param lower        下限
            /// @param upper        上限
            /// @return             上下限中间的随机值
            int8_t      rand        (int8_t     lower,              int8_t  upper)  noexcept; 
            /// @brief              8位无符号随机数生成器
            /// @param lower        下限 默认'0'
            /// @param upper        上限 默认'255'
            /// @return             上下限中间的随机值
            uint8_t     rand_u8     (uint8_t    lower = 0,          uint8_t upper = UINT8_MAX)  noexcept;
            /// @brief              8位无符号随机数生成器
            /// @param lower        下限
            /// @param upper        上限
            /// @return             上下限中间的随机值
            uint8_t     rand        (uint8_t     lower,             uint8_t  upper)  noexcept; 
            /// @brief              16位随机数生成器
            /// @param lower        下限 默认'-32768'
            /// @param upper        上限 默认'32767'
            /// @return             上下限中间的随机值
            int16_t     rand_i16    (int16_t    lower = INT16_MIN,  int16_t  upper = INT16_MAX)  noexcept;
            /// @brief              16位随机数生成器
            /// @param lower        下限
            /// @param upper        上限
            /// @return             上下限中间的随机值
            int16_t     rand        (int16_t    lower,              int16_t  upper)  noexcept;
            /// @brief              16位无符号随机数生成器
            /// @param lower        下限 默认'0'
            /// @param upper        上限 默认'65535'
            /// @return             上下限中间的随机值
            uint16_t    rand_u16    (uint16_t   lower = 0,          uint16_t upper = UINT16_MAX)  noexcept;
            /// @brief              16位无符号随机数生成器
            /// @param lower        下限
            /// @param upper        上限
            /// @return             上下限中间的随机值
            uint16_t    rand        (uint16_t   lower,              uint16_t upper)  noexcept;
            /// @brief              32位随机数生成器 //不知道为啥32位的用起来非常慢,尽量别用32位的吧
            /// @param lower        下限 默认'-2147483648'
            /// @param upper        上限 默认'2147483647'
            /// @return             上下限中间的随机值
            int32_t     rand_i32    (int32_t    lower = INT32_MIN,  int32_t  upper = INT32_MAX)  noexcept; 
            /// @brief              32位随机数生成器
            /// @param lower        下限
            /// @param upper        上限
            /// @return             上下限中间的随机值
            int32_t     rand        (int32_t    lower,              int32_t  upper)  noexcept; 
            /// @brief              32位无符号随机数生成器
            /// @param lower        下限 默认'0'
            /// @param upper        上限 默认'4294967295'
            /// @return             上下限中间的随机值
            uint32_t    rand_u32    (uint32_t   lower = 0,          uint32_t upper = UINT32_MAX)  noexcept;
            /// @brief              32位无符号随机数生成器
            /// @param lower        下限 默认'0'
            /// @param upper        上限 默认'4294967295'
            /// @return             上下限中间的随机值
            uint32_t    rand        (uint32_t   lower,              uint32_t upper)  noexcept;
            /// @brief              64位随机数生成器
            /// @param lower        下限 默认'-9223372036854775808'
            /// @param upper        上限 默认'9223372036854775807'
            /// @return             上下限中间的随机值
            int64_t     rand_i64    (int64_t    lower = INT64_MIN,  int64_t  upper = INT64_MAX)  noexcept; 
            /// @brief              64位随机数生成器
            /// @param lower        下限
            /// @param upper        上限
            /// @return             上下限中间的随机值
            int64_t     rand        (int64_t    lower,              int64_t  upper)  noexcept; 
            /// @brief              64位无符号随机数生成器
            /// @param lower        下限 默认'0'
            /// @param upper        上限 默认'18446744073709551615'
            /// @return             上下限中间的随机值
            uint64_t    rand_u64    (uint64_t   lower = 0,          uint64_t upper = UINT64_MAX)  noexcept;
            /// @brief              64位无符号随机数生成器
            /// @param lower        下限
            /// @param upper        上限
            /// @return             上下限中间的随机值
            uint64_t    rand        (uint64_t   lower = 0,          uint64_t upper = UINT64_MAX)  noexcept;
            /// @brief              32位浮点数生成器
            /// @param lower        下限 默认'-8388608.0f'
            /// @param upper        上限 默认'8388607.0f'
            /// @return             上下限中间的随机值
            float       rand_fp32   (float      lower = FLT32_RAND_MIN_EMANSIS, float   upper = FLT32_RAND_MAX_EMANSIS); 
            /// @brief              32位浮点数生成器
            /// @param lower        下限
            /// @param upper        上限
            /// @return             上下限中间的随机值
            float       rand        (float      lower,                          float   upper); 
            /// @brief              64位浮点数生成器
            /// @param lower        下限 默认'-8388608.0lf'
            /// @param upper        上限 默认'8388607.99999999lf'
            /// @return             上下限中间的随机值
            double      rand_fp64   (double    lower = FLT64_RAND_MIN_EMANSIS,  double  upper = FLT64_RAND_MAX_EMANSIS);
            /// @brief              64位浮点数生成器
            /// @param lower        下限
            /// @param upper        上限
            /// @return             上下限中间的随机值
            double      rand        (double    lower,                           double  upper);
            /// @brief              随机至1
            /// @return             0.0~1.0之间的随机值
            double      one         ();
            /// @brief              百分比随机
            /// @return             0.0~100.0中间的随机值
            double      hundred     ();
            /// @brief              千分比随机
            /// @return             0.0~1000.0中间的随机值
            double      thousand    ();
            /// @brief              种子是否有效
            /// @return             如果种子不为空返回true，否则返回false
            bool        isSeedValid ();
        private:
            /// @brief              64位无符号随机数生成器
            /// @param reg          传入种子，种子经过计算变为结果
            /// @param r_1          第一次右移值
            /// @param l_1          第一次左移值
            /// @param r_2          第二次右移值
            static void xorShift_u64(uint64_t& reg, uint8_t r_1, uint8_t l_1, uint8_t r_2);
            /// @brief              xorShiftPlus
            /// @tparam Ret_Type    数据类型
            /// @tparam Length      数据长度-byte数
            /// @param srcSeed      种子
            /// @param unmask       输出掩码
            /// @param r_1          第一次随机的凭据-最高为64bit
            /// @param l_1          第二次随机的凭据-最高为64bit
            /// @param r_2          第三次随机的凭据-最高为64bit
            /// @return             完成数据生成后的掩码处理后随机值
            template<
            typename    Ret_Type,
            uint8_t     Length>
            static Ret_Type xorShiftPlus(
                Ret_Type&       srcSeed,
                const Ret_Type& unmask, 
                int8_t r_1, 
                int8_t l_1,
                int8_t r_2);
            /// @brief              模板函数随机数生成器
            /// @tparam Rand_Type   随机数类型
            /// @param lower        上限值
            /// @param upper        下限值
            /// @param r_1          第一次右移值
            /// @param l_1          第一次左移值
            /// @param r_2          第二次右移值
            /// @return             上下限中间的随机值
            template<typename Rand_Type>
            Rand_Type   typeOf_rand (Rand_Type lower, Rand_Type upper, Rand_Type unmask, uint8_t r_1, uint8_t l_1, uint8_t r_2);
        };
    }
    /// @brief 全局随机数生成器生成器
    static random::Random gs_rand;
}