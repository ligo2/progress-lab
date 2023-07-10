#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

using namespace std;

//int divide() 
//{
//	int left, right;
//	cin >> left >> right;
//	if (right == 0)
//		throw invalid_argument("除0错误");
//	return left / right;
//}
////void func()
////{
////	int* p1 = new int;
////	//当divide抛异常时就会有异常安全问题，无法delete p1引发资源泄露
////	//方法一：中途捕获完delete，重新抛异常
////	try {
////		cout << divide() << endl;
////	}
////	catch (...) {
////		delete p1;
////		throw;
////	}
////	cout << "delete: " << p1 << endl;
////	delete p1;
////}
////方法一有一个问题，当有多个地方都可能存在异常时，需要判断具体是谁引发的异常，比较麻烦
//void func()
//{
//	int* p1 = new int;
//	int* p2 = nullptr;
//	int* p3 = nullptr;
//	
//	try {
//		p2 = new int;
//		p3 = new int;
//		cout << divide() << endl;
//		
//	}
//	catch (...) {
//		//在这里需要判断到底是谁引发的异常，然后根据情况进行delete
//		//...
//		delete p1;
//		throw;
//	}
//	delete p1;
//	delete p2;
//	delete p3;
//}
//int main()
//{
//	try {
//		func();
//	}
//	catch (const exception& e) {
//		cout << e.what() <<endl;
//	}
//
//	return 0;
//}


//方法二：智能指针，像指针一样使用
//template<class T>
//class SmartPtr
//{
//public:
//	SmartPtr(T* ptr)
//		:_ptr(ptr)
//	{}
//	T& operator*() const
//	{
//		return *_ptr;
//	}
//	T* operator->() const
//	{
//		return _ptr;
//	}
//	~SmartPtr()
//	{
//		cout << "delete: " << _ptr << endl;
//		if (_ptr)
//			delete _ptr;
//	}
//private:
//	T* _ptr;
//};
//int divide()
//{
//	int left, right;
//	cin >> left >> right;
//	if (right == 0)
//		throw invalid_argument("除0错误");
//	return left / right;
//}
//void func()
//{
//	//将资源统一交给对象SmartPtr管理，出了作用域自动调用析构函数清理资源
//	SmartPtr<int> p1(new int);
//	SmartPtr<int> p2(new int);
//	SmartPtr<int> p3(new int);
//	cout << divide() << endl;
//}
//int main()
//{
//	try {
//		func();
//	}
//	catch (const exception& e) {
//		cout << e.what() << endl;
//	}
//
//	//但是还有一个问题，这里实现的智能指针拷贝就要出问题了
//	SmartPtr<int> p1(new int);
//	SmartPtr<int> p2(p1);//这里默认的拷贝构造时浅拷贝，同一块空间连续析构两次就会出错
//	//但是深拷贝又无法完成，因为底层无法确定空间是new出来的，还是malloc出来的，无法完成深拷贝
//	return 0;
//}

//C++98中的智能指针，对拷贝构造的处理：资源管理权的转移
namespace king
{
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{}
		auto_ptr(auto_ptr<T>& sp)
			:_ptr(sp._ptr)
		{
			sp._ptr = nullptr;
		}
		T& operator*() const
		{
			return *_ptr;
		}
		T* operator->() const
		{
			return _ptr;
		}
		~auto_ptr()
		{
			cout << "delete: " << _ptr << endl;
			if (_ptr)
				delete _ptr;
		}
	private:
		T* _ptr;
	};
}
////C++98的只能指针是一个失败的设计
//int main()
//{
//	king::auto_ptr<int> ap1(new int);
//	king::auto_ptr<int> ap2(ap1);//C++98中管理权的转移，导致被拷贝对象悬空，调用时出现问题
//	cout << *ap2 << endl;
//	//一旦调用ap1就会出问题，因为C++98是将被拷贝对象管理的资源转移给拷贝对象了，
//	//所以被拷贝对象ap1是悬空的（ap1是空指针）
//	cout << *ap1 << endl;
//
//	return 0;
//}

//boost库中的智能指针：scoped_ptr   shared_ptr    weak_ptr
//C++11的智能指针：	   unique_ptr	shared_ptr    weak_ptr

