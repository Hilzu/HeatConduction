#ifndef ARRAY_H
#define	ARRAY_H

typedef struct _Array Array;
void allocate_zeroes(Array* arr_ptr);
Array* new_array(unsigned int width, unsigned int height);
void del_array(Array* arr_ptr);
double* get_val(Array* arr_ptr, unsigned int row, unsigned int col);
void print_arr(Array* arr_ptr);
void arr_test();

#endif	/* ARRAY_H */

