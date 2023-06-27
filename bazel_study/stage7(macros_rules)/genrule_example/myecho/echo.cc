#include <iostream>

int main(int argc, char * argv[])
{
    while(--argc)
        std::cout << *++argv << (argc > 1? " ": "");
    std::cout << std::endl;
}