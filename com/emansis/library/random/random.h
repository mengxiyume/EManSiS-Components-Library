#pragma once
#include "../../identify_tables/idt_exception.h"
#include "./randomException.h"
#include "../bitmap/bitmap"

#include <cstdint>
#include <ctime>
#include <algorithm>

namespace emansis {
    namespace random {
        /// @brief 随机数生成器
        class Random {
        public:
            typedef int64_t InitSeed_Type;
        private:
        #define RANDOM_SEED_LENGTH_EMANSIS (sizeof(emansis::random::Random::InitSeed_Type) * 4)
            /// @brief 随机数种子集
            static bitmap<RANDOM_SEED_LENGTH_EMANSIS> gs_seed;
            /// @brief 随机数种子索引
            static uint8_t gs_seedIndex;
        public:
            /// @brief              随机数生成器构造
            /// @param seedValue    初始种子-为0时不更新种子
            inline  Random  (int64_t seedValue = (InitSeed_Type)time(nullptr)) { seed(seedValue); };
            /// @brief              析构
            ~Random         () = default;
            /// @brief              设置随机种子
            /// @param initSeed      初始种子-为0时不更新种子
            static void seed(InitSeed_Type initSeed);
            /// @brief              获取种子集
            /// @return             种子集的拷贝
            inline static bitmap<RANDOM_SEED_LENGTH_EMANSIS> seed   () { return gs_seed; }
            /// @brief              8位随机数生成器
            /// @param lower        下限 默认'-128'
            /// @param upper        上限 默认'127'
            /// @return             上下限中间的随机值
            int8_t  rand_i8 (int8_t lower = INT8_MIN, int8_t upper = INT8_MAX);
            /// @brief              模板函数随机数生成器
            /// @tparam Rand_Type   随机数类型
            /// @param lower        最低值
            /// @param upper        最高值
            /// @param r_1          第一次右移值
            /// @param l_1          第一次左移值
            /// @param r_2          第二次右移值
            /// @return             结果
            template<typename Rand_Type>
            Rand_Type rand(Rand_Type lower, Rand_Type upper, uint8_t r_1, uint8_t l_1, uint8_t r_2);
        private:
        
            /// @brief              种子是否有效
            /// @return             如果种子不为空返回true，否则返回false
            inline static bool  isSeedValid () { return !gs_seed.empty(); }

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