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

// 		void PrintWithDeep(int deep)
// 		{
// 			--deep;
// 			if (deep == 0)
// 			{
// 				std::cout << data << ":" << ((color == NodeColor::BLACK) ? "B" : "R") << " ";
// 				return;
// 			}
// 			if (leftchild)
// 				leftchild->PrintWithDeep(deep);
// 			if (rightchild)
// 				rightchild->PrintWithDeep(deep);
// 		}

		void InsertIntoCompleteTree(std::vector<T> *target, unsigned int index)
		{
#ifdef _DEBUG
			assert(target->size() >= index);
#endif	
			(*target)[index - 1] = data;
			if (leftchild)
				leftchild->InsertIntoCompleteTree(target, index * 2);
			if (rightchild)
				rightchild->InsertIntoCompleteTree(target, index * 2 + 1);
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
// 		for (int i = 1; i <= maxdeep; ++i)
// 		{
// 			treeroot->PrintWithDeep(i);
// 			std::cout << std::endl;
// 		}

		//������ɶ�����
		std::vector<T> *completeTree = new std::vector<T>((0x1 << maxdeep) - 1, T());
		treeroot->InsertIntoCompleteTree(completeTree, 1);
		
		int tabcount = (completeTree->size() + 1) / 4;
		for (int i = 0, tar_idx = 0, line_count = 1; i < maxdeep; ++i)
		{
			for (int j = 0; j < tabcount - (line_count / 2 + 1); ++j)
			{
				std::cout << "\t";
			}
			for (int j = 0; j < line_count; ++j)
			{
				std::cout << (*completeTree)[tar_idx] /*<< ":" << ((color == RBTree::NodeColor::BLACK) ? "B" : "R")*/ << "\t";
				++tar_idx;
			}
			line_count = line_count * 2;
			std::cout << std::endl;
		}

		delete completeTree;
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
			if (*newnode == *xnode) //���ظ�
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
				ynode = newnode->father->father->rightchild; //��
				if (ynode && ynode->color == NodeColor::RED) //����
				{
					newnode->father->color = NodeColor::BLACK;
					ynode->color = NodeColor::BLACK;
					if (treeroot == newnode->father->father) //
						newnode->father->father->color = NodeColor::BLACK;
					else
						newnode->father->father->color = NodeColor::RED;
					newnode = newnode->father->father;
				}
				else //���������
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
				ynode = newnode->father->father->leftchild; //��
				if (ynode && ynode->color == NodeColor::RED) //����
				{
					newnode->father->color = NodeColor::BLACK;
					ynode->color = NodeColor::BLACK;
					if (treeroot == newnode->father->father) //
						newnode->father->father->color = NodeColor::BLACK;
					else
						newnode->father->father->color = NodeColor::RED;
					newnode = newnode->father->father;
				}
				else  //���������
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
		RBTreeNode *tmp = pnode->rightchild; //pnode->rightchild��Ϊnull
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
		RBTreeNode *tmp = pnode->leftchild; //pnode->leftchild��Ϊnull
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