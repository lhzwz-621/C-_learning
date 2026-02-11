#pragma once
#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;

template<typename K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;//默认的哈希函数，直接将键转换为size_t类型
	}
};

template<>
struct HashFunc<string>
{
	size_t operator()(const string& key)//字符串的哈希函数，使用BKDR算法
	{
		size_t hash = 0;
		for (auto ch : key)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};


//链地址哈希表
namespace hash_bucket
{
	//哈希表节点
	template<typename T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;//指向下一个节点的指针

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
		//好像有什么移动语义构造函数，但不会，之后有空学了再补充
	};
	//需要前置声明哈希表类，因为迭代器类中需要使用哈希表类的指针
	template<typename K, typename T, typename KeyOfT, class Hash>
	class HashTable;

	template <typename K,typename T,typename Ref,typename Ptr,typename KeyOfT,typename Hash>
	struct HTIterator
	{
		typedef HashNode<T> Node;
		typedef HTIterator<K, T, Ref, Ptr, KeyOfT, Hash> Self;

		Node* _node;
		const HashTable<K, T, KeyOfT, Hash>* _pht;

		HTIterator(Node* node, const HashTable<K, T, KeyOfT, Hash>* pht)
			:_node(node)
			, _pht(pht)
		{
		}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator==(const Self& it) const
		{
			return _node == it._node;
		}

		bool operator!=(const Self& it) const
		{
			return _node != it._node;
		}

		Self& operator++()
		{
			if (_node->_next)//如果该桶还有结点
			{
				_node = _node->_next;
			}
			else
			{
				//当前桶走完了，找下一个非空桶
				KeyOfT _kot;
				Hash hs;
				//找到当前桶的索引
				size_t hashi = hs(_kot(_node->_data)) % _pht->_tables.size();
				hashi++;//从下一个桶开始找
				while (hashi < _pht->_tables.size() && _pht->_tables[hashi] == nullptr)
				{
					hashi++;
				}
				if (hashi == _pht->_tables.size())//如果找到了最后一个桶还没有找到非空桶，说明迭代器已经到达末尾了
				{
					_node = nullptr;
				}
				else
				{
					_node = _pht->_tables[hashi];
				}
			}

			return *this;
		}
	};

	//哈希表类
	template<typename K, typename T,typename KeyOfT, class Hash>//Hash是仿函数对象，提供哈希函数，用来计算键的哈希值
	class HashTable
	{
		//友元迭代器类需要访问哈希表的私有成员
		template <typename _K, typename _T, typename Ref, typename Ptr, typename _KeyOfT, typename _Hash>	
		friend struct HTIterator;

		typedef HashNode<T> Node;
		
		inline unsigned long __stl_next_prime(unsigned long n)//返回大于等于n的最小质数
		{
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			const unsigned long* first = __stl_prime_list;
			const unsigned long* last = __stl_prime_list + __stl_num_primes;
			const unsigned long* pos = lower_bound(first, last, n);
			return pos == last ? *(last - 1) : *pos;//如果n大于最大的质数，则返回最大的质数
		}

	public:
		typedef HTIterator<K, T, T&, T*, KeyOfT, Hash> iterator;
		typedef HTIterator<K, T, const T&, const T*, KeyOfT, Hash> const_iterator;

		iterator Begin()
		{
			if (_n == 0)//如果哈希表为空，直接返回end迭代器
			{
				return End();
			}
			else
			{
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					if (_tables[i])
					{
						return iterator(_tables[i], this);
					}
				}
				return End();//如果所有桶都为空，返回end迭代器
			}
		}

		iterator End()
		{
			return iterator(nullptr, this);
		}

		const_iterator Begin() const
		{
			if (_n == 0)//如果哈希表为空，直接返回end迭代器
			{
				return End();
			}
			else
			{
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					if (_tables[i])
					{
						return const_iterator(_tables[i], this);
					}
				}
				return End();//如果所有桶都为空，返回end迭代器
			}
		}

		const_iterator End() const
		{
			return const_iterator(nullptr, this);
		}

		HashTable()
		{
			_tables.resize(__stl_next_prime(0), nullptr);//初始化哈希表，大小为大于等于0的最小质数，所有桶都指向nullptr
		}
		//拷贝构造函数，深拷贝哈希表中的所有节点
		HashTable(const HashTable& ht)
		{
			this->_tables.resize(ht._tables.size(), nullptr);
			for (size_t i = 0; i < ht._tables.size(); ++i)
			{
				Node* cur = ht._tables[i];
				if(cur==nullptr)
				{
					continue;//如果桶为空，直接跳过
				}
				else
				{
					while (cur)
					{
						this->Insert(cur->_data);//把旧表中的元素插入到新表中，Insert函数会自动处理哈希值和索引
						cur = cur->_next;
					}
				}
			}
		}

		HashTable& operator=(HashTable ht)
		{
			this->Swap(ht);
			return *this;				
		}

		void Swap(HashTable& other)
		{
			this->_tables.swap(other._tables);
			std::swap(_n, other._n);
		}
		//析构函数，释放哈希表中的所有节点
		~HashTable()
		{
			for (size_t i = 0; i < _tables.size();++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;//把桶指向nullptr，方便后续使用
			}
		}




		pair<iterator,bool> Insert(const T& data)
		{
			KeyOfT _kot;
			Hash hs;//把键转换为哈希值
			iterator it = Find(_kot(data));
			if(it!=End())//如果元素已经存在，插入失败，返回false
			{
				return make_pair(it, false);
			}
			//扩容，如果负载因子==1时，负载因子=元素个数/桶的数量
			if (_n == _tables.size())
			{
				vector<Node*> newTable(__stl_next_prime(_tables.size()+1),nullptr);    //直接创建一个新的桶数组，不需要创建新的哈希表对象
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						//直接移动旧表结点到新表中，效率更好
						Node* next = cur->_next;
						//重新计算哈希值在新表中的索引
						size_t newHashi = hs(_kot(cur->_data)) % newTable.size();
						//头插法插入到新表中
						cur->_next = newTable[newHashi];
						newTable[newHashi] = cur;
						cur = next;
					}
					_tables[i] = nullptr;//旧表的桶指向nullptr，方便后续删除旧表
				}
				_tables.swap(newTable);//交换新表和旧表的桶
			}
			//更新完哈希表再算哈希值，否则可能会导致哈希值在新表中的索引不正确
			size_t hashi = hs(_kot(data)) % _tables.size();//计算哈希值在哈希表中的索引
			//头插结点
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;

			return make_pair(iterator(newnode, this), true);
		}


		iterator Find(const K& key)
		{
			Hash hs;
			KeyOfT _kot;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (_kot(cur->_data) == key)
				{
					return iterator(cur, this);
				}
				cur = cur->_next;
			}
			return End();
		}


		bool Erase(const K& key)
		{
			Hash hs;
			KeyOfT _kot;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			Node* prev = nullptr;
			while (cur)
			{
				if (_kot(cur->_data) == key)//找到要删除掉的节点
				{
					//分两种情况，删除的是头结点还是非头结点
					//所以需要一个prev指针来记录当前节点的前一个节点
					if (prev == nullptr)
					{
						_tables[hashi] = cur->_next;//如果是头结点，直接把桶指向下一个节点
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					--_n;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}
	private:
		vector<Node*> _tables;
		size_t _n = 0;
	};
}










