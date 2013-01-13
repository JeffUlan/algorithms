#ifndef __2D_ARRAY_H__
#define __2D_ARRAY_H__
#include <stdint.h>
#include <stdlib.h>

struct Array2D
{
	uint32_t nrow;
	uint32_t ncol;
	int * data;
};


inline struct Array2D * array2d_create(uint32_t nrow, uint32_t ncol)
{
	struct Array2D * arr = (struct Array2D *)malloc(sizeof(struct Array2D));
	arr->nrow = nrow;
	arr->ncol = ncol;
	
	arr->data = (int *)malloc(nrow * ncol * sizeof(int));

	return arr;
}

inline void array2d_destroy(struct Array2D * array)
{
	free(array->data);
	free(array);
}

inline int array2d_get(struct Array2D * array, uint32_t row, uint32_t col)
{
	return array->data[array->ncol * row + col];
}

inline void array2d_set(struct Array2D * array, uint32_t row, uint32_t col, int value)
{
	array->data[array->ncol * row + col] = value;
}

#endif //
