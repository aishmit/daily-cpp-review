#include <cstdio>

int main() {
    int x = 258;   // 258 = 1*256 + 2

    // "Pretend the memory of x is a row of bytes, and let me read them one at a time."
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&x);

    for (int i = 0; i < 4; ++i)
        std::printf("byte %d: %d\n", i, bytes[i]);
}
