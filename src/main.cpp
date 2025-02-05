#include <iostream>

#include "examples.hpp"
#include "util.hpp"

int main(int argc, char* argv[]) {
    switch (argv[1][0]) {
        case '0':
            return testInviscidBurgers1d();
        case '1':
            return testInviscidBurgers2d();
        default:
            std::cout << "error: unknown test case\n";
            return FAILURE;
    }
}