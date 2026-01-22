#pragma once
#include<vector>

namespace bit
{
	template<typename T,class Container =vector<T>,class Compare=less<int>>
	class priority_queue//这是一个优先队列模板类
	{
	private:
		Container _con;
	public:
		void AdjustUp(size_t child)//
		{
			Compare _cmp;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				if (_cmp(_con[parent] , _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void AdjustDown(size_t parent)
		{
			Compare _cmp;
			size_t child = parent * 2 + 1;
			while (child < _con.size())
			{
				if (child + 1 < _con.size() && _cmp(_con[child], _con[child + 1]))
				{
					child++;
				}

				if (_cmp(_con[parent], _con[child]))
				{
					std::swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);
			AdjustUp(_con.size() - 1);
		}
		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown(0);
		}
		const T& top()
		{
			return _con[0];
		}

		bool empty()
		{
			return _con.empty();
		}
	};

	template<typename T>
	class less
	{
	public:
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};

	template<typename T>
	class greater
	{
	public:
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};
}