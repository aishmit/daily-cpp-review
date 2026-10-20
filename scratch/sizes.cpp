#include <cstdio>
struct WithVirtual { virtual ~WithVirtual() = default; };
struct NoVirtual   { ~NoVirtual() = default; };
int main() { std::printf("WithVirtual=%zu NoVirtual=%zu\n", sizeof(WithVirtual), sizeof(NoVirtual)); }
