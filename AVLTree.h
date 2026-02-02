#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template<typename K,typename V>
struct AVLTreeNode//AVL树节点
{
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;//存储父节点，以便于更新平衡因子
	int _bf;//balance factor

	AVLTreeNode (const pair<K,V>& kv)
			:_kv(kv)
			,_left(nullptr)
			,_right(nullptr)
			,_parent(nullptr)
			,_bf(0)
		{ }
};

template<typename K,typename V>
class AVLTree
{
	using Node = AVLTreeNode<K, V>;
public:
	AVLTree()
		:_root(nullptr)
	{ }
	bool Insert(const pair<K, V>& kv)
	{
		if(_root==nullptr)//若为空树
		{
			_root=new Node(kv);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;//用来记录父节点
		while (cur)
		{
			if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;//不允许插入相同关键字
			}
		}
		cur = new Node(kv);
		//插入新节点
		if (parent->_kv.first > kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
			cur->_parent = parent;
			//更新平衡因子
			//循环向上更新每个节点的平衡因子
			//平衡因子=右子树高度-左子树高度
			while (parent)
			{
				if (parent->_left == cur)
				{
					parent->_bf--;//左子树插入节点，平衡因子-1
				}
				else
				{
					parent->_bf++;//右子树插入节点，平衡因子+1
				}

				//判断parent节点的平衡因子
				//1.平衡因子为0，说明parent节点原本是平衡的，现在插入节点后仍然是平衡的，停止更新
				if (parent->_bf == 0)
				{
					break;//停止更新
				}
				else if (parent->_bf == 1 || parent->_bf == -1)//继续向上更新
				{
					cur = parent;
					parent = cur->_parent;
				}
				else if (parent->_bf == 2 || parent->_bf == -2)//不平衡，进行旋转
				{
					//
					if(parent->_bf==2)//右子树高
					{
						if(cur->_bf==1)//RR型
						{
							RotateL(parent);
						}
						else//RL型
						{
							RotateRL(parent);
						}
					}
					else//左子树高
					{
						if(cur->_bf==-1)//LL型
						{
							RotateR(parent);
						}
						else//LR型
						{
							RotateLR(parent);
						}
					}
					break;
				}
				else
				{
					assert(false);
				}
			}
		return true;
	}


/*	
RR型：
         A(失衡, BF = 2)           B(新根)
		/ \                       / \
	   B   E      右单旋         C   A
	  / \       --------->      /   / \
	 C   D                     F   D   E
	/
   F(新插入)

*/
	void RotateR(Node* parent)//右单旋
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		//1.让subL的右子树成为parent的左子树
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		//2.让parent成为subL的右子树
		subL->_right = parent;
		Node* parentParent = parent->_parent;
		parent->_parent = subL;
		//3.连接parent的父节点和subL
		if (parentParent == nullptr)//parent是根节点
		{
			_root = subL;
		}
		else//parent不是根节点
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}
		subL->_bf = parent->_bf = 0;//更新平衡因子
	}

/*
LL型：
	 A (失衡, BF=-2)               B (新根)
	/ \                           / \
   E   B         左单旋          A   C
	  / \       --------->      / \   \
	 D   C                     E   D   F
		  \
		   F (新插入)
*/
	void RotateL(Node* parent)//左单旋
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//1.让subR的左子树成为parent的右子树
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		//2.让parent成为subR的左子树
		subR->_left = parent;
		Node* parentParent = parent->_parent;
		parent->_parent = subR;
		if (parentParent == nullptr)//是根节点
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}
		subR->_bf = parent->_bf = 0;//更新平衡因子
	}

/*
   设F为插入节点
LR:(分三种情况)
  1.C的平衡因子为0
	       A (失衡)              A                C (完美平衡)
		  / \                   / \              / \
		 B   E    先对B左旋    C   E  再对A右旋 B   A
		/ \       ------->    / \     ------>  / \ / \
	   D   C                 B   G            D  F G  E
		  / \               / \
		 F   G             D   F
  2.C的平衡因子为-1
		   A (失衡)              A                C (完美平衡)
		  / \                   / \              / \
		 B   E    先对B左旋    C   E  再对A右旋 B   A
		/ \       ------->    /       ------>  / \   \
	   D   C                 B                D  F    E
	      /                 / \          
		 F                 D   F
  3.C的平衡因子为1
		   A (失衡)              A                 C (完美平衡)
		  / \                   / \               / \
		 B   E    先对B左旋    C   E  再对A右旋  B   A
		/ \       ------->    / \     ------>   /   / \
	   D   C                 B   F             D    F  E
	        \               /
			 F             D
*/
	void RotateLR(Node* parent)//先左后右
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(subL);//对subL左旋
		RotateR(parent);//对parent右旋
		//根据bf更新平衡因子
		if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

/*
  设F为插入节点
RL型：(分三种情况)
  1.C的平衡因子为0
		 A (失衡)                  A                  C (完美平衡)
		/ \                       / \                / \
	   E   B        先对B右旋    E   C    再对A左旋 A   B
		  / \       ------->        / \   ------>  / \ / \
		 C   D                     F   B          E  F G  D
		/ \                           / \
	   F   G                         G   D
  2.C的平衡因子为-1
		 A (失衡)                  A                     C (完美平衡)
		/ \                       / \                   / \
	   E   B        先对B右旋    E   C    再对A左旋    A   B
		  / \       ------->        / \      ------>  / \   \
		 C   D                     F   B             E   F   D
		/                               \
	   F                                 D
  3.C的平衡因子为1
		A (失衡)                  A                  C (完美平衡)
	   / \                       / \                / \
	  E   B        先对B右旋    E   C    再对A左旋 A   B
   		 / \       ------->          \   ------>  /   / \
		C   D                         B          E   F   D
		 \                           / \
		  F                         F   D
*/
	void RotateRL(Node* parent)//先右后左
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(subR);//对subR右旋
		RotateL(parent);//对parent左旋
		//根据bf更新平衡因子
		if (bf == 0)
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	//剩余功能以后有空写，燃尽了

	private:
		Node* _root;
		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_InOrder(root->_left);
			cout << root->_kv.first <<":"<<root->_kv.second << " ";
			_InOrder(root->_right);
		}
};
