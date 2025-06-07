#include "ShiftRows.hpp"

void ShiftRows(Block& block) {
    for (int i = 1; i < 4; i++) {
        CyclicWordShift(block[i], i);
    }
}

void CyclicWordShift(Word& array, int shift, ShiftMode mode) {
    for (size_t i = 0; i < shift; i++) {
        for (size_t j = 0; j < WordLength - 1; j++) {
            Byte temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
        }
    }
}