#define  _CRT_SECURE_NO_WARNINGS 1
#include"AVLTree.h"

// 测试代码
void TestAVLTree1()
{
	AVLTree<int, int> t;
	// 常规的测试⽤例
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	// 特殊的带有双旋场景的测试⽤例
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : a)
	{
	    t.Insert({ e, e });
	 }
	t.InOrder();
}


int main()
{
	TestAVLTree1();
	return 0;
}