//unique_ptr和boost中的scoped_ptr原理是一样的，直接禁用拷贝
namespace king
{
	template<class T, class Del>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}
		/*unique_ptr(unique_ptr<T>& sp) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T> up) = delete;*/
		unique_ptr(unique_ptr<T, Del>& sp) = delete;
		unique_ptr<T, Del>& operator=(const unique_ptr<T, Del> up) = delete;
		T& operator*() const
		{
			return *_ptr;
		}
		T* operator->() const
		{
			return _ptr;
		}
		/*~unique_ptr()
		{
			cout << "delete: " << _ptr << endl;
			if (_ptr)
				delete _ptr;
		}*/
		~unique_ptr()
		{
			cout << "Del" << endl;
			Del d;
			if (_ptr)
				 d(_ptr);
		}
	private:
		T* _ptr;
	};
}
//int main()
//{
//	king::unique_ptr<int> up1(new int);
//	king::unique_ptr<int> up2(up1);
//
//	return 0;
//}

//但是如果有需要拷贝的场景，就得用shared_ptr(支持拷贝，引用计数)
//拷贝构造的问题就是两个对象共同管理同一份资源的话，生命周期结束后就会对同一块空间析构两次，引发错误
//所以需要解决共同管理资源时，最后一个析构时才释放资源，可以用引用计数记录有多少个对象管理着同一份资源，
//拷贝构造时对引用计数++，析构时首先对引用计数--，让最后一个对象析构时释放资源

namespace king
{
	//template<class T>
	//class shared_ptr
	//{
	//public:
	//	shared_ptr(T* ptr)
	//		:_ptr(ptr)
	//	{
	//		_RefCount = 1;
	//	}
	//	shared_ptr(shared_ptr<T>& sp)
	//		:_ptr(sp._ptr)
	//	{
	//		sp._RefCount = ++_RefCount;
	//	}

	//	T& operator*() const
	//	{
	//		return *_ptr;
	//	}
	//	T* operator->() const
	//	{
	//		return _ptr;
	//	}
	//	~shared_ptr()
	//	{
	//		if (--_RefCount == 0 && _ptr) {
	//			cout << "delete: " << _ptr << endl;
	//			delete _ptr;
	//		}
	//	}
	//private:
	//	T* _ptr;
	//	static int _RefCount;
	//	//静态的引用计数有一个问题，当有再次构造其他对象时，将引用计数置为1了
	//};
	//template<class T>
	//int shared_ptr<T>::_RefCount = 0;

	//一个资源一个引用计数，在构造时new一个引用计数，这样多个对象管理同一份资源时用的是同一个引用计数
	//新的对象管理新的资源时用的又是一个引用计数
	
	//多线程访问引用计数时，就会引发线程安全问题，所以需要加锁
	// 加锁后shared_ptr是线程安全的
	//但是对资源的访问，智能指针是管不了的，只能由访问资源的人管，因为访问临界资源的地方operator*只是将资源返回
	//给上层
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			:_ptr(ptr), _PtrCount(new int(1)),	_pmtx(new mutex)
		{}
		void AddRef()
		{
			_pmtx->lock();
			++(*_PtrCount);
			_pmtx->unlock();
		}
		void Release()
		{
			bool flag = false;
			_pmtx->lock();
			if (--(*_PtrCount) == 0 && _ptr) {
				cout << "delete: " << _ptr << endl;
				delete _ptr;
				delete _PtrCount;
				flag = true;//当维护资源的最后一个对象要释放时，锁也要释放，但是需要先解锁在释放
			}
			_pmtx->unlock();
			if (flag == true)
				delete _pmtx;
		}
		shared_ptr(shared_ptr<T>& sp)
			:_ptr(sp._ptr),	_PtrCount(sp._PtrCount), _pmtx(sp._pmtx)
		{
			AddRef();
		}
		shared_ptr& operator=(shared_ptr<T>& sp)
		{
			//考虑到不同的对象，维护同一块资源
			//if (this != &sp)
			if (_ptr != sp._ptr)
			{
				Release();
				_ptr = sp._ptr;
				_PtrCount = sp._PtrCount;
				_pmtx = sp._pmtx;
				AddRef();
			}

			return *this;
		}
		T& operator*() const
		{
			return *_ptr;
		}
		T* operator->() const
		{
			return _ptr;
		}
		//返回引用计数
		int use_count()
		{
			return *_PtrCount;
		}
		//返回指向的资源
		T* get()
		{
			return _ptr;
		}
		~shared_ptr()
		{
			Release();
		}
	private:
		T* _ptr;
		int* _PtrCount;
		mutex* _pmtx;
	};

	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr()
			:_ptr(nullptr)
		{}
		weak_ptr(const shared_ptr<T>& sp)
		{
			_ptr = sp.get();
		}
		weak_ptr<T>& operator=(shared_ptr<T>& sp)
		{
			_ptr = sp.get();

			return *this;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr = nullptr;//weakptr不需要引用计数,是对shared_ptr的弱化
	};

}

