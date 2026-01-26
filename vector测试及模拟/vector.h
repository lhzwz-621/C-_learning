#pragma once
#include<assert.h>
#include <iostream>
#include<vector>
using namespace std;


namespace bit
{
	template<typename T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		//构造函数
		vector() :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
		{}


		vector(size_t n,const T& val=T()) 
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}
		//类模板的成员函数，还可以继续是函数模板
		//区间构造
		//任意类型的迭代器都可以
		template<typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
            while(first!=last)
			{
				push_back(*first);
				++first;
			}
		}
		//拷贝构造函数
		vector(const vector<T>& v)
		{
			reserve(v.size());//提前分配好空间，避免多次扩容
			for (auto& e : v)
			{
				push_back(e);
			}
		}
		//析构函数
		~vector()
		{
			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_endOfStorage = nullptr;
		}

		void clear()
		{
			_finish = _start;
		}

		iterator begin()
		{
			return _start;
		}

		const_iterator begin()const
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator end()const
		{
			return _finish;
		}
		
		size_t capacity()const
		{
			return _endOfStorage - _start;
		}
		

		size_t size()const
		{
			return _finish - _start;
		}


		bool empty() const
		{
			return _start == _finish;
		}

		void reserve(size_t n)//扩容
		{
			if (n > capacity())
			{
				size_t old_size = size();
				T* tmp = new T[n];
				//浅拷贝，因为T类型不确定，不能调用T的拷贝构造函数
				// 如果T中有指针成员，浅拷贝会出问题
				//memcpy(tmp, _start, size() * sizeof(T));
				for (size_t i = 0; i < size(); i++)//深拷贝,循环调用T的拷贝构造函数
				{
					tmp[i] = _start[i];
				}
				delete[] _start;
				_start = tmp;
				_finish = _start + old_size;//size()中的_start已经变了，所以要重新计算
				_endOfStorage = _start + n;
			}
		}


		//尾插
		void push_back(const T& val)
		{
			if (_finish == _endOfStorage)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}
			*_finish = val;
			++_finish;
		}

		//尾删
		void pop_back()
		{
			assert(size() > 0);
			--_finish;
		}
		//插入
		iterator insert(iterator pos, const T& val)//返回新插入元素的位置
		{
			assert(pos <= _finish && pos >= _start);
			size_t len = pos - _start;

			if (_finish == _endOfStorage)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());//如果扩容，地址发生改变，迭代器失效
			}
			pos = _start + len;
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}
			*pos = val;
			++_finish;
			return pos;
		}

		void insert(iterator pos, const T& val, int n)//在pos位置插入n个val
		{
			assert(pos <= _finish && pos >= _start);
			size_t len = pos - _start;
			while (size() + n > capacity())
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());//如果扩容，地址发生改变，迭代器失效
			}
			pos = _start + len;
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + n) = *end;
				--end;
			}
			for (size_t i = 0; i < n; ++i)
			{
				*(pos + i) = val;
			}
			_finish += n;
		}
		//删除
		iterator erase(iterator pos)//
		{
			assert(pos >= _start && pos < _finish);
			iterator it = pos;
			while (it < _finish - 1)
			{
				*it = *(it + 1);
				it++;
			}
			_finish--;
			return pos;
		}

		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endOfStorage, v._endOfStorage);
		}

		//vector<T>& operator=(const vector<T>& v)
		//{
		//	if (this != &v)//防止自赋值
		//	{
		//		clear();
		//		reserve(v.size());
		//		for (auto& e : v)
		//		{
		//			push_back(e);
		//		}
		//	}
		//	return *this;
		//}

		vector<T>& operator=(vector<T> v)//传值方式，调用深拷贝构造函数，给副本新的空间，然后交换，不会改变原来对象的数据
		{
			swap(v);
			return *this;
		}

		void resize(size_t n, const T& val = T())//改变大小
		{
			if (n <= size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n < capacity())
				{
					while (_finish != _start + n)
					{
						*_finish=val;
						_finish++;
					}
				}
				else
				{
					reserve(n);
					while (_finish != _start + n)
					{
						*_finish = val;
						_finish++;
					}
				}
			}
		}


	private:
		iterator _start=nullptr;
		iterator _finish = nullptr;//指向最后一个元素的下一个位置
		iterator _endOfStorage = nullptr;//指向容量的最后一个位置的下一个位置
	};

	template<typename T>
	void printVector(const vector<T>& v)
	{
		//规定：没有实例化类模板，就不能使用类内的类型，因为编译器不能区分const_iterator是类内类型还是静态成员
		typename vector<T>::const_iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;

	}

}

