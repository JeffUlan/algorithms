/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * 2-DIMENSIONAL ARRAY
 *
 * Simulated by 1-dimension array.
 ******************************************************************************/
 
#ifndef __2D_ARRAY_H__
#define __2D_ARRAY_H__
#include <stdint.h>
#include <stdlib.h>

/**
 * 2D Array definition
 */
struct Array2D
{
	uint32_t nrow;	// num of rows
	uint32_t ncol;	// num of columns
	int * data;		// the place where the array resides.
};

/**
 * create a 2-D array of size 'nrow' times 'ncol', an new Array2D struct is
 * returned.
 */
static inline struct Array2D * array2d_create(uint32_t nrow, uint32_t ncol)
{
	struct Array2D * arr = (struct Array2D *)malloc(sizeof(struct Array2D));
	
	if (arr!=NULL) {
		arr->nrow = nrow;
		arr->ncol = ncol;
		arr->data = (int *)malloc(nrow * ncol * sizeof(int));
	}

	return arr;
}

/**
 * safely destroy and free array
 */
static inline void array2d_destroy(struct Array2D * array)
{
	free(array->data);
	free(array);
}

/**
 * get value from given row and col
 */
static inline int array2d_get(struct Array2D * array, uint32_t row, uint32_t col)
{
	return array->data[array->ncol * row + col];
}

/**
 * set value to [row, col]
 */
static inline void array2d_set(struct Array2D * array, uint32_t row, uint32_t col, int value)
{
	array->data[array->ncol * row + col] = value;
}

#endif //
