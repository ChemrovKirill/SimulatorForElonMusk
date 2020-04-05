#include "Tests.h"

int main() {
    try {
        test_B2();
    }
    catch (std::out_of_range & e) {
        std::cerr << "out_of_range in " << e.what() << '\n';
    }
    return 0;
}