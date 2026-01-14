#pragma once
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

namespace bit
{
	class string
	{
	public:
		//输入流、输出流
		friend ostream& operator<<(ostream& out, const string& s);
		friend istream& operator>>(istream& in, string& s);
		//模拟迭代器
		typedef char* iterator;
		iterator begin() { return _str; };
		iterator end() { return _str + _size; };		
		iterator begin() const { return _str; } ;
		iterator end() const { return _str + _size; };
		//构造函数
		string(const char* str="\0")//不赋空指针是为了防止c_str直接解引用导致程序崩溃
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		//拷贝构造（深度）
		string(const string& s)
		{
			//_str = new char[s._capacity + 1];
			//strcpy(_str, s._str);
			//_capacity = s._capacity;
			//_size = s._size;
			string tmp(s._str);//调用构造函数(替换)
			swap(tmp);
		}
		string& operator=(const string& s)//重载赋值
		{
			if (*this != s)
			{
				string tmp(s._str);
				swap(tmp);
			}
			return *this;
		}
		//析构
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
		//打印
		const char* c_str() const
		{
			return _str;
		}
		// capacity
		size_t size()const
		{
			return _size;
		}
		size_t capacity() const
		{
			return _capacity;
		}

		//索引重载
		char& operator[](size_t pos);//可修改
		const char& operator[](size_t pos) const;//不可修改

		// modify
		void reserve(int n);//扩容
		void push_back(char c);//尾插
		string& operator+=(char c);
		void append(const char* str);
		string& operator+=(const char* str);
		//指定位置插入
		void insert(size_t pos, char ch);
		void insert(size_t pos, const char* str);
		//指定位置删除
		void erase(size_t pos,size_t len);
		void clear();
		void swap(string& s);
		//查找
		size_t find(char ch, size_t pos = 0);
		size_t find(const char* str, size_t pos = 0);
		string substr(size_t pos, size_t len=npos);
		//重载函数
		bool operator<(const string& s);

		bool operator<=(const string& s);

		bool operator>(const string& s);

		bool operator>=(const string& s);

		bool operator==(const string& s);

		bool operator!=(const string& s);
	private:
		char* _str;
		size_t _capacity;
		size_t _size;
		static const size_t npos=-1;
	};
}
