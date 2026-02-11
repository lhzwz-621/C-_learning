#pragma once
#include"HashiTable.h"

namespace bit
{
	template<typename K,typename Hash=HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename hash_bucket::HashTable<K, K, SetKeyOfT, Hash>::iterator iterator;
		typedef typename hash_bucket::HashTable<K, K, SetKeyOfT, Hash>::const_iterator const_iterator;

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

		pair<iterator, bool> Insert(const K& key)
		{
			return _ht.Insert(key);
		}

		iterator Find(const K& key)
		{
			return _ht.Find(key);
		}

		bool Erase(const K& key)
		{
			return _ht.Erase(key);
		}
	private:
		hash_bucket::HashTable<K, K, SetKeyOfT, Hash>_ht;
	};
}