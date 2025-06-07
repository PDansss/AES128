#ifndef AES_INCLUDE_SUB_BYTES
#define AES_INCLUDE_SUB_BYTES

#include "AES128.hpp"

void SubBytes(Block& block)    noexcept;
void InvSubBytes(Block& block) noexcept;

#endif