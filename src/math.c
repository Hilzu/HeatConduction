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
  //return (*get_el_ptr(arr, row - 1, column) + *get_el_ptr(arr, row + 1, column) + *get_el_ptr(arr, row, column - 1) + *get_el_ptr(arr, row, column + 1)) * 0.25;
  return (a+b+c+d) / 4;
}

double calculate_iteration(Array* from, Array* to)
{
  double sum = 0;
  for (unsigned int row = 1; row < ((from->height) - 1); ++row) {
    for (unsigned int col = 1; col < ((from->width) - 1); ++col) {
      *get_el_ptr(to, row, col) = calculate_point_temp(from, row, col);
      sum += *get_el_ptr(to, row, col);
    }
  }
  return sum / ((to->width - 2) * (to->height - 2));
}

/*
 * This is the only fuction you should be using
 */
double calculate_heatconduct(Array* arr, unsigned int max_iters)
{
  if (max_iters == 0 || arr->width < 3 || arr->height < 3)
    return -1;

  Array* temp_arr = new_array(arr->width, arr->height);
  copy_array(arr, temp_arr);

  double prev_mean = -1,new_mean = 0;
  for (unsigned int i = 0; i < max_iters; ++i) {
    new_mean = calculate_iteration(arr, temp_arr);

    swap_ptrs((void**) &arr, (void**) &temp_arr);

    //printf("Iter: %d Mean: %.15f\n", i + 1, new_mean);


    if (fabs(new_mean - prev_mean) < 0.0000000000001) {
      //printf("Found balance after %d iterations.\n", i);
      del_array(temp_arr);
      return new_mean;
    }

    prev_mean = new_mean;
  }
  del_array(temp_arr);
  //printf("Didn't find balance after %d iterations.\n", max_iters);
  return prev_mean;
}

double fabs(double x)
{
  if (x < 0)
    return -x;
  return x;
}
