#include <stdio.h>
#include "array.h"
#include "math.h"
#include "utils.h"

double calculate_point_temp(Array* arr, unsigned int row, unsigned int column)
{
  double a = *get_el_ptr(arr, row - 1, column);
  double b = *get_el_ptr(arr, row + 1, column);
  double c = *get_el_ptr(arr, row, column - 1);
  double d = *get_el_ptr(arr, row, column + 1);
  return (a + b + c + d) / 4;
}

void calculate_iteration(Array* from, Array* to)
{
  for (unsigned int row = 1; row < ((from->height) - 1); ++row) {
    for (unsigned int col = 1; col < ((from->width) - 1); ++col) {
      *get_el_ptr(to, row, col) = calculate_point_temp(from, row, col);
    }
  }
}

double calculate_mean_temp(Array* arr)
{
  double sum = 0;
  for (unsigned int row = 1; row < arr->height - 1; ++row) {
    for (unsigned int col = 1; col < arr->width - 1; ++col) {
      sum += *get_el_ptr(arr, row, col);
    }
  }
  return sum / ((arr->width - 2)*(arr->height - 2));
}

/*
 * This is the only fuction you should be using
 */
double calculate_heatconduct(Array* arr, unsigned int iterations)
{

  if (iterations == 0 || arr->width < 3 || arr->height < 3)
    return -1;

  Array* temp_arr = new_array(arr->width, arr->height);
  copy_array(arr, temp_arr);

  for (unsigned int i = 0; i < iterations; ++i) {
    calculate_iteration(arr, temp_arr);
    swap_ptrs((void**) &arr ,(void**) &temp_arr);
    printf("After iter %d:\n", i + 1);
    print_arr(arr);
  }
  //del_array(temp_arr);

  return calculate_mean_temp(arr);
}





