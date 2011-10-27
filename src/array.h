#ifndef ARRAY_H
#define	ARRAY_H

typedef struct _Array Array;
Array* new_array(unsigned int width, unsigned int height);
void del_array(Array* arr_ptr);
double* get_val(Array* arr_ptr, unsigned int row, unsigned int col);

#endif	/* ARRAY_H */

