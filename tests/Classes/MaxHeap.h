#ifndef _MAXHEAP_H
#define _MAXHEAP_H

template <typename T>
class MaxHeap
{
public:
	MaxHeap()
		: data()
	{}

	template <typename Tx>
	MaxHeap(Tx&& param)
		: data(std::forward<Tx>(param))
	{}

	template <typename Tx>
	MaxHeap& operator = (Tx&& param)
	{
		data = std::forward<Tx>(param);
		return *this;
	}

	~MaxHeap()
	{}

	//insert 是否调整
	template <typename Tx>
	void Insert(Tx&& param, bool badjust)
	{
		data.emplace_back(std::forward<Tx>(param));
		if (badjust)
		{
			unsigned int index = data.size() / 2;
			if (index > 0)
				AdjustOne(index, true);
		}
	}

	void PrintSelf()
	{
		std::for_each(std::begin(data), std::end(data), [](const T& element){
			std::cout << element << " ";
		});
		std::cout << std::endl;
	}

	bool CheckData()
	{
		unsigned int datacount = data.size() / 2;
		for (unsigned int i = 0; i < datacount; ++i)
		{
			if ((i + 1) * 2 + 1 > datacount) //没有右子
			{
				if (data[(i + 1) * 2 - 1] > data[i])
					return false;
			}
			else
			{
				if (data[(i + 1) * 2 - 1] > data[i] || data[(i + 1) * 2] > data[i])
					return false;
			}
		}
		return true;
	}

	void AdjustAll()
	{
		unsigned int datacount = data.size() / 2;
		for (unsigned int i = 0; i < datacount; ++i)
		{
			AdjustOne(i + 1, true);
		}
	}

	//推出根节点并加入一个新的节点
	template <typename Tx>
	void Select(Tx&& param)
	{
		if (data[0] > param)
		{
			data[0] = std::forward<Tx>(param);
			AdjustOne(1, false);
		}
	}

private:
	//调整一个子树
	//director 向上或向下调整，true上，false下
	void AdjustOne(unsigned int index, bool director)
	{
		unsigned int swap_idx = 0; //交换的节点
		if (index * 2 > data.size()) //index是叶子
		{
			if (director == true && index != 1)
				AdjustOne(index / 2, director);
			return;
		}
		else if (index * 2 == data.size()) //只有一个左孩子
		{
			if (data[index - 1] > data[index * 2 - 1])
				return;
			else
				swap_idx = index * 2;
		}
		else
		{
			if (data[index - 1] > data[index * 2 - 1] && data[index - 1] > data[index * 2])
				return;
			else if (data[index * 2 - 1] > data[index * 2])
				swap_idx = index * 2;
			else
				swap_idx = index * 2 + 1;
		}
		//交换
		std::swap(data[index - 1], data[swap_idx - 1]);
		if (director == true)
		{
			if (index == 1) //根
				return;
			else
				AdjustOne(index / 2, director);
		}
		else
			AdjustOne(swap_idx, director);
	}

private:
	std::vector<T> data;
};

#endif