#include <cmath>
#include <cstdio>
#include <iostream>
#include <typeinfo>
typedef unsigned char *byte_pointer;

// 因为计算机存储的是数值的补码，所以这里打印的是补码
void show_bytes(byte_pointer start, int len) {
    int i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer)&x, sizeof(void *));
}
void test_show_bytes(int val) {
    int ival = val;
    float fval = (float)ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

void test1() {
    printf("%ld\n", sizeof(long int));  // 64位大小位8

    int val = 1;
    if (*((char *)&val) == 1) {
        std::cout << "小端" << std::endl;
    } else {
        std::cout << "大端" << std::endl;
    }
    int val1 = 12345;
    float val2 = 12345.0;
    test_show_bytes(val1);
    test_show_bytes(val2);
}

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y; /* Step 1 */
    *x = *x ^ *y; /* Step 2 */
    *y = *x ^ *y; /* Step 3 */
}

void reverse_array(int a[], int cnt) {
    int first, last;
    for (first = 0, last = cnt - 1;
         first < last;
         first++, last--)
        inplace_swap(&a[first], &a[last]);
}

void test2() {
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {1, 2, 3, 4, 5};
    reverse_array(arr1, 4);
    reverse_array(arr2, 5);
    for (int i = 0; i < 4; ++i) {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

    int x = 10;
    inplace_swap(&x, &x);
    std::cout << x << std::endl;
}

/* Declarations of functions implementing operations bis and bic */
int bis(int x, int m) { return 0; }  // 位设置
int bic(int x, int m) { return 0; }  // 位清除
/* Compute x|y using only calls to functions bis and bic */
int bool_or(int x, int y) {
    int result = bis(x, y);
    return result;
}
/* Compute x^y using only calls to functions bis and bic */

int bool_xor(int x, int y) {
    int result = bis(bic(x, y), bic(y, x));
    return result;
}

int Xor(int x, int y) {
    return (x | y) & (~x | ~y);
}

// 代替x==y，异或的非
void test3() {
    int x = 0x66, y = 0x39;
    printf("%0x\n", Xor(x, y));
    std::cout << !Xor(10, 10) << std::endl;
    std::cout << !Xor(20, 20) << std::endl;
    std::cout << !Xor(10, 20) << std::endl;
    std::cout << sizeof(void *) << std::endl;
    int val = 1;
    for (int i = 1; i < 70; ++i) {
        if (i == 32) {
            std::cout << "1左移" << i << "位时=  " << (val << i) << std::endl;
        } else {
            std::cout << "1左移" << i << "位时=  " << (val << i) << std::endl;
        }
    }
}

void test4() {
    short int v = -12345;
    unsigned short uv = (unsigned short)v;
    printf("v = %d, uv = %u\n", v, uv);

    std::cout << (-1 < 0u) << std::endl;                        // 结果为0，-1被看做是2^32
    std::cout << (2147483647 > (int)2147483648u) << std::endl;  // 1
    std::cout << (2147483647U > -2147483647 - 1) << std::endl;  // 0
    std::cout << (-1 < 0U) << std::endl;                        // 0
}

void test5() {
    short sx = -12345;       /* -12345 */
    unsigned short usx = sx; /* 53191 */
    int x = sx;              /* -12345 */
    unsigned ux = usx;       /* 53191 */

    printf("sx = %d:\t", sx);
    show_bytes((byte_pointer)&sx, sizeof(short));  //  c7 cf
    printf("usx = %u:\t", usx);
    show_bytes((byte_pointer)&usx, sizeof(unsigned short));  //  c7 cf
    printf("x = %d:\t", x);
    show_bytes((byte_pointer)&x, sizeof(int));  // c7 cf ff ff(补码高位补得是1)
    printf("ux = %u:\t", ux);
    show_bytes((byte_pointer)&ux, sizeof(unsigned));  // c7 cf 00 00

    int val = -1;
    show_bytes((byte_pointer)&val, sizeof(int));  // ff ff ff ff

    std::cout << "==================================" << std::endl;
    short sx2 = -12345;
    /*先要改变大小，之后再完成从有符号到无符号的转换。
     也就是先把高位补1，然后作无符号类型计算该值*/
    unsigned int uy = sx2;
    printf("uy=%u\t", uy);
    show_bytes((byte_pointer)&uy, sizeof(unsigned int));
}

int fun1(unsigned word) {
    return (int)((word << 24) >> 24);
}

void test6() {
    int w = 0x00000076;
    int ans = fun1(w);
    int w1 = 0x87654321;
    show_bytes((byte_pointer)(&ans), sizeof(int));
    show_bytes((byte_pointer)(&ans), sizeof(int));
}

/**
 * @brief
 * 检查x+y是否溢出
 * @param x
 * @param y
 * @return 溢出返回1，否则返回0
 */
int uadd_ok(unsigned x, unsigned y) {
    return (x + y > x || x + y > y);
}

/**
 * @brief
 * 检查x+y是否溢出
 * @param x
 * @param y
 * @return 不溢出返回1，溢出返回0
 */
int tadd_ok(int x, int y) {
    int positive_overflow = x > 0 && y > 0 && x + y < 0;
    int negative_overflow = x < 0 && y < 0 && x + y >= 0;
    return !(positive_overflow || negative_overflow);
}

/**
 * @brief
 * 检查x-y是否溢出
 * @param x
 * @param y
 * @return 不溢出返回1，溢出返回0
 * x，y取何值会产生错误结果，the code is buggy
 */
int tsub_ok(int x, int y) {
    return tadd_ok(x, -y);  // 若y位INT_MIN就已经溢出了
}
int tsub_ok_nobug(int x, int y) {
    if (y == INT32_MIN)
        return 0;
    return tadd_ok(x, -y);
}

void test7() {
    float val1 = 671088632.11;
    printf("%f\n", val1);
    float val2 = 1.11;

    printf("%f\n", 3.4e+35);    //float阶码e占8位，最大255，E最大=e-bias=255-127=128    val=2^128

    int val3 = 1.6f;//向0舍入，也就是1
    printf("val3=%d\n", val3);

    float val4 = float(3.14f + 1e+10) - 1e+10;
    printf("val4=%f\n", val4);

    double val5 = 3.14;
    printf("val5=%.2lf\n", val5);

//双精度定义正无穷、负无穷、零
#define POS_INFINITY 1.0 / 0.0
#define NEG_INFINITY -1.0 / 0.0
#define NEG_ZERO 0.0

    // double pos_infinity = POS_INFINITY;
    double pos_infinity = pow(2, 1024);
    double neg_infinity = NEG_INFINITY;
    double zero = NEG_ZERO;

    if (pos_infinity == INFINITY)
        printf("是正无穷\n");
    if (neg_infinity == -INFINITY)
        printf("是负无穷\n");
    if (zero == 0)
        printf("是零\n");

}




// 作业2.60
/**
 * @brief 
 * 将x的第i个字节（从0开始算），替换成b
 * @param x 
 * @param i 
 * @param b 
 * @return 最终被替换的值
 */
unsigned replace_byte(unsigned x, int i, unsigned char b) {
    unsigned ans = x;
    ((char *)&ans)[i] = b;
    return ans;
}

void print(unsigned char* byte, int bytes) {
    for (int i = 0; i < bytes;++i) {
        printf("%.2x ", byte[i]);
    }
    printf("\n");
}


//作业2.62


void test8() {
    unsigned ret = replace_byte(0x12345678, 2, 0xAB);
    print((unsigned char*)&ret, sizeof(ret));

    ret = replace_byte(0x12345678, 0, 0xAB);
    print((unsigned char*)&ret, sizeof(ret));

}
using std::cout;
using std::endl;
class T5Base
{
public:
    T5Base() :value(55) {}
    virtual ~T5Base() {}
    void test1() { cout << "T5Base test1..." << endl; }
protected:
    int value;
};

class T5Derived : private T5Base {
public:
    using T5Base::test1;
    //using T5Base::value;
    void test2() { cout << "value is " << value << endl; }
};
int main()
{
    // test1();
    // test2();
    test8();
    T5Derived t;
    t.test2();
    t.test1();
    return 0;
}