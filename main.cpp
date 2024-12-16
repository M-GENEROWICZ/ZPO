// Wersje bibliotek standardowych znanych z języka C, ale zaimplementowanych
// dla C++, mają przedrostek "c" (np. stdlib.h -> cstdlib).
#include <cstdlib>
#include <iostream>

int main() {
    std::cout << "Hello world!";
    return EXIT_SUCCESS;
}