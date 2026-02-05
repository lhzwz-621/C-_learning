#pragma once
#include<iostream>
using namespace std;

enum Color//枚举颜色
{
	Red,
	Black
};

template <typename K,typename V>
struct RBTreeNode
{
	pair<K, V> _kv;
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;
	Color _color;
	RBTreeNode(const pair<K,V>& kv)
		:_kv(kv)
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		, _color(Red)//默认新节点为红色
	{ }
};

template<typename K,typename V>
class RBTree
{
	using Node = RBTreeNode<K, V>;
public:
	RBTree()
		:_root(nullptr)
	{
	}
	~RBTree()
	{
		Destroy(_root);
		_root = nullptr;
	}
	//插入
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)//如果树为空，直接插入
		{
			_root = new Node(kv);
			_root->_color = Black;
			return true;
		}
		//找到插入位置
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;//不允许插入重复键
			}
		}
		cur = new Node(kv);//创建新节点
		//链接父节点
		if (parent->_kv.first<kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;

		while (parent && parent->_color == Red)//修正红黑树性质,只有当父节点为红色时才需要修正
		{
			Node* grandparent = parent->_parent;
			//判断parent是grandparent的左孩子还是右孩子

			if (grandparent->_left == parent)//parent是左孩子
			{
				Node* uncle = grandparent->_right;
				//情况1：叔叔结点存在且为红色
/*
					 g(黑)                 g(红) < --cur 变成 g，继续往上查
					/ \                     / \
			   (红)p   u(红) == = >    (黑)p   u(黑)
				  /                      /
			(红)cur                 (红)cur
*/
				if (uncle && uncle->_color == Red)
				{
					grandparent->_color = Red;
					parent->_color = uncle->_color = Black;
					//继续往上调整
					cur = grandparent;
					parent = cur->_parent;
				}
				else//情况2：叔叔结点不存在或为黑色
				{
					/*
									LL型：
															g(黑)                    p(黑)
														   / \           单旋       /    \
													   p(红)  u(黑/空)  =====>  cur(红)  g(红)
														/                                  \
													  cur(红)                               u(黑/空)
									注：省略了parent和grandparent的父节点以及parent的右子树
					*/
					if (parent->_left == cur)
					{
						grandparent->_color = Red;
						parent->_color = Black;
						//右旋
						RotateR(grandparent);
						//由于平衡恢复，退出循环
						break;
					}
					/*
									LR型：
												g(黑)                    g(黑)                 cur(黑)
											   /  \                     /  \                  /  \
										   (红)p   u(黑/空) ====>  (红)cur  u(黑/空) ====> (红)p  g(红)
											   \                   /                                \
											   cur(红)           p(红)                              u(黑/空)
									注：省略了grandparent的父节点以及parent的左子树
					*/
					else
					{
						grandparent->_color = Red;
						cur->_color = Black;
						RotateL(parent);
						RotateR(grandparent);
						//由于平衡恢复，退出循环
						break;
					}
				}
			}
			else//parent是grandparent的右孩子
			{
				Node* uncle = grandparent->_left;
				//情况1：叔叔结点存在且为红色
				if (uncle && uncle->_color == Red)
				{
					grandparent->_color = Red;
					parent->_color = uncle->_color = Black;
					//继续往上调整
					cur = grandparent;
					parent = cur->_parent;
				}
				else//情况2：叔叔结点不存在或为黑色
				{
					//RR型
					if (parent->_right == cur)
					{
						grandparent->_color = Red;
						parent->_color = Black;
						RotateL(grandparent);
						break;
					}
					//RL型
					else
					{
						grandparent->_color = Red;
						cur->_color = Black;
						RotateR(parent);
						RotateL(grandparent);
						break;
					}
				}
			}
		}
		_root->_color = Black;//根节点始终为黑色
		return true;
	}
	//右旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//旋转过程
		subL->_right = parent;
		parent->_left = subLR;
		//判断subLR是否为空
		if (subLR)
		{
			subLR->_parent = parent;
		}
		//处理parent的父节点
		Node* parentParent = parent->_parent;
		parent->_parent = subL;
		//判断parent是否为根节点
		if (parentParent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if(parentParent->_left== parent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}
	}

	//左旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		//旋转过程
		subR->_left = parent;
		parent->_right = subRL;
		//判断subRL是否为空
		if (subRL)
		{
			subRL->_parent = parent;
		}
		//处理parent的父节点
		Node* parentParent = parent->_parent;
		parent->_parent = subR;
		//判断parent是否为根节点
		if (parentParent == nullptr)
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
	}





	//查找
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}

	bool IsBalanced()
	{
		if (_root == nullptr)
			return true;

		if (_root->_color == Red)
			return false;//根节点必须为黑色

		Node* cur = _root;
		int RefNum = 0;//参考黑色节点数

		//循环找到一条从根节点到叶子节点的路径，计算黑色节点数
		while (cur)
		{
			if (cur->_color == Black)
			{
				RefNum++;
			}
			cur = cur->_left;
		}
		return CheckRBTree(_root, 0, RefNum);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	bool CheckRBTree(Node* root, int BlackNum, const int RefNum)//采用递归方式检查每一条路径的黑色节点数是否相等
	{
		if (root == nullptr)
		{
			if (BlackNum == RefNum)
			{
				return true;
			}
			return false;
		}

		if (root->_color == Black)
		{
			BlackNum++;
		}
		if (root->_color == Red)
		{
			//判断是否有连续的红色节点
			if (root->_parent && root->_parent->_color == Red)
			{
				return false;
			}
		}
		return CheckRBTree(root->_left, BlackNum, RefNum) &&
			CheckRBTree(root->_right, BlackNum, RefNum);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << " ";
		_InOrder(root->_right);
	}

	void Destroy(Node* root)
	{
		if (root == nullptr)
			return;
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}
	Node* _root;
};