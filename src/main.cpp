#include <iostream>
#include "../include/Sailboat.h"

using namespace Sailboat::Easing;

int main(int, char**) {
    auto tw = Sailboat::from('h', 'e', 'l', 'l', 'o').to('w', 'o', 'r', 'l', 'd').in(10).wait(5, 2, 0, 1, 3).via(Lerp);
    for (int i = 0; i < tw.length(); i++) {
        for (char c : tw.step()) std::cout << c << " ";
        std::cout << "\n";
    }
}
