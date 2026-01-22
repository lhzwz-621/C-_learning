#pragma once

namespace bit
{
	template<typename T, class Container = list<T>>
	class queue
	{
	public:
		void push(const T& x)//入队
		{
			_con.push_back(x);
		}

		void pop()//出队
		{
			_con.pop_front();
		}

		const T& front() const//队头
		{
			return _con.front();
		}

		const T& back() const//队尾
		{
			return _con.back();
		}

		size_t size() const
		{
			return _con.size();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
}