#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <string>

#include "AES128.hpp"
#include "ShiftRows.hpp"
#include "SubBytes.hpp"
#include "MixColumns.hpp"
#include "Key.hpp"

unsigned char Xtime(unsigned char num) noexcept
{
    unsigned char highbit = num & 0x80;
    unsigned char result = num << 1;
    if (highbit) {
        result = result ^ IrreduciblePolynomial; // subtract x^4 + x^3 + x + 1 
    }
    return result;
}

unsigned char GFMultiply(unsigned char a, unsigned char b) noexcept {
    unsigned char result = 0;
    for (unsigned char i = 0; i < 8; ++i) {
        if (b & 1) {
            result ^= a;
        }
        a = Xtime(a);
        b >>= 1;
    }
    return result;
}

Byte::Byte(int i) {
    byte = i;
}
Byte::Byte() {
    byte = 0;
}

Byte Byte::operator=(const Byte& _byte) {
    byte = _byte.byte;
    return byte;
}

Byte Byte::operator+(Byte _byte) {
    return byte ^ _byte;
}

Byte::operator const unsigned char& () const {
    return byte;
}

Byte::operator unsigned char& () {
    return byte;
}

Byte Byte::operator*(Byte _byte) {
    return GFMultiply(byte, _byte);
}

Byte Byte::operator*(int _byte) {
    return GFMultiply(byte, _byte);
}

template<typename T>
Byte operator+(T byte1, Byte byte2) {
    return byte1 ^ byte2;
}

template<typename T>
Byte operator+(Byte byte1, T byte2) {
    return byte1 ^ byte2;
}

Word& Word::operator=(const Word& _word) {
    word[0] = _word[0];
    word[1] = _word[1];
    word[2] = _word[2];
    word[3] = _word[3];
    return reinterpret_cast<Word&>(word);
}

Byte& Word::operator[](unsigned char index) {
    return word[index];
}

const Byte& Word::operator[](unsigned char index) const {
    return word[index];
}

Word& Block::operator[](unsigned char index) {
    return words[index];
}

const Word& Block::operator[](unsigned char index) const {
    return words[index];
}

void OneBlockEncrypt(Block& block, const Word* keys) {
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

void OneBlockDecrypt(Block& block, const Word* keys) {
    AddRoundKey(block, keys, 10);
    for (int i = 9; i > 0; i--) {
        InvShiftRows(block);
        InvSubBytes(block);
        AddRoundKey(block, keys, i);
        InvMixColumns(block);
    }
    InvShiftRows(block);
    InvSubBytes(block);
    AddRoundKey(block, keys, 0);
}

void FullBuffer(const char* path, unsigned char* buffer, size_t size) {
    std::ifstream file{ path, std::ios::binary };
    file.read(reinterpret_cast<char*>(buffer), size);
    file.close();
}

unsigned char* CreateBuffer(size_t size, size_t& blocks_count) {
    unsigned char* buffer = nullptr;
    if (size % 16 != 0) {
        buffer = new unsigned char[((size / 16) + ((size % 16) / (size % 16))) * 16]{};
        blocks_count = ((size / 16) + ((size % 16) / (size % 16)));
    }
    else {
        buffer = new unsigned char[size] {};
        if (size != 16) {
            blocks_count = size / 16;
        }
        else {
            blocks_count = 1;
        }
        std::cout << size;
    }
    return buffer;
}

void FileEncryption(const char* path, const Word* keys) {
    size_t file_size = std::filesystem::file_size(path);
    size_t blocks_number;
    unsigned char* file_bytes = CreateBuffer(file_size, blocks_number);
    FullBuffer(path, file_bytes, file_size);
    Block* blocks = reinterpret_cast<Block*>(file_bytes);
    for (int i = 0; i < blocks_number; i++) {
        OneBlockEncrypt(blocks[i], keys);
    }
    std::ofstream file{ path, std::ios::binary };
    file.write(reinterpret_cast<char*>(blocks), blocks_number * 16);
    file.close();
}

void FileDecryption(const char* path, const Word* keys) {
    size_t file_size = std::filesystem::file_size(path);
    size_t blocks_number;
    unsigned char* file_bytes = CreateBuffer(file_size, blocks_number);
    FullBuffer(path, file_bytes, file_size);
    Block* blocks = reinterpret_cast<Block*>(file_bytes);
    for (int i = 0; i < blocks_number; i++) {
        OneBlockDecrypt(blocks[i], keys);
    }
    std::ofstream file{ path, std::ios::binary };
    file.write(reinterpret_cast<char*>(blocks), blocks_number * 16);
    file.close();
}
