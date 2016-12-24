// RBTree.h
#ifndef _RBTREE_H
#define _RBTREE_H

template <typename T>
class RBTree
{
private:
	enum class NodeColor
	{
		RED,
		BLACK,
	};

	class RBTreeNode
	{
		friend RBTree;
	private:
		T data;
		NodeColor color;
		RBTreeNode *leftchild;
		RBTreeNode *rightchild;
		RBTreeNode *father;

		~RBTreeNode()
		{}

	public:
		template <typename Tx>
		RBTreeNode(Tx&& data_)
			:data(std::forward<Tx>(data_)), color(NodeColor::RED),
			leftchild(nullptr), rightchild(nullptr), father(nullptr)
		{}

		bool operator < (const RBTreeNode& node_) const
		{
			return data < node_.data;
		}

		bool operator == (const RBTreeNode& node_) const
		{
			return data == node_.data;
		}

		void Release()
		{
			if (leftchild)
				leftchild->Release();
			if (rightchild)
				rightchild->Release();
			delete this;
		}

		void PrintWithDeep(int deep)
		{
			--deep;
			if (deep == 0)
			{
				std::cout << data << ":" << ((color == NodeColor::BLACK) ? "B" : "R") << " ";
				return;
			}
			if (leftchild)
				leftchild->PrintWithDeep(deep);
			if (rightchild)
				rightchild->PrintWithDeep(deep);
		}
	};

public:
	RBTree()
		:treeroot(nullptr), count(0)
	{}

	RBTree(const RBTree&) = delete;

	RBTree& operator = (const RBTree&) = delete;

	RBTree(RBTree &&tree)
		:treeroot(tree.treeroot)
	{
		tree.treeroot = nullptr;
	}

	RBTree& operator = (const RBTree&& tree)
	{
		treeroot = tree.treeroot;
		tree.treeroot = nullptr;
		return *this;
	}

	~RBTree()
	{
		if (treeroot)
			treeroot->Release();
	}

	void PrintSelf()
	{
		int maxdeep = static_cast<int>(std::log2(count)) + 1;
		for (int i = 1; i <= maxdeep; ++i)
		{
			treeroot->PrintWithDeep(i);
			std::cout << std::endl;
		}
	}

	template <typename Tx>
	bool Insert(Tx&& data)
	{
		// create
		RBTreeNode *newnode = new RBTreeNode(std::forward<Tx>(data));
		bool success = InsertImpl(newnode);
		if (success) ++count;
		return success;
	}

private:
	bool InsertImpl(RBTreeNode *newnode)
	{
		// insert
		RBTreeNode *ynode = nullptr;
		RBTreeNode *xnode = treeroot;
		while (xnode)
		{
			ynode = xnode;
			if (*newnode == *xnode) //不重复
			{
				delete newnode;
				return false;
			}
			else if (*newnode < *xnode)
				xnode = xnode->leftchild;
			else
				xnode = xnode->rightchild;
		}
		newnode->father = ynode;
		if (!ynode)
		{
			treeroot = newnode;
			newnode->color = NodeColor::BLACK;
			/*return true;*/
		}
		else if (*newnode < *ynode)
			ynode->leftchild = newnode;
		else
			ynode->rightchild = newnode;
		// fix
		while (newnode->father && newnode->father->color == NodeColor::RED)
		{
			if (newnode->father == newnode->father->father->leftchild)
			{
				ynode = newnode->father->father->rightchild; //叔
				if (ynode && ynode->color == NodeColor::RED) //红叔
				{
					newnode->father->color = NodeColor::BLACK;
					ynode->color = NodeColor::BLACK;
					if (treeroot == newnode->father->father) //
						newnode->father->father->color = NodeColor::BLACK;
					else
						newnode->father->father->color = NodeColor::RED;
					newnode = newnode->father->father;
				}
				else //黑叔或无叔
				{
					if (newnode == newnode->father->rightchild)
					{
						newnode = newnode->father;
						LeftRoate(newnode);
					}
					newnode->father->color = NodeColor::BLACK;
					newnode->father->father->color = NodeColor::RED;
					RightRoate(newnode->father->father);
				}
			}
			else
			{
				ynode = newnode->father->father->leftchild; //叔
				if (ynode && ynode->color == NodeColor::RED) //红叔
				{
					newnode->father->color = NodeColor::BLACK;
					ynode->color = NodeColor::BLACK;
					if (treeroot == newnode->father->father) //
						newnode->father->father->color = NodeColor::BLACK;
					else
						newnode->father->father->color = NodeColor::RED;
					newnode = newnode->father->father;
				}
				else  //黑叔或无叔
				{
					if (newnode == newnode->father->leftchild)
					{
						newnode = newnode->father;
						RightRoate(newnode);
					}
					newnode->father->color = NodeColor::BLACK;
					newnode->father->father->color = NodeColor::RED;
					LeftRoate(newnode->father->father);
				}
			}
		}

		return true;
	}

	void LeftRoate(RBTreeNode *pnode)
	{
		RBTreeNode *tmp = pnode->rightchild; //pnode->rightchild不为null
		pnode->rightchild = tmp->leftchild;
		if (tmp->leftchild)
			tmp->leftchild->father = pnode;
		tmp->father = pnode->father;
		if (!pnode->father)
			treeroot = tmp;
		else if (pnode == pnode->father->leftchild)
			pnode->father->leftchild = tmp;
		else
			pnode->father->rightchild = tmp;
		tmp->leftchild = pnode;
		pnode->father = tmp;
	}

	void RightRoate(RBTreeNode *pnode)
	{
		RBTreeNode *tmp = pnode->leftchild; //pnode->leftchild不为null
		pnode->leftchild = tmp->rightchild;
		if (tmp->rightchild)
			tmp->rightchild->father = pnode;
		tmp->father = pnode->father;
		if (!pnode->father)
			treeroot = tmp;
		else if (pnode == pnode->father->leftchild)
			pnode->father->leftchild = tmp;
		else
			pnode->father->rightchild = tmp;
		tmp->rightchild = pnode;
		pnode->father = tmp;
	}

	void Tests()
	{
		//git test
	}

	RBTreeNode *treeroot;
	int count;
};

#endif