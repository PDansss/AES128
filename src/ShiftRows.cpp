#include "ShiftRows.hpp"
#include <algorithm>

void ShiftRows(Block& block) {
    for (int i = 1; i < 4; i++) {
        CyclicWordShift(block[i], i, ShiftMode::LEFT);
    }
}

void InvShiftRows(Block& block) {
    for (int i = 1; i < 4; i++) {
        CyclicWordShift(block[i], i, ShiftMode::RIGHT);
    }
}

void CyclicWordShift(Word& array, int shift, ShiftMode mode) {

    if (mode == ShiftMode::RIGHT) {
        for (size_t i = 0; i < shift; i++) {
            for (size_t j = WordLength - 1; j > 0; j--) {
                Byte temp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = temp;
            }
        }
    }

    if (mode == ShiftMode::LEFT) {
        for (size_t i = 0; i < shift; i++) {
            for (size_t j = 0; j < WordLength - 1; j++) {
                Byte temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}