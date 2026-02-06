#pragma once
#include"RBTree.h"

namespace bit
{
	template<typename K,typename V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::const_iterator const_iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		const_iterator begin() const
		{
			return _t.begin();
		}

		const_iterator end() const
		{
			return _t.end();
		}

		pair<iterator,bool> Insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}

		iterator Find(const K& key)
		{
			return _t.Find(key);
		}

		V& operator[](const K& key)
		{
			auto ret = _t.Insert(make_pair(key, V()));//如果key不存在，插入一个默认值为V()的键值对
			return ret.first->second;
			return ret.first->second;//这里面的->是迭代器的成员访问运算符，返回一个指向pair<const K, V>的指针，通过->second访问到值
			//本来应该是ret.first->->second,但是省略了一个
		}
	private:
		RBTree<K, pair<const K, V>, MapKeyOfT> _t;
	};
}