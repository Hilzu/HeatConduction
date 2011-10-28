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
  free(arr_ptr);
  arr_ptr = NULL;
}

double* get_el_ptr(Array* arr_ptr, unsigned int row, unsigned int col)
{
  unsigned int index = 0;
  index = row * arr_ptr->width + col;
  return &(arr_ptr->arr[index]);
}

void print_arr(Array* arr_ptr)
{
  for (unsigned int row = 0; row < arr_ptr->height; row++) {
    for (unsigned int col = 0; col < arr_ptr->width; col++) {
      printf("%4.0f ", *get_el_ptr(arr_ptr, row, col));
    }
    printf("\n");
  }
}

void copy_array(Array* from, Array* to)
{
  if (to->width < from->width) {
    printf("Can't copy to an array with smaller width!");
    exit(1);
  }
  if (to->height < from->height) {
    printf("Can't copy to an array with smaller height!");
    exit(1);
  }

  for (unsigned int row = 0; row < from->height; ++row) {
    for (unsigned int col = 0; col < from->width; ++col) {
      *get_el_ptr(to, row, col) = *get_el_ptr(from, row, col);
    }
  }
}

void arr_test()
{
  Array* arr = new_array(10, 10);
  printf("w: %d h: %d\n", arr->width, arr->height);

  print_arr(arr);

  double* dblptr = get_el_ptr(arr, 0, 0);
  printf("uninitialized 0,0: %f\n", *dblptr);
  *dblptr = 3;
  printf("val of dblptr 0,0: %f\n", *dblptr);
  printf("val of get_val 0,0: %f\n", *get_el_ptr(arr, 0, 0));

  dblptr = get_el_ptr(arr, 9, 9);
  printf("uninitialized 9,9: %f\n", *dblptr);
  *dblptr = 11;
  printf("val of dblptr 9,9: %f\n", *dblptr);
  printf("val of get_val 9,9: %f\n", *get_el_ptr(arr, 9, 9));

  printf("arr1:\n");
  print_arr(arr);
  
  Array* arr2 = new_array(10, 10);
  copy_array(arr, arr2);
  printf("arr2:\n");
  print_arr(arr2);

  allocate_zeroes(arr);
  printf("val of get_val after zero alloc 9,9: %f\n", *get_el_ptr(arr, 9, 9));

  print_arr(arr);

  del_array(arr);
  del_array(arr2);
}
