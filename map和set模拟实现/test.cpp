#define  _CRT_SECURE_NO_WARNINGS 1

#include"RBTree.h"
#include"mymap.h"
#include"myset.h"

namespace bit
{
	void test_set()
	{
		set<int> s;
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		for (auto e : a)
		{
		 s.Insert(e);
		 }
	     for (auto e : s)
		 {
			cout << e << " ";
		 }
		cout << endl;
		
		Print(s);
		 }

	void test_map()
		{
		    map<string, string> dict;
		    dict.Insert({ "sort", "ÅÅÐò" });
		    dict.Insert({ "left", "×ó±ß" });
		    dict.Insert({ "right", "ÓÒ±ß" });
		    dict["left"] = "×ó±ß£¬Ê£Óà";
		    dict["insert"] = "²å?";
		    dict["string"];
			map<string, string>::iterator it = dict.begin();
		    while (it != dict.end())
			{
			// ²»ÄÜÐÞ¸Äfirst£¬¿ÉÒÔÐÞ¸Äsecond
			//it->first += 'x';
			it->second += 'x';
			
		    cout << it->first << ":" << it->second << endl;
		    ++it;
		    }
		    cout << endl;
		}
}



int main()
{
	bit::test_map();
	bit::test_set();
	return 0;
}