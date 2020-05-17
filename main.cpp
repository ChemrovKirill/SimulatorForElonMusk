#include "Tests.h"

int main() {
    //GetReady(); //for STM32
try {
        test_menu();
        //test_B2();
    }
    catch (std::out_of_range & e) {
        std::cerr << "out_of_range in " << e.what() << '\n';
    }
    return 0;
}