#ifndef AES_INCLUDE_KEY
#define AES_INCLUDE_KEY

#include "AES128.hpp"

void AddRoundKey(Block& block, const Word* keys, size_t round);

#endif

