#include "Key.hpp"
#include "ShiftRows.hpp"

void AddRoundKey(Block& block, const Word* keys, size_t round) {
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            block.words[j][i] = block.words[j][i] + keys[round * 4 + i][j];
        }
    }
}

Word* KeyExpansion(const Block& key) {
    Word* keys = new Word[44];
    keys[0] = { key.words[0][0], key.words[1][0], key.words[2][0], key.words[3][0] };
    keys[1] = { key.words[0][1], key.words[1][1], key.words[2][1], key.words[3][1] };
    keys[2] = { key.words[0][2], key.words[1][2], key.words[2][2], key.words[3][2] };
    keys[3] = { key.words[0][3], key.words[1][3], key.words[2][3], key.words[3][3] };

    Word temp = keys[3];

    size_t i = 4;
    while (i < 44) {
        if (i % 4 == 0) {
            CyclicWordShift(temp, 1, ShiftMode::LEFT);
            temp[0] = Sbox[temp[0]] ^ Rcon[i / Nk];
            temp[1] = Sbox[temp[1]];
            temp[2] = Sbox[temp[2]];
            temp[3] = Sbox[temp[3]];
        }
        keys[i][0] = temp[0] + keys[i - Nk][0];
        keys[i][1] = temp[1] + keys[i - Nk][1];
        keys[i][2] = temp[2] + keys[i - Nk][2];
        keys[i][3] = temp[3] + keys[i - Nk][3];
        temp = keys[i];
        i++;
    }
    return keys;
}