#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

namespace bit
{
	template<typename T>
	struct list_node//结点类
	{
		T _data;  //数据
		list_node<T>* _next;  //指向下一个结点指针
		list_node<T>* _prev;  //指向前一个结点指针

		list_node(const T& data=T())
			:_data(data)
			, _next(nullptr)
			, _prev(nullptr)
		{
		};
	};

	template<typename T,class Ref,class Ptr>
	struct list_iterator//迭代器类
	{
		typedef list_node<T> node;
		typedef list_iterator<T,Ref,Ptr> self;
		node* _node;//指向结点的指针

		list_iterator(node* n)
			:_node(n)
		{};

		Ref operator*()//重载解引用运算符
		{
			return _node->_data;
		}

		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Ptr operator->()
		{
			return &_node->data;
		}

		bool operator!=(const self& it)
		{
			return _node != it._node;
		}

		bool operator==(const self& it)
		{
			return _node == it._node;
		}
	};


	//template<typename T>
	//struct list_const_iterator//迭代器类
	//{
	//	typedef list_node<T> node;
	//	typedef list_const_iterator<T> self;
	//	node* _node;//指向结点的指针

	//	list_const_iterator(node* n)
	//		:_node(n)
	//	{
	//	};

	//	const T& operator*()//重载解引用运算符
	//	{
	//		return _node->_data;
	//	}

	//	self& operator++()
	//	{
	//		_node = _node->_next;
	//		return *this;
	//	}

	//	self& operator--()
	//	{
	//		_node = _node->_prev;
	//		return *this;
	//	}

	//	const T* operator->()
	//	{
	//		return &_node->data;
	//	}

	//	bool operator!=(const self& it)
	//	{
	//		return _node != it._node;
	//	}

	//	bool operator==(const self& it)
	//	{
	//		return _node == it._node;
	//	}
	//};


	template<typename T>//双向循环链表
	class list
	{
		typedef list_node<T> node;
	public:
		//迭代器
		typedef list_iterator<T,T&,T*> iterator;
		typedef list_iterator<T,const T&,const T*> const_iterator;
		iterator begin()
		{
			return iterator(_head->_next);//匿名对象，返回第一个有效结点
			//return _head->next;//隐式转换
		}

		iterator end()
		{
			return iterator(_head);//匿名对象，返回尾后结点（哨兵结点）
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);//匿名对象，返回第一个有效结点
			//return _head->next;//隐式转换
		}

		const_iterator end() const
		{
			return const_iterator(_head);//匿名对象，返回尾后结点（哨兵结点）
		}
		void empty_init()//初始化链表
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		list()//构造函数,先创建一个头结点（哨兵结点）
		{
			empty_init();
		}

		list(const list<T>& lt)//
		{
			empty_init();
			for (auto e : lt)
			{
				push_back(e);
			}
		}

		void swap(list<T>& lt)
		{
			std::swap(lt._head, _head);
			std::swap(lt._size, _size);
		}

		list<T>& operator=( list<T> lt)
		{
			swap(lt);
			return *this;
		}


		void push_back(const T& x)//尾插
		{
			//node* newNode = new node(x);
			//node* tail = _head->_prev;

			//tail->_next = newNode;
			//newNode->_prev = tail;
			//newNode->_next = _head;
			//_head->_prev = newNode;

			//_size++;

			insert(end(), x);
		}

		void insert(iterator pos,const T& x)//在指定位置前插入
		{
			node* cur = pos._node;
			node* prev = cur->_prev;
			node* newNode = new node(x);

			newNode->_next = cur;
			newNode->_prev = prev;
			prev->_next = newNode;
			cur->_prev = newNode;

			_size++;
		}

		void push_front(const T& x)//头插
		{
			insert(begin(), x);
		}

		void pop_front()//头删
		{
			erase(begin());
		}

		void pop_back()//尾删
		{
			erase(--end());
		}

		~list()//析构函数
		{
			clear();
			delete _head;
			_head = nullptr;
			_size = 0;
		}

		void clear()//清空链表
		{
			auto it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}



		iterator erase(iterator pos)
		{
			assert(pos != end());//不能删除尾后结点
			node* cur = pos._node;
			node* prev = cur->_prev;
			prev->_next = cur->_next;
			cur->_next->_prev = prev;
			delete pos._node;

			_size--;

			return iterator(prev->_next);
		}


		size_t size() const//获取链表长度
		{
			return _size;
		}

		bool empty() const//判断链表是否为空
		{
			return _size == 0;
		}
	private:
		node* _head;
		size_t _size;//链表长度
	};

	template<class Container>
	void print_container(const Container& con)
	{
		//const iterator ->迭代器本身不能修改
		//const_iterator ->指向内容不能修改
		list<int>::const_iterator it = con.begin();
		while (it != con.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}