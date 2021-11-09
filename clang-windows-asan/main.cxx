#include <cstdio>
#include <cstdlib>

int main() {
    std::printf("hello world!\n");
    char* array = (char*)malloc(10);
    array[0] = 'a';
    array[101] = 'o';
    std::printf("out-of-bounds\n");
    return 0;
}
