#include "mylib.h"

int main() {
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << endl;
    }

    cout << "Just trying out\n";

    greet();

    return 0;
}