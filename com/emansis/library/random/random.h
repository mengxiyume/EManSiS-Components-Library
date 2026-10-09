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
        private:
        #define RANDOM_SEED_LENGTH_EMANSIS (sizeof(int64_t) * 4)
            /// @brief 随机数种子集
            static bitmap<RANDOM_SEED_LENGTH_EMANSIS> gs_seed;
            /// @brief 随机数种子索引
            static uint8_t gs_seedIndex;
        public:
            /// @brief              随机数生成器构造
            /// @param seedValue    初始种子-为0时不更新种子
            inline Random(int64_t seedValue = (int64_t)time(nullptr)) { seed(seedValue); };
            /// @brief              析构
            ~Random() = default;
            /// @brief              设置随机种子
            /// @param seed         初始种子-为0时不更新种子
            void seed(int64_t seed);
            /// @brief              获取种子集
            /// @return             种子集的拷贝
            inline static bitmap<RANDOM_SEED_LENGTH_EMANSIS> seed() { return gs_seed; }
            /// @brief              8位随机数生成器
            /// @param lower        下限 默认'-128'
            /// @param upper        上限 默认'127'
            /// @return             上下限中间的随机值
            int8_t rand_i8(int8_t lower = INT8_MIN, int8_t upper = INT8_MAX);
        private:
            /// @brief              种子是否有效
            /// @return             如果种子不为空返回true，否则返回false
            inline static bool isSeedValid() { return !gs_seed.empty(); }
        };
    }
}