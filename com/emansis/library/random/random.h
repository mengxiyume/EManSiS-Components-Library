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
        /// @brief 随机数生成器
        class Random {
        public:
            typedef int64_t InitSeed_Type;
        private:
        #define RANDOM_SEED_LENGTH_EMANSIS (sizeof(emansis::random::Random::InitSeed_Type) * 4) //初始种子库长度为4，可更改为更高
            /// @brief 随机数种子集
            static bitmap<RANDOM_SEED_LENGTH_EMANSIS> gs_seed;
            /// @brief 随机数种子索引
            static uint8_t gs_seedIndex;
        public:
            /// @brief              随机数生成器构造
            /// @param seedValue    初始种子-为0时不更新种子
            Random  (InitSeed_Type seedValue = (InitSeed_Type)time(nullptr));
            /// @brief              析构
            ~Random         () = default;
            /// @brief              设置随机种子
            /// @param initSeed      初始种子-为0时不更新种子
            static void seed(InitSeed_Type initSeed);
            /// @brief              获取种子集
            /// @return             种子集的拷贝
            static bitmap<RANDOM_SEED_LENGTH_EMANSIS> seed();
            /// @brief              8位随机数生成器
            /// @param lower        下限 默认'-128'
            /// @param upper        上限 默认'127'
            /// @return             上下限中间的随机值
            int8_t      rand_i8     (int8_t     lower = INT8_MIN,   int8_t  upper = INT8_MAX)  noexcept; 
            /// @brief              8位无符号随机数生成器
            /// @param lower        下限默认'0'
            /// @param upper        上限默认'255'
            /// @return             上下限中间的随机值
            uint8_t     rand_u8     (uint8_t    lower = 0,          uint8_t upper = UINT8_MAX)  noexcept;
            /// @brief              16位随机数生成器
            /// @param lower        下限 默认'-32768'
            /// @param upper        上限 默认'32767'
            /// @return             上下限中间的随机值
            int16_t     rand_i16    (int16_t    lower = INT16_MIN,  int16_t  upper = INT16_MAX)  noexcept; 
            /// @brief              16位无符号随机数生成器
            /// @param lower        下限默认'0'
            /// @param upper        上限默认'65535'
            /// @return             上下限中间的随机值
            uint16_t    rand_u16    (uint16_t   lower = 0,          uint16_t upper = UINT16_MAX)  noexcept;
            /// @brief              32位随机数生成器
            /// @param lower        下限 默认'-2147483648'
            /// @param upper        上限 默认'2147483647'
            /// @return             上下限中间的随机值
            int32_t     rand_i32    (int32_t    lower = INT32_MIN,  int32_t  upper = INT32_MAX)  noexcept; 
            /// @brief              32位无符号随机数生成器
            /// @param lower        下限默认'0'
            /// @param upper        上限默认'4294967295'
            /// @return             上下限中间的随机值
            uint32_t    rand_u32    (uint32_t   lower = 0,          uint32_t upper = UINT32_MAX)  noexcept;
            /// @brief              64位随机数生成器
            /// @param lower        下限 默认'-9223372036854775808'
            /// @param upper        上限 默认'9223372036854775807'
            /// @return             上下限中间的随机值
            int64_t     rand_i64    (int64_t    lower = INT64_MIN,  int64_t  upper = INT64_MAX)  noexcept; 
            /// @brief              64位无符号随机数生成器
            /// @param lower        下限默认'0'
            /// @param upper        上限默认'18446744073709551615'
            /// @return             上下限中间的随机值
            uint64_t    rand_u64    (uint64_t   lower = 0,          uint64_t upper = UINT64_MAX)  noexcept;
            /// @brief              模板函数随机数生成器
            /// @tparam Rand_Type   随机数类型
            /// @param lower        上限值
            /// @param upper        下限值
            /// @param r_1          第一次右移值
            /// @param l_1          第一次左移值
            /// @param r_2          第二次右移值
            /// @return             上下限中间的随机值
            template<typename Rand_Type>
            Rand_Type   rand        (Rand_Type lower, Rand_Type upper, uint8_t r_1, uint8_t l_1, uint8_t r_2);
        private:
        
            /// @brief              种子是否有效
            /// @return             如果种子不为空返回true，否则返回false
            static bool  isSeedValid();

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
            
            /// @brief              随机数生成器
            /// @tparam Reg_Type    生成对象类型
            /// @param reg          传入种子，种子经过计算变为结果
            /// @param r_1          第一次右移值
            /// @param l_1          第一次左移值
            /// @param r_2          第二次右移值
            template<typename Reg_Type>
            static void xorShift(Reg_Type& reg, uint8_t r_1, uint8_t l_1, uint8_t r_2);
        };
    }
}