#define  _CRT_SECURE_NO_WARNINGS 1
#define  _CRT_SECURE_NO_WARNINGS 1
#include"HashiTable.h"

void testHs()
{
	hash_bucket_first::HashTable<string, int> ht;
	ht.Insert(make_pair("one", 1));
	ht.Insert(make_pair("two", 2));
	ht.Insert(make_pair("three", 3));
	ht.Insert(make_pair("four", 4));
	ht.Insert(make_pair("five", 5));
	ht.Insert(make_pair("six", 6));
	ht.Insert(make_pair("seven", 7));
	ht.Insert(make_pair("eight", 8));
	ht.Insert(make_pair("nine", 9));
	ht.Insert(make_pair("ten", 10));
	auto value = ht.Find("three");
	if (value)
	{
		cout << "Find three: " << value->_kv.second << endl;
	}
	else
	{
		cout << "three not found" << endl;
	}
	value = ht.Find("eleven");
	if (value)
	{
		cout << "Find eleven: " << value->_kv.second << endl;
	}
	else
	{
		cout << "eleven not found" << endl;
	}
}


int main()
{
	//²âÊÔ¹þÏ£±í
	testHs();
	return 0;
}