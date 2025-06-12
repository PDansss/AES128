#include "AES128.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;

int main()
{
    Block key = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    Word* keys = KeyExpansion(key);
    FileEncryption("TESTFILE.txt", keys);
    return 0;
}
