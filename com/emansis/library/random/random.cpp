#include "../../identify_tables/idt_exception.h"
#include "./random.h"
#include "../bitmap/bitmap"

#include <cstdint>
#include <ctime>
#include <algorithm>

namespace emansis {

    //TODO: Random Seed setter

    namespace random {
        //TODO: use bitmap save random seed
        using namespace random;
        class Random {
        private:
        #define RANDOM_SEED_LENGTH (sizeof(int64_t) * 4)
            static bitmap<RANDOM_SEED_LENGTH> gs_seed;
            static uint8_t gs_seedIndex;
        public:
            Random(int64_t seedValue = (int64_t)time(nullptr)) {
                seed(seedValue);
            };
            ~Random();
            void seed(int64_t seed) {
                if (isSeedValid() && seed == 0) {
                    ; //TODO: throw exception
                }
                else if (seed != 0) { 
                    for (int i = 0; i < RANDOM_SEED_LENGTH / sizeof(int64_t); i++) {
                        //reg init
                        int64_t reg = seed * (i + 1) * 0x7D3EC265D + 0xB;
                        //xorShift
                        reg ^= seed >> ((i * 32) % sizeof(int64_t) * 8);
                        reg ^= seed << ((i * 57) % sizeof(int64_t) * 8);
                        reg ^= seed >> ((i * 99) % sizeof(int64_t) * 8);
                        //past
                        ((int64_t*)gs_seed.data())[i] = reg;
                    }
                    
                }
            }
            bitmap<RANDOM_SEED_LENGTH> seed() const { return gs_seed; }
            
            int8_t rand_i8(int8_t lower = INT8_MIN, int8_t upper = INT8_MAX) {
                if (lower > upper) 
                    std::swap(lower, upper);
                int8_t reg = gs_seed[gs_seedIndex++];
                ; //TODO: 进行xorShift生成随机数，使用种子对应位置的数据作为种子，并将种子对应位置的数据覆盖与索引移位

            }
        private:
            bool isSeedValid() { return !gs_seed.empty(); }
        #undef RANDOM_SEED_LENGTH
        };
    }
}