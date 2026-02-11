#pragma once
#include"HashiTable.h"

namespace bit
{
	template<typename K,typename V,typename Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename hash_bucket::HashTable<K, pair<K, V>, MapKeyOfT, Hash>::iterator iterator;
		typedef typename hash_bucket::HashTable<K, pair<K, V>, MapKeyOfT, Hash>::const_iterator const_iterator;

		iterator begin()
		{
			return _ht.Begin();
		}

		iterator end()
		{
			return _ht.End();
		}

		const_iterator begin() const
		{
			return _ht.Begin();
		}

		const_iterator end() const
		{
			return _ht.End();
		}

		pair<iterator,bool> Insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}

		iterator Find(const K& key)
		{
			return _ht.Find(key);
		}

		bool Erase(const K& key)
		{
			return _ht.Erase(key);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));//如果key不存在，插入一个默认值，如果key存在，返回对应的迭代器
			return ret.first->second;//语法糖，省略了一个->，直接访问迭代器指向的pair的second成员，即value
		}
	private:
		hash_bucket::HashTable<K, pair<K, V>, MapKeyOfT, Hash> _ht;
	};
}