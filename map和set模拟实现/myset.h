#pragma once
#include"RBTree.h"

namespace bit
{
	template<typename K>
	class set
	{
		struct setKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename RBTree<K, const K, setKeyOfT>::iterator iterator;
		typedef typename RBTree<K, const K, setKeyOfT>::const_iterator const_iterator;
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

		pair<iterator,bool> Insert(const K& key)
		{
			return _t.Insert(key);
		}

		iterator Find(const K& key)
		{
			return _t.Find(key);
		}
	private:
		RBTree<K, const K, setKeyOfT> _t;
	};

	void Print(const set<int>& s)
	{
		set<int>::const_iterator it = s.end();
		while (it != s.begin())
		{
			--it;
			// 不⽀持修改
			//*it += 2;
			cout << *it << " ";
		}
		cout << endl;
	}
}