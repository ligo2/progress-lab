#include <iostream>
#include <vector>
#include <cassert>

namespace myVector {

template <class T>
class vector {
public:
    typedef T* iterator;
    typedef const T* const_iterator;

    typedef T& refrence;
    typedef const T& const_refrence;

    vector() :start(nullptr), finish(nullptr), end_of_storage(nullptr)  {}
    //const左值引用可以引用右值
    vector(int size, const T& value)
        : start(nullptr), finish(nullptr), end_of_storage(nullptr) {
        for (int i = 0; i < size; ++i) {
            push_back(value);
        }
    }

    template <class InputIterator>
    vector(InputIterator first, InputIterator last) 
        :start(nullptr), finish(nullptr), end_of_storage(nullptr) {
        InputIterator begin = first;
        while (begin != last) {
            push_back(*(begin++));
        }
    }

    vector(const vector<T>& x) 
        : start(nullptr), finish(nullptr), end_of_storage(nullptr) {
        for (int i = 0; i < x.size(); ++i) {
            push_back(x[i]);
        }
    }

    ~vector() {
        if (start) {
            delete[] start;
            start = finish = end_of_storage = nullptr;
        }
    }
    /**
     * @brief 
     * @return 返回第一个元素所在位置 
     */
    iterator begin() { return start; }
    const_iterator begin() const { return static_cast<const_iterator>(start); }

    /**
     * @brief 
     * @return  返回最后元素所在位置 
     */
    iterator end() { return finish; }
    const_iterator end() const { return static_cast<const_iterator>(finish); }

    size_t size() const { return finish - start; }
    size_t capacity() const { return end_of_storage - start; }

    bool empty() const { return start == nullptr || start == finish; }

    /**
     * @brief 
     * @param n 
     * @return  返回第n个元素的引用
     */
    refrence operator[](size_t n) {
        assert(n < finish - start);
        return start[n];
    }
    const_refrence operator[](size_t n) const {
        assert(n < finish - start);
        return start[n];
    }

    /**
     * @brief 
     * 如果当前容量 > n则不做任何处理，不会缩容
     * 只改变capacity，不改变size，在n大于当前capacity，capacity变为n
     * @param n 需要开辟的空间大小 
     */
    void reserve (size_t n) {
        if (n > capacity()) {
            //记录个数
            size_t sz = size();
            iterator newStart = new T[n];
            if (start != nullptr) { //vector暂无有效元素时无需拷贝
                // 数据迁移
                iterator begin1 = newStart;
                iterator begin2 = start;
                while (begin2 != finish) {
                    *(begin1++) = *(begin2++);
                }
                delete[] start;
            }
            start = newStart;
            finish = start + sz;
            end_of_storage = start + n;
        }
    }

    /**
     * @brief 
     * 如果当前容量 > n，不会缩容，但会改变size大小
     * capacity不是指定的n，而是2的倍数
     * @param n 
     * @param val 
     */
    void resize (size_t n, T val = T()) {
        if (n > capacity()) {
            reserve(capacity() == 0 ? 4 : 2 * capacity());
        }
        //改变size大小
        size_t sz = size();
        if (n > sz) {
            for (int i = sz; i < n;++i) {
                *(finish++) = val;
            }
        } else {
            finish = start + n;
        }
    }

    void push_back(const T& value) {
        // 先判断空间是否足够
        if (finish == end_of_storage) {
            reserve(capacity() == 0 ? 4 : capacity() * 2);
        }
        *(finish++) = value;
    }

    void pop_back() {        
        if (start && finish!= start) {
            --finish;
        }
    }

    /**
     * @brief 
     * 返回新插入元素的迭代器
     * @param position 
     * @param val 
     * @return 
     */
    iterator insert (iterator position, const T& val) {
        assert(begin() && position - begin() >= 0 && end() - position >= 0);
        size_t pos = position - start;
        if (finish == end_of_storage) {
            reserve(capacity() == 0 ? 4 : capacity() * 2);
        }

        //position及后面元素集体后移
        iterator start = end() - 1;
        while (start != position) {
            *(start + 1) = *start;
            --start;
        }
        *(position + 1) = *position;
        *position = val;
        ++finish;
        return begin() + pos;
    }

    iterator erase (iterator position) {
        assert(begin() && position - begin() >= 0 && end() - position > 0);

        //position及后面元素集体前移
        iterator begin = position + 1;
        while (begin != end()) {
            *(begin - 1) = *begin;
            ++begin;
        }
        --finish;
        return position;
    }

private:
    iterator start;     //指向第一个元素
    iterator finish;    //指向最后一个元素的下一个位置
    iterator end_of_storage;    //指向空间容量的下一个位置
};


void test1() {
    vector<int> v1;
    for (int i = 0; i < 10;++i) {
        v1.resize(i);
        std::cout << "v1's size=" << v1.size() << std::endl;
        std::cout << "v1's capacity=" << v1.capacity() << std::endl;
        for (int i = 0; i < v1.size(); ++i) {
            std::cout << v1[i] << " ";
        }
        std::cout << std::endl;
    }
}

void test2() {
    vector<int> v1(10, 5);
    for (auto& e : v1) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    vector<int> v2(v1);
    for (auto& e : v2) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    vector<int> v3(v1.begin(), v1.end());
    for (auto& e : v3) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    v3.insert(v3.begin() + 3, 2);
    for (auto& e : v3) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    v3.erase(v3.begin() + 3);
    for (auto& e : v3) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    while (!v3.empty()) {
        v3.pop_back();
    }
    for (auto& e : v3) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
}  // namespace myVecot

void test1() {
    std::vector<int> v1;       //default
    for (int i = 0; i < 20;++i) {
        v1.push_back(1);
        std::cout << "v1's capacity=" << v1.capacity() << std::endl;
    }
    std::vector<int> v2(10, 5);
    std::cout << "v1's capacity=" << v1.capacity() << std::endl;
    std::vector<int> v3(v2.begin(), --v2.end());
    std::vector<int> v4(v3);

    std::cout << "v1 : ";
    for (const auto& e : v1) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::cout << "v2 : ";
    for (const auto& e :v2) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::cout << "v3 : ";
    for (const auto& e :v3) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::cout << "v4 : ";
    for (const auto& e : v4) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

}

void test2() {
    // std::vector<int> v1;
    // for (int i = 0; i < 40; ++i) {
    //     v1.resize(i);
    //     std::cout << "v1's size=" << v1.size() << std::endl;
    //     std::cout << "v1's capacity=" << v1.capacity() << std::endl;
    // }
    // v1.pop_back();

    std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    // v1.insert(v1.end() + 10, 10);
    // std::vector<int> v2;
    // v1.insert(v2.begin(), 10);
    // for (auto& e : v2) {
    //     std::cout << e << " ";
    // }
    auto begin = v1.begin();
    auto iterator = v1.erase(v1.begin());

    v1.erase(iterator);
    for (auto& e : v1) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    v1.erase(begin);
    for (auto& e : v1) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main() {
    test2();

    // myVector::test2();

    return 0;
}
