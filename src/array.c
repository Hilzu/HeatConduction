#include <stdlib.h>
#include <stdio.h>
#include "array.h"

Array* new_array(unsigned int width, unsigned int height)
{
  Array* arr_ptr = malloc(sizeof (Array) + width * height * (sizeof (double)));
  arr_ptr->width = width;
  arr_ptr->height = height;
  allocate_zeroes(arr_ptr);
  return arr_ptr;
}

void allocate_zeroes(Array* arr_ptr)
{
  for (unsigned long int i = 0; i < arr_ptr->width * arr_ptr->height; i++) {
    arr_ptr->arr[i] = 0;
  }
}

void del_array(Array* arr_ptr)
{
  free(arr_ptr->arr);
  free(arr_ptr);
  arr_ptr = NULL;
}

double* get_val(Array* arr_ptr, unsigned int row, unsigned int col)
{
  unsigned int index = 0;
  index = row * arr_ptr->width + col;
  return &(arr_ptr->arr[index]);
}

void print_arr(Array* arr_ptr)
{
  for (unsigned int row = 0; row < arr_ptr->height; row++) {
    for (unsigned int col = 0; col < arr_ptr->width; col++) {
      printf("%5.3f ", *get_val(arr_ptr, row, col));
    }
    printf("\n");
  }
}

void arr_test()
{
  Array* arr = new_array(10, 10);
  printf("w: %d h: %d\n", arr->width, arr->height);

  print_arr(arr);

  double* dblptr = get_val(arr, 0, 0);
  printf("uninitialized 0,0: %f\n", *dblptr);
  *dblptr = 3;
  printf("val of dblptr 0,0: %f\n", *dblptr);
  printf("val of get_val 0,0: %f\n", *get_val(arr, 0, 0));

  dblptr = get_val(arr, 9, 9);
  printf("uninitialized 9,9: %f\n", *dblptr);
  *dblptr = 11;
  printf("val of dblptr 9,9: %f\n", *dblptr);
  printf("val of get_val 9,9: %f\n", *get_val(arr, 9, 9));

  print_arr(arr);

  allocate_zeroes(arr);
  printf("val of get_val after zero alloc 9,9: %f\n", *get_val(arr, 9, 9));

  print_arr(arr);
}