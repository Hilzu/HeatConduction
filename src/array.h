#ifndef ARRAY_H
#define ARRAY_H

typedef struct _Array {
  unsigned int width;
  unsigned int height;
  double arr[];
}Array;
void init_with_zeroes(Array* arr_ptr);
Array* new_array(unsigned int width, unsigned int height);
void del_array(Array* arr_ptr);
double* get_el_ptr(Array* arr_ptr, unsigned int row, unsigned int col);
void print_arr(Array* arr_ptr);
void arr_test();
void copy_array(Array* from, Array* to);

#endif  /* ARRAY_H */

