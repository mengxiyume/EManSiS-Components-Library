#include "./random.h"

#include <cstdint>

void emansis::random::Random::seed(int64_t seed) {
    if (isSeedValid() && seed == 0) {
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(seed, "seed is dont set, and input seed is 0");
    }
    else if (seed != 0) { 
        for (int i = 0; i < RANDOM_SEED_LENGTH_EMANSIS / sizeof(int64_t); i++) {
            //reg init
            int64_t reg = seed * (i + 1) * 0x7D3EC265D + 0xB;
            //xorShift
            reg ^= seed >> ((i * 32) % sizeof(int64_t) * 8);
            reg ^= seed << ((i * 57) % sizeof(int64_t) * 8);
            reg ^= seed >> ((i * 99) % sizeof(int64_t) * 8);
            //seed paste
            ((int64_t*)gs_seed.data())[i] = reg;
        }
    }
    if (!isSeedValid())
        throw RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(seed, "the seed is not set, and input seed maked out seed is 0");
}

//Prototype: random functions

int8_t emansis::random::Random::rand_i8(int8_t lower, int8_t upper) {
    // abs left and right
    if (lower > upper) std::swap(lower, upper);
    //get seed
    int8_t reg = gs_seed[gs_seedIndex];
    if (reg == 0) reg = 97;
    //xorShift
    reg ^= reg >> (3 % sizeof(int8_t) * 1) & 0xFF;
    reg ^= reg << (2 % sizeof(int8_t) * 1) & 0xFF;
    reg ^= reg >> (5 % sizeof(int8_t) * 1) & 0xFF;
    //update seed index
    if (gs_seedIndex + 1 >= RANDOM_SEED_LENGTH_EMANSIS) gs_seedIndex = 0;
    else ++gs_seedIndex;
    //seed paste
    gs_seed[gs_seedIndex] = reg;
    return (reg % (upper - lower + 1)) + lower;
}