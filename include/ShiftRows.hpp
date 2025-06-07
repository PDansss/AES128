#ifndef AES_INCLUDE_SHIFT_ROWS
#define AES_INCLUDE_SHIFT_ROWS

#include "AES128.hpp"

enum class ShiftMode { LEFT, RIGHT };

void ShiftRows(Block& block);
void InvShiftRows(Block& block);
void CyclicWordShift(Word& array, int shift, ShiftMode mode);

#endif
