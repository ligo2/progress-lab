#include <iostream>

using namespace std;

// 基类 Shape
// class Shape {
// public:
//     void setWidth(int w) {
//         width = w;
//     }
//     void setHeight(int h) {
//         height = h;
//     }

// protected:
//     int width;
//     int height;
// };

// // 基类 PaintCost
// class PaintCost {
// public:
//     int getCost(int area) {
//         return area * 70;
//     }
// };

// class Rectangle : public Shape, public PaintCost {
// public:
//     int getArea() {
//         return (width * height);
//     }
// };

// void test1() {
//     Rectangle rect;
//     rect.setHeight(10);
//     rect.setWidth(20);
//     int area = rect.getArea();
//     int cost = rect.getCost(area);
//     cout << "area=" << area << "  cost=" << cost << endl;
// }



//重载
class A {
public:
    A(int _a = 10) : a(_a) {}
    A operator+(const A& a_obj){
        A ans;
        ans.a = a + a_obj.a;
        return ans;
    }
    int get() {
        return a;
    }

private:
    int a;
};


void test2() {
    A a(10);
    A b(20);
    A c(a + b);
    cout << c.get() << endl;
}


//多态
class Shape {
protected:
    int width, height;

public:
    Shape(int a = 0, int b = 0) {
        width = a;
        height = b;
    }
    virtual int area() {
        cout << "Parent class area :" << endl;
        return 0;
    }
};

class Rectangle : public Shape {
public:
    Rectangle(int a = 0, int b = 0) : Shape(a, b) {}
    virtual int area() {
        cout << "Rectangle class area :" << endl;
        return (width * height);
    }
};

class Triangle : public Shape {
public:
    Triangle(int a = 0, int b = 0) : Shape(a, b) {}
    virtual int area() {
        cout << "Triangle class area :" << endl;
        return (width * height / 2);
    }
};

void test3() {
    //通过父类的指针或引用去调用虚函数
    Shape* s;
    Rectangle rect(10, 20);
    s = &rect;
    s->area();

    Triangle tri(20, 30);
    s = &tri;
    s->area();
}

//模板
// 函数模板
template<class T>
T add(const T& t1, const T& t2) {
    return t1 + t2;
}
//对普通的类而言，类名就是类型，而对模板而言，myStack是类名，myStack<T>才是类型
template<class T>
class myStack{
public:
    myStack(int _capacity = 4)
		:capacity(_capacity), top(0)
	{
		resource = new int[capacity];
	}
	~myStack()
	{
		delete[] resource;
		top = capacity = 0;
	}
    void push(const T& t);

private:
    T* resource;
    int capacity;
    int top;//栈顶元素
};

template<class T>
void myStack<T>::push(const T& t) {}

void test4() {
    // 隐式实例化，由编译器根据类型自动推导
    std::cout << add(10, 20) << std::endl;
    std::cout << add(10.11, 20.22) << std::endl;
    //显示实例化，直接指定类型
    int a = 22;
    double b = 20.22;
    cout << add<int>(a, b) << endl;
    myStack<int> s;
    s.push(20);
}


//模板特化

//非类型模板参数N是常量值，不占用空间
template<class T, size_t N = 10>
class Demo {
public:
    void print() {
        cout << N << endl;
    }

private:
    T arr[N];
    size_t top;
};

void test5() {
    Demo<int, 20> obj;
    obj.print();
}

//函数模板特化
//需要一个基础的函数模板
template<class T>
bool Max(const T t1, const T t2) {
    return t1 > t2;
}

//特化类型
template<>
bool Max<int*>(int* p1,int* p2) {   //特化的类型和函数的参数需保持一致
    return *p1 > *p2;
}
void test6() {
    cout << Max(30, 20) << endl;
    int a = 20, b = 10;
    int *p1 = &a, *p2 = &b;
    cout << Max(p1, p2) << endl;
}

//偏特化
//1.部分特化，指定部分类型
// 2.对参数进行限制，如下
template <class T1, class T2>
class Data {
public:
    Data() { cout << "Data<T1, T2>" << endl; }

private:
    T1 _d1;
    T2 _d2;
};

template <class T1, class T2>
class Data<T1*, T2*> {
public:
    Data() { cout << "Data<T1*, T2*>" << endl; }

private:
    T1 _d1;
    int _d2;
};
void test7() {
    Data<int, int> d1;
    Data<int*, int*> d2;
}


class Lib {
public:
    void Run(){
        Step1();
        Step2();//this指针指向的是子类对象，多态调用
    }
    void Step1() {
        cout << "parent step1" << endl;
    }
protected:
    virtual void Step2() {
        cout << "parent step2" << endl;
    }
};

class App : public Lib{
protected:
    virtual void Step2() {
        cout << "child step2" << endl;
    }
};
void test8() {
    Lib* plib = new App();
    plib->Run();
}

class Stream{
public:
    virtual void Read(int number)=0; 
    virtual ~Stream(){}
};

//主体类
class FileStream: public Stream{
public:
    virtual void Read(int number){
        cout << "读文件流" << endl;
    }
};

class NetworkStream :public Stream{
public:
    virtual void Read(int number){
        cout << "读网络流" << endl;
    }
};

//扩展操作
// class CryptoStream{
//     Stream* stream; 
// public:
//     CryptoStream(Stream* stm):stream(stm){}

// public:
//     void Read(int number){
//         //额外的加密操作...
//         stream->Read(number);
        
//     }
// };

class CryptoStream : public Stream{
    Stream* stream; 
public:
    CryptoStream(Stream* stm):stream(stm){}

public:
    virtual void Read(int number){
        //额外的加密操作...
        stream->Read(number); 
        
    }
};

void test9() {
    CryptoStream cps1(new FileStream);
    cps1.Read(10);
    CryptoStream cps2(new NetworkStream);
    cps2.Read(10);
}

//单例--双检查
class Singleton {
private:
    Singleton() {}
    Singleton(const Singleton& singleton) = delete;
public:
    /*存在读写时reorder的问题，s_instance = new Singleton();这行代码理论上的三步：
    1. 分配内存
    2. 调用构造器对这块内存初始化
    3. 返回内存的地址交给s_instance

    但是很多编译器会对步骤进行优化，对上面步骤进行重排，可以是先将内存地址交给s_instance后再调用构造器
    进行初始化，这样就会导致一个问题thread A在执行这几步时恰好是将地址交给s_instance但并未掉构造初始化，
    thread B这时执行第一个if时，判断s_instace不为空就直接return了，这时候返回的对象并未初始化就会引发问题
    */
    Singleton* getInstace() {
        if (s_instance == nullptr) {
            //加锁 pthread_mutex_lock 
            if (s_instance == nullptr)
                s_instance = new Singleton();
        }
        return s_instance;
    }

private: 
    static Singleton* s_instance;
};
Singleton* Singleton::s_instance = nullptr;//类外初始化




int main() {
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    // test8();
    test9();

    return 0;
}
