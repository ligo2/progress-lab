#include <iostream>

// This function is defined in assembly.
extern "C" int my_function(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

int main() {
    int result = my_function(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    // Print the result.
    std::cout << "The result is " << result << std::endl;

    return 0;
}
