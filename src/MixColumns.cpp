#include "AES128.hpp"

void MixColumns(Block& block) {
    Word rows;
    for (size_t i = 0; i < Nb; i++) {
        rows[0] = block.words[0][i];
        rows[1] = block.words[1][i];
        rows[2] = block.words[2][i];
        rows[3] = block.words[3][i];
        block.words[0][i] = (rows[0] * 0x02) + (rows[1] * 0x03) + rows[2] + rows[3];
        block.words[1][i] = rows[0] + (rows[1] * 0x02) + (rows[2] * 0x03) + rows[3];
        block.words[2][i] = rows[0] + rows[1] + (rows[2] * 0x02) + (rows[3] * 0x03);;
        block.words[3][i] = (rows[0] * 0x03) + rows[1] + rows[2] + (rows[3] * 0x02);
    }
}

void InvMixColumns(Block& block) {
    Word rows;
    for (size_t i = 0; i < Nb; i++) {
        rows[0] = block.words[0][i];
        rows[1] = block.words[1][i];
        rows[2] = block.words[2][i];
        rows[3] = block.words[3][i];
        block.words[0][i] = rows[0]*0x0e + rows[1]*0x0b + rows[2]*0x0d + rows[3]*0x09;
        block.words[1][i] = rows[0]*0x09 + rows[1]*0x0e + rows[2]*0x0b + rows[3]*0x0d;
        block.words[2][i] = rows[0]*0x0d + rows[1]*0x09 + rows[2]*0x0e + rows[3]*0x0b;
        block.words[3][i] = rows[0]*0x0b + rows[1]*0x0d + rows[2]*0x09 + rows[3]*0x0e;
    }
}