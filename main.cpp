// Wersje bibliotek standardowych znanych z języka C, ale zaimplementowanych
// dla C++, mają przedrostek "c" (np. stdlib.h -> cstdlib).
#include <cstdlib>
#include <iostream>
#include "include/package.hpp"

int main() {

    Package p1;
    Package p2(std::move(p1));

    std::cout << p2.get_id();
    return EXIT_SUCCESS;
}