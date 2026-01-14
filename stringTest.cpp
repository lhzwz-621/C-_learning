#define  _CRT_SECURE_NO_WARNINGS 1
#include"string.h"

namespace bit
{
	//string& string::operator=(const string& s)
	//索引
	char& string::operator[](size_t pos)
	{
		assert(pos < _size);
		return _str[pos];
	}
	const char& string::operator[](size_t pos) const
	{
		assert(pos < _size);
		return _str[pos];
	}
	void string::clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}
	void string::swap(string& s)
	{
		std::swap(_str, s._str);
		std::swap(_capacity, s._capacity);
		std::swap(_size, s._size);
	}

	//modify
	void string::reserve(int n)//扩容
	{
		if (n > _capacity)
		{
			char* tmp = new char[ n + 1];
			strcpy(tmp, _str);
			delete[]_str;
			_str = tmp;
			_capacity = n;
		}
	}
	void string::push_back(char c)//尾插
	{
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		_str[_size] = c;
		_size++;
		_str[_size] = '\0';
	}

	string& string::operator += (char c)
	{
		push_back(c);
		return *this;
	}

	void string::append(const char* str)
	{
		size_t len = strlen(str);
		if (_capacity < _size + len)
		{
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}
		strcpy(_str + _size, str);
		_size += len;
	}

	string& string::operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	//指定位置插入
	void string::insert(size_t pos, char ch)
	{
		assert(pos <= _size);
		if (_capacity == _size)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		int end = _size;
		while (end >= (int)pos)//注意0的情况，因为size_t类型为负数会转变为size_t类型的最大值
		{
			_str[end + 1] = _str[end];
			end--;
		}
		_str[pos] = ch;
		++_size;
	}

	void string::insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (len + _size > _capacity)
		{
			reserve(len + _size > 2 * _capacity ? len + _size : 2 * _capacity);
		}
		int end = _size+len;
		while (end>=pos+len)
		{
			_str[end] = _str[end-len];
			end--;
		}
		for (size_t i = 0; i < len; i++)
		{
			_str[pos + i] = str[i];
		}
		_size += len;
	}

	//指定位置删除
	void string::erase(size_t pos,size_t len)
	{
		assert(pos < _size);
		if (len >= _size - pos)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			int begin = pos;
			while (begin + len <= _size)
			{
				_str[begin] = _str[begin + len];
				begin++;
			}

		}
		_size -= len;
	}

	size_t string::find(char ch, size_t pos)
	{
		for (size_t i = pos; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return npos;
	}

	size_t string::find(const char* str, size_t pos)
	{
		assert(pos < _size);
		const char* ptr = strstr(_str + pos, str);
		if (ptr == nullptr)
		{
			return npos;
		}
		else
		{
			return ptr - _str;
		}
	}

	string string::substr(size_t pos, size_t len)
	{
		assert(pos < _size);
		if (len > _size - pos)
		{
			len = _size - pos;
		}

		string tmp;
		tmp.reserve(len);
		for (size_t i = pos; i < pos + len; i++)
		{
			tmp += _str[i];
		}
		return tmp;
	}
	//函数重载
	bool string::operator<(const string& s)
	{
		return strcmp(this->c_str(), s.c_str()) < 0;
	}

	bool string::operator<=(const string& s)
	{
		return *this < s && *this == s;
	}

	bool string::operator>(const string& s)
	{
		return strcmp(this->c_str(), s.c_str()) > 0;
	}

	bool string::operator>=(const string& s)
	{
		return *this > s && *this == s;
	}

	bool string::operator==(const string& s)
	{
		return strcmp(this->c_str(), s.c_str()) ==0;
	}

	bool string::operator!=(const string& s)
	{
		return !(*this == s);
	}

	//输入流、输出流
	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto& ch : s)
		{
			out << ch;
		}
		return out;
	}
	istream& operator>>(istream& in, string& s)
	{
		s.clear();
		const int N = 1024;
		char buff[N];
		char ch;
		int i = 0;
		//in >> ch;
		ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == N - 1)
			{
				buff[N] = '\0';
				s += buff;

				i = 0;
			}
			//in >> ch;
			ch = in.get();
		}
		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}
		return in;
	}
}




