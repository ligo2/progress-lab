#include <iostream>
#include <vector>
#include <string>

#define ASPECT_RATIO 1.653 // 预处理器盲目进行宏替换坑导致目标码出现多份1.653

const double aspect_radio = 1.653;

class GamePlayer
{
public:
    static const int NumTurns = 5; // 常量声明式
    enum
    {
        NumTurns2 = 5
    };
    int scores[NumTurns];
};
// 这里加上括号也会发生意想不到的效果
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))
// 模板函数可以很好的解决这个问题
template <typename T>
inline void callWithMax(const T &a, const T &b)
{
    f(a > b ? a : b);
}

void f(int a) {}
const int GamePlayer::NumTurns; // 在main函数取static的地址必须提供定义

class TextBlock
{
public:
    TextBlock() {}
    ~TextBlock() {}
    void test() const
    {
        /*  const修饰的只是this指针，也就是const TextBlock* const this
            但是static成员不所以单个对象，不是通过this访问的
        */
        ++s_value;  
        // ++value;    
    }
    void print()
    {
        std::cout << "s_value=" << s_value << std::endl;

    }

private:
    static int s_value;
    int value = 20;
};
int TextBlock::s_value = 10;

class TextBlock2 {
public:
    /*
        两个方法中间做的操作相同，只有返回类型不同
        这么做造成代码的重复，编译时间的浪费
    */
    const char& operator[](std::size_t position) const {
        //边界检查
        //......
        return text[position];
    }
    char& operator[](std::size_t position) {
        //边界检查
        //......
        return text[position];
    }
private:
    std::string text;
};
//解决方法
class TextBlock3 {
public:
    TextBlock3(std::string s):text(s){}
    const char& operator[](std::size_t position) const {
        //边界检查
        //......
        return text[position];
    }
    char& operator[](std::size_t position) {
        return const_cast<char&>(
                    (static_cast<const TextBlock3&>(*this))[position]
                );
    }
private:
    std::string text;
};

int main()
{
    printf("%p\n", &GamePlayer::NumTurns);
    int val1 = ASPECT_RATIO;

    // int a = 5, b = 0;
    // CALL_WITH_MAX(++a, b); // 这里本意是++a的值和b取较大值调用f，但是这里a被累加了两次

    std::vector<int> v{1, 2, 3};
    std::vector<int>::const_iterator iter = v.begin(); // 迭代器指向的内容不可被修改
    const auto iter2 = v.begin();                      // 迭代器指向不可被修改

    TextBlock tb;
    tb.test();
    tb.print();
    
    TextBlock3 tb2("hello");
    const TextBlock3 tb3("hello");
    std::cout<<tb2[2]<<std::endl; 
    std::cout<<tb3[2]<<std::endl; 

    return 0;
}
