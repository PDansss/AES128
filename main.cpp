#include <iostream>

#include "AES128.hpp"
#include "ShiftRows.hpp"
#include "SubBytes.hpp"
#include "MixColumns.hpp"
#include "KeyExpansion.hpp"

using namespace std;

void AddRoundKey(Block& block, const Word* keys, size_t round) {
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            //block.words[i][j] = block.words[i][j] + keys[round * 4 + j][i];
            block.words[j][i] = block.words[j][i] + keys[round * 4 + i][j];
        }
    }
}

void OneBlockCipher(Block& block, const Word* keys) {
    AddRoundKey(block, keys, 0);
    for (int i = 1; i < 10; i++) {
        SubBytes(block);
        ShiftRows(block);
        MixColumns(block);
        AddRoundKey(block, keys, i);
    }
    SubBytes(block);
    ShiftRows(block);
    AddRoundKey(block, keys, 10);
}


int main()
{
    Block array = { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    Block key = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    
    //Block array = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
    //Block key = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    Word* keys = KeyExpansion(key);
    OneBlockCipher(array, keys);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << (int)array[j][i] << " ";
        }
    }
    return 0;
}
