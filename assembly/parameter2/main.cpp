#include "add.hpp"
#include <iostream>

// 声明函数形参，接收一个 lambda 函数
void MyFunction(void (*lambda)(int)) {
    // 在函数体内调用 lambda 函数
    lambda(10);
}

// int main() {
//     // lambda 函数作为实参传递给 MyFunction
//     MyFunction([](int value) {
//     // lambda 函数体
//     std::cout << "Value: " << value << std::endl;
//     });
//     return 0;
// }

int main() {
    int result = my_asm_function(1, 2);
    std::cout << "Result: " << result << std::endl;

    return 0;
}

