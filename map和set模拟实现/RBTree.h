#pragma once
#include<iostream>
using namespace std;

enum Color//枚举颜色
{
	Red,
	Black
};

template <typename T>
struct RBTreeNode
{
	T _data;
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Color _color;
	RBTreeNode(const T& data)
		:_data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _color(Red)//默认新节点为红色
	{
	}
};

template<typename T,typename Ref,typename Ptr>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> Self;
	Node* _node;
	Node* _root;//迭代器需要知道树的根节点，以便在--操作时找到最大节点
	RBTreeIterator(Node* node,Node* root)
		:_node(node)
		,_root(root)
	{}

	Self& operator++()
	{
		if (_node->_right)
		{
			//如果右子树不为空，找到右子树的最左节点
			Node* leftMost = _node->_right;
			while (leftMost->_left)
			{
				leftMost = leftMost->_left;	
			}
			_node = leftMost;
		}
		else
		{
			//右子树为空，向上找到第一个祖先结点，其左子树也是该祖先节点的祖先
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && parent->_right == cur)//只有祖先结点存在且当前结点是祖先结点的右孩子时，继续向上查找
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;//找到的祖先结点就是下一个节点，可能为nullptr
		}
		return *this;//*this是迭代器对象本身的引用,改变了_node的值后返回迭代器对象本身,以便支持链式调用
	}
		
	Self& operator--()
	{
		//需要先检查_node是否为nullptr，如果是nullptr，说明迭代器已经越过了最后一个元素，此时需要找到树的最大节点
		if (_node == nullptr)
		{
			Node* cur = _root;
			while (cur->_right)
			{
				cur = cur->_right;
			}
			_node = cur;
		}
		else if (_node->_left)
		{
			//如果左子树不为空，找到左子树的最右节点
			Node* rightMost = _node->_left;
			while (rightMost->_right)
			{
				rightMost = rightMost->_right;
			}
			_node = rightMost;
		}
		else
		{
			//左子树为空，向上找到第一个祖先结点，其右子树也是该祖先节点的祖先
			Node* cur = _node;
			Node* parent = cur->_parent;

			while (parent && parent->_left == cur)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	//解引用
	Ref operator*()
	{
		return _node->_data;
	}

	//用于访问成员
	Ptr operator->()
	{
		return &_node->_data;
	}

	//
	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}

	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}
};




template<typename K, typename T,typename KeyOfT>
class RBTree
{
	using Node = RBTreeNode<T>;
public:
	typedef RBTreeIterator<T, T&, T*> iterator;
	typedef RBTreeIterator<T, const T&, const T*> const_iterator;

	iterator begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)//加上cur的非空判断，避免树为空时访问空指针
		{
			cur = cur->_left;
		}
		return iterator(cur, _root);//调用迭代器的构造函数创建一个指向最左节点的迭代器
	}

	iterator end()
	{
		return iterator(nullptr, _root);//end迭代器指向nullptr，表示越过最后一个元素
	}

	const_iterator begin() const
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return const_iterator(cur, _root);
	}

	const_iterator end() const
	{
		return const_iterator(nullptr, _root);
	}


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
	pair<iterator,bool> Insert(const T& data)
	{
		if (_root == nullptr)//如果树为空，直接插入
		{
			_root = new Node(data);
			_root->_color = Black;
			return make_pair(iterator(_root, _root), true);
		}

		KeyOfT kot;
		//找到插入位置
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(iterator(cur, _root), false);//不允许插入重复键
			}
		}
		cur = new Node(data);//创建新节点
		Node* newNode = cur;
		//链接父节点
		if (kot(parent->_data) < kot(data))
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
		return make_pair(iterator(newNode, _root), true);
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
	iterator Find(const K& key)
	{
		Node* cur = _root;
		KeyOfT kot;
		while (cur)
		{
			if (kot(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else if (kot(cur->_data) > key)
			{
				cur = cur->_left;
			}
			else
			{
				return iterator(cur, _root);
			}
		}
		return iterator(nullptr, _root);
	}


private:

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