//int main()
//{
//	king::shared_ptr<int> up1(new int);
//	king::shared_ptr<int> up2(up1);
//	up1 = up2;//另类的自己给自己赋值
//
//	king::shared_ptr<int> up3(up2);
//	king::shared_ptr<int> up4(new int);
//	up1 = up4;
//	
//
//	return 0;
//}

//struct Date
//{
//	int _year = 0;
//	int _month = 0;
//	int _day= 0;
//};
//void Shared_Func(king::shared_ptr<Date>& sp, mutex& mtx, int cnt)
//{
//	for (int i = 0; i < cnt; ++i)
//	{
//		king::shared_ptr < Date> copy(sp);
//		{
//			unique_lock<mutex> uq(mtx);
//			copy->_day++;
//			copy->_month++;
//			copy->_year++;
//		}
//		//当后面还有代码要执行且没有线程安全问题时，可以提前解锁，除了调用unlock还可以加个匿名域
//		//....
//		//cout<<"xxxx"<<endl;
//		//.....
//	}
//}
//int main()
//{
//	king::shared_ptr<Date> sp(new Date);
//	mutex mtx;
//	thread th1(Shared_Func, std::ref(sp), std::ref(mtx), 1000000);
//	thread th2(Shared_Func, std::ref(sp), std::ref(mtx), 1000000);
//	cout << "delete: " << sp.get() << endl;
//	th1.join();
//	th2.join();
//
//	cout << sp->_year << endl;
//	cout << sp->_month << endl;
//	cout << sp->_day << endl;
//	cout << "引用计数: " << sp.use_count() << endl;
//
//	return 0;
//}

//shared_ptr的循环引用问题：两个智能指针对象管理着两块不同的资源，但是各自对象中又有智能指针管理着对方管理的资源
//就像两个女孩互相扯着对方头发，一方说你先松手我就松手，另一方也说你先松手我就松手
//struct ListNode
//{
//	ListNode()
//	{}
//	int val = 0;
//	//shared_ptr<ListNode> _prev;
//	//shared_ptr<ListNode> _prev;
//	king::weak_ptr<ListNode> _prev;
//	king::weak_ptr<ListNode> _next;
//	~ListNode()
//	{
//		cout << "~ListNode()" << endl;
//	}
//};
//
//int main()
//{
//	king::shared_ptr<ListNode> n1(new ListNode);
//	king::shared_ptr<ListNode> n2(new ListNode);
//	cout << n1.use_count() << endl;
//	cout << n2.use_count() << endl;
//	n1->_next = n2;
//	n2->_prev = n1;
//	cout << n1.use_count() << endl;
//	cout << n2.use_count() << endl;
//
//	return 0;
//}

template<class T>
struct Del
{
	void operator()(T* p)
	{
		delete[] p;//指定用delete[]释放资源
	}
};

struct D
{
	void operator()(FILE* p)
	{
		fclose(p);//关闭打开的文件，释放系统质押UN
	}
};

//定址删除器
int main()
{
	shared_ptr<int> sp(new int[100], [](int* p) {delete[] p; });
	king::unique_ptr <int, Del<int>> up1(new int[100]);
	king::unique_ptr<FILE, D> up2(fopen("test.txt", "w"));

	return 0;
}