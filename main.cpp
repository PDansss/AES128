#include "AES128.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;

void FullBuffer(string path, unsigned char* buffer, size_t size) {
    ifstream file{ path, ios::binary };
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
        buffer = new unsigned char[size]{};
        if (size != 16) {
            blocks_count = size / 16;
        }
        else {
            blocks_count = 1;
        }
        cout << size;
    }
    return buffer;
}

int main()
{
    Block key = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    Word* keys = KeyExpansion(key);

    string path = "TESTFILE.txt";
    size_t file_size = std::filesystem::file_size(path);
    size_t blocks_number;

    unsigned char* file_bytes = CreateBuffer(file_size, blocks_number);
    FullBuffer(path, file_bytes, file_size);
    Block* blocks = reinterpret_cast<Block*>(file_bytes);
    for (int i = 0; i < blocks_number; i++) {
        OneBlockDecrypt(blocks[i], keys);
    }
    ofstream file{ path, ios::binary};
    file.write(reinterpret_cast<char*>(blocks), blocks_number * 16);
    file.close();

    return 0;
}
