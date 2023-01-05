![](https://img.shields.io/github/license/ANormalGameDev/Sailboat) ![](https://img.shields.io/github/last-commit/ANormalGameDev/Sailboat)

# Sailboat

Sailboat is an inbetweening library which utilizes modern C++ features to create fluid interpolation between values for complex animations, games and other software. It provides a simple, descriptive and intuitive API which optimizes both performance and readability to make it look as good as it functions. It has a timeline-like structure, and supports interpolation between values of any type which can be converted into a float and vice-versa.

Sailboat was originally designed for private use in my GUI projects / experiments which often consisted of complex animations and required smooth interpolation for translation, scaling, and rotation of objects. However, due to its simple yet powerful nature, I have decided to release it to the public here on GitHub. This project has helped me learn a lot and I hope it will be as helpful for its users as it has been for me.

### Features
- Provides a simple, descriptive, and intuitive API,
- Supports multi-point tweening,
- Supports simultaneous tween of heterogenous values,
- Can step both forwards and backwards by any amount,
- Allows jumping and seeking to any point,
- Accepts custom easing functions and on-step callbacks in form of functions and lambdas,
- Allows separate delays (both positive and negative!), easing functions, and durations for every value,
- Provides useful macroes such as `jump_to_end`, `jump_to_start`, etc. for user convenience,
- Is header-only,
- Has no external dependencies, and much more!

### Hello World!
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

**Line 7:** First, a `Tween` object is created to interpolate from "hello" to "world" in 10 steps (for all values as only one value has been provided). Delays are then added for every value i.e. 'h' will not be interpolated for the first 5 steps, 'e' will not be interpolated for the first 2 steps and so on... After that, the easing function is set to `Sailboat::Easing::Lerp`.

**Line 9:** After the creation of the object, the `for` loop steps forward (default: 1), iterates over the results (a `std::array<char, 5>` in this case as all values are of type `char`), and prints them.

# Getting Started
Since Sailboat is a header-only library with only two files, the installation process is extremely simple and will only take a few moments.

1. Clone this repository using `git` and enter the `Sailboat` directory.
```
git clone https://github.com/ANormalGameDev/Sailboat.git
```

2. Copy the contents of the `include` folder to the directory which contains your project's headers.

3. Include the `Sailboat.h` file and start using it.

# Contributions
Sailboat appreciates any kind of contribution, whether it is just correcting a typo or fixing a major bug. However, there is a set of guidelines which should be followed during development.
- PascalCase should be used for naming namespaces, classes, structs, and easing functions.
- snake_case should be used for naming traits, variables and functions. It should also be used for naming namespaces, classes, and structs which are not frequently accessed by the user.
- The `m_` prefix should be used when naming private variables of a class.
- Implementation details should be in a `*.tci` file.
- Traits should be defined and implemented in the `Sailboat::traits` namespace.
- Easing functions should be defined and implemented in the `Sailboat::Easing` namespace.
- Any class, struct, function, etc. which the users will not access frequently should be implemented in the `Sailboat::detail` namespace (excluding traits and easing functions).

# Credits
Sailboat's readable and intuitive API is inspired by [mobius3/tweeny](https://github.com/mobius3/tweeny).