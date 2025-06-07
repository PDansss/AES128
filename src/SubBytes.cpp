#include "SubBytes.hpp"

void SubBytes(Block& block) noexcept {
    for (size_t i = 0; i < 16; i++) {
        block.words[i / 4][i % 4] = Sbox[block.words[i / 4][i % 4]];
    }
}