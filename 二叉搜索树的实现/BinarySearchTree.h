#pragma once
#include<iostream>
using namespace std;

namespace key
{
	template<typename K>
	struct BSTNode//二叉搜索树节点
	{
		K _key;//键
		BSTNode<K>* left;//左子树
		BSTNode<K>* right;//右子树

		BSTNode(const K& key)
			:_key(key)
			, left(nullptr)
			, right(nullptr)
		{
		}
	};

	template<typename K>
	class BSTree
	{
		typedef BSTNode<K> Node;
	public:
		BSTree()
			:_root(nullptr)
		{
		}
		bool insert(const K& key)
		{
			if (_root == nullptr)//空树
			{
				Node* newNode = new Node(key);
				_root = newNode;
				return true;
			}
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)//比该结点小，往左走
				{
					parent = cur;
					cur = cur->left;
				}
				else if (cur->_key < key)//比该结点大，往右走
				{
					parent = cur;
					cur = cur->right;
				}
				else
				{
					return false;//不允许插入相同的键
				}
			}
			//找到了插入位置
			cur = new Node(key);
			if (parent->_key < key)
			{
				parent->right = cur;
			}
			else
			{
				parent->left = cur;
			}
			return true;
		}

		//中序遍历
		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

		Node* find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->left;
				}
				else if (cur->_key < key)
				{
					cur = cur->right;
				}
				else
				{
					return cur;
				}
			}
			return nullptr;
		}

		bool erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->left;
				}
				else//找到待删结点
				{
					//如果该结点只有0或1个孩子
					//若该节点的左子树为空
					if (cur->left == nullptr)
					{
						//如果该结点是根结点
						if (parent == nullptr)
						{
							_root = cur->right;
						}
						else {
							if (parent->left == cur)
							{
								parent->left = cur->right;
							}
							else
							{
								parent->right = cur->right;
							}
						}
						delete cur;
						return true;
					}
					else if (cur->right == nullptr)//若该节点的右子树为空
					{
						//如果该结点是根节点
						if (parent == nullptr)
						{
							_root = cur->left;
						}
						else
						{
							if (parent->left == cur)
							{
								parent->left = cur->left;
							}
							else
							{
								parent->right = cur->left;
							}
						}
						delete cur;
						return true;
					}
					else//该结点有两个孩子
					{
						//找到待删结点的右子树的最小节点（也可以是左子树的最大节点）
						//用该节点的值覆盖待删结点的值，然后删除该最小节点
						Node* minRightParent = cur;
						Node* minRight = cur->right;

						//找到右子树的最小节点
						while (minRight->left)
						{
							minRightParent = minRight;
							minRight = minRight->left;
						}
						//用该节点的值覆盖待删结点的值
						cur->_key = minRight->_key;

						//删除该最小节点
						//判断原因：存在待删节点的右子树的最小节点可能是待删节点的右孩子，也可能不是
						if (minRightParent->left == minRight)
						{
							minRightParent->left = minRight->right;
						}
						else//minRightParent==cur,待删节点的右节点就是右子树的最小节点
						{
							minRight->right = minRight->right;
						}
						delete minRight;//释放该最小节点
						return true;
					}
				}
			}
			return false;//未找到待删结点
		}
	private:
		void _InOrder(Node* _root)
		{
			if (_root == nullptr)
			{
				return;
			}
			_InOrder(_root->left);
			cout << _root->_key << " ";
			_InOrder(_root->right);
		}
		BSTNode<K>* _root;//根节点
	};
}

namespace keyAndval
{
	template<typename K,typename V>
	struct BSTNode//二叉搜索树节点
	{
		K _key;//键
		V _value;//值
		BSTNode<K,V>* left;//左子树
		BSTNode<K,V>* right;//右子树

		BSTNode(const K& key,const V& value)
			:_key(key)
			, _value(value)	
			, left(nullptr)
			, right(nullptr)
		{
		}
	};

	template<typename K,typename V>
	class BSTree
	{
		typedef BSTNode<K,V> Node;
	public:
		BSTree()
			:_root(nullptr)
		{
		}
		BSTree(const Node& other)//拷贝构造函数
		{
			_root = Copy(other._root);
		}
		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}

		Node* Copy(Node* root)
		{
			if (root == nullptr)
			{
				return nullptr;
			}
			Node* newNode = new Node(root->_key, root->_value);
			newNode->left = Copy(root->left);
			newNode->right = Copy(root->right);
			return newNode;
		}
		bool Insert(const K& key,const V& value)
		{
			if (_root == nullptr)//空树
			{
				Node* newNode = new Node(key,value);
				_root = newNode;
				return true;
			}
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)//比该结点小，往左走
				{
					parent = cur;
					cur = cur->left;
				}
				else if (cur->_key < key)//比该结点大，往右走
				{
					parent = cur;
					cur = cur->right;
				}
				else
				{
					return false;//不允许插入相同的键
				}
			}
			//找到了插入位置
			cur = new Node(key,value);
			if (parent->_key < key)
			{
				parent->right = cur;
			}
			else
			{
				parent->left = cur;
			}
			return true;
		}

		//中序遍历
		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

		Node* find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->left;
				}
				else if (cur->_key < key)
				{
					cur = cur->right;
				}
				else
				{
					return cur;
				}
			}
			return nullptr;
		}

		bool erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->left;
				}
				else//找到待删结点
				{
					//如果该结点只有0或1个孩子
					//若该节点的左子树为空
					if (cur->left == nullptr)
					{
						//如果该结点是根结点
						if (parent == nullptr)
						{
							_root = cur->right;
						}
						else {
							if (parent->left == cur)
							{
								parent->left = cur->right;
							}
							else
							{
								parent->right = cur->right;
							}
						}
						delete cur;
						return true;
					}
					else if (cur->right == nullptr)//若该节点的右子树为空
					{
						//如果该结点是根节点
						if (parent == nullptr)
						{
							_root = cur->left;
						}
						else
						{
							if (parent->left == cur)
							{
								parent->left = cur->left;
							}
							else
							{
								parent->right = cur->left;
							}
						}
						delete cur;
						return true;
					}
					else//该结点有两个孩子
					{
						//找到待删结点的右子树的最小节点（也可以是左子树的最大节点）
						//用该节点的值覆盖待删结点的值，然后删除该最小节点
						Node* minRightParent = cur;
						Node* minRight = cur->right;

						//找到右子树的最小节点
						while (minRight->left)
						{
							minRightParent = minRight;
							minRight = minRight->left;
						}
						//用该节点的值覆盖待删结点的值
						cur->_key = minRight->_key;
						cur->_value = minRight->_value;

						//删除该最小节点
						//判断原因：存在待删节点的右子树的最小节点可能是待删节点的右孩子，也可能不是
						if (minRightParent->left == minRight)
						{
							minRightParent->left = minRight->right;
						}
						else//minRightParent==cur,待删节点的右节点就是右子树的最小节点
						{
							minRight->right = minRight->right;
						}
						delete minRight;//释放该最小节点
						return true;
					}
				}
			}
			return false;//未找到待删结点
		}
	private:
		void Destroy(Node* _root)
		{
			if (_root == nullptr)
			{
				return;
			}
			Destroy(_root->left);
			Destroy(_root->right);
			delete _root;
		}
		void _InOrder(Node* _root)
		{
			if (_root == nullptr)
			{
				return;
			}
			_InOrder(_root->left);
			cout << _root->_key << ":"<<_root->_value<<" ";
			_InOrder(_root->right);
		}
		BSTNode<K,V>* _root;//根节点
	};
}