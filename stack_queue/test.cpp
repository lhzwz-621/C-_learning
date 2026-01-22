#define  _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<list>
using namespace std;

#include"Stack.h"
#include"Queue.h"
#include"priority_queue.h"
namespace bit
{
	void test1()
	{
		stack<int, vector<int>> st;

		//类模板实例化时，是按需实例化，使用哪些成员函数，就实例化哪些成员函数
		st.push(1);
		st.push(2);
		st.push(3);
		st.push(4);

		st.pop();

		queue<int, list<int>> q;
		q.push(1);
		q.push(2);
		q.push(3);
		q.push(4);

	}
	void test2()
	{
		priority_queue<int,vector<int>,less<int>> pq;
		pq.push(1);
		pq.push(9);
		pq.push(2);
		pq.push(2);
		pq.push(4);
		while (!pq.empty())
		{
			cout << pq.top() << " ";
			pq.pop();
		}
		cout << endl;
	}
}


int main()
{
	//bit::test1();
	bit::test2();
	return 0;
}