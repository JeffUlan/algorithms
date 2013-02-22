/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * RANDOM-SELECT
 *
 * Features:
 * 1. select the smallest k-th element
 * 2. will modify orignal list
 *
 * http://en.wikipedia.org/wiki/Order_statistic
 *
 ******************************************************************************/

#ifndef __RANDOM_SELECT_H__
#define __RANDOM_SELECT_H__

/**
 * the random_select partition routine
 */
static inline int 
__partition(int list[],int begin, int end)
{
	int pivot_idx = choose_pivot(begin,end);
    int pivot = list[pivot_idx];
	swap(list[begin],list[pivot_idx]);

	int i = begin + 1;
	int j = end;
  
	while(i <= j)
	{
		while((i <= end) && (list[i] <= pivot))
			i++;
		while((j >= begin) && (list[j] > pivot))
			j--;
		if(i < j)
			swap(list[i],list[j]);
	}
      
	swap(list[begin],list[j]);
	return j; // final pivot position
}

/**
 * select the k-th smallest number in 'list' of range [begin, end]
 */
static inline int 
random_select(int list[], int begin, int end, int k)
{
	if(begin == end)
		return begin;
   
	int pivot_idx = __partition(list, begin, end);
	int human_idx = pivot_idx - begin + 1;

	if(k == human_idx)
		return pivot_idx;
	if(k < human_idx)
		return random_select(list, begin, pivot_idx - 1, k);
	if(k > human_idx)
		return random_select(list, pivot_idx+1, end, k - human_idx);
}

#endif //
