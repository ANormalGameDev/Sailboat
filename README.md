# Sailboat
Sailboat is an inbetweening library which utilizes modern C++ features to create fluid interpolation between values for complex animations, games and other software. It provides a simple, descriptive and intuitive API which optimizes both performance and readability to make it look as good as it functions. It has a timeline-like structure, and supports interpolation between values of any type which can be converted into a float and vice-versa.

Sailboat was originally designed for private use in my GUI projects / experiments which often consisted of complex animations and required smooth interpolation for translation, scaling, and rotation of objects. However, due to its simple yet powerful nature, I have decided to release it to the public here on GitHub. This project has helped me learn a lot and I hope it will be as helpful for its users as it has been for me.

### Features
- Provides a simple, descriptive, and intuitive API,
- Supports multi-point tweening,
- Supports simultaneous tween of heterogenous values,
- Can step both forwards and backwards,
- Allows jumping and seeking to any point,
- Accepts custom easing functions and on-step callbacks in form of functions and lambdas,
- Allows separate delays (both positive and negative!), easing functions, and durations for every value,
- Provides useful macroes for user convenience,
- Is header-only,
- Has no external dependencies, and much more!

### Sample Code
```
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
```

**How it works**

// Under Construction //