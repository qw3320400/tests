#ifndef _TOOLS_H
#define _TOOLS_H

template <typename IT>
void OneLoopOfFastSort(IT begin, IT end)
{
	if (begin == end) return;
	auto tmp = *begin;
	bool director = false; //·½Ïò
	IT base = begin, i = begin, j = end;

	for (;i != j;)
	{
		if (!director)
		{
			if (tmp > *j)
			{
				*base = *j;
				base = j;
				director = !director;
			}
			else
				--j;
		}
		else
		{
			if (*i > tmp)
			{
				*base = *i;
				base = i;
				director = !director;
			}
			else
				++i;
		}
	}

	if (base != begin)
	{
		*base = tmp;
		IT tmpbase = base;
		OneLoopOfFastSort(begin, --tmpbase);
	}
	if (base != end)
		OneLoopOfFastSort(++base, end);
}

template <typename IT>
void FastSort(IT begin, IT end)
{
	if (begin != end)
		OneLoopOfFastSort(begin, end);
}

#endif