#define  _CRT_SECURE_NO_WARNINGS 1
#include"BinarySearchTree.h"
#include<string>

int main()
{	
	//using Node = key::BSTNode<int>;

	//key::BSTree<int> tree;
	//tree.insert(5);
	//tree.insert(3);
	//tree.insert(7);
	//tree.insert(2);
	//tree.insert(4);
	//tree.InOrder();//2 3 4 5 7
	//int key;
	//cin >> key;
	//Node* ret = tree.find(key);
	//if (ret)
	//{
	//	printf("Found: %d\n", ret->_key);
	//}
	//else
	//{
	//	printf("Not Found\n");
	//}

	//tree.erase(3);
	//tree.InOrder();//2 4 5 7

	// ×ÖµäÊ÷²âÊÔ
	keyAndval::BSTree<string, string> dict;
	dict.Insert("left", "×ó±ß");
	dict.Insert("right", "ÓÒ±ß");
	dict.Insert("insert", "²åÈë");
	dict.Insert("string", "×Ö·û´®");

	string str;
	while (cin >> str)
	{
		auto ret = dict.find(str);
		if (ret)
		{
			cout << "->" << ret->_value << endl;
		}
		else
		{
			cout << "ÎÞ´Ëµ¥´Ê£¬ÇëÖØÐÂÊäÈë" << endl;
			break;
		}
	}
	return 0;
}