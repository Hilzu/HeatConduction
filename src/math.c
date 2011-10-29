#include <stdio.h>
#include "array.h"
#include "math.h"
#include "utils.h"

double calculate_point_temp(const Array* arr, const unsigned int row, const unsigned int column)
{
  const double a = get_val(arr, row - 1, column);
  const double b = get_val(arr, row + 1, column);
  const double c = get_val(arr, row, column - 1);
  const double d = get_val(arr, row, column + 1);
  return (a + b + c + d) * 0.25;        // This equals dividing with 4
}

double calculate_iteration(const Array* from, Array* to, const double divisor)
{
  double sum = 0;
  for (unsigned int row = 1; row < ((from->height) - 1); ++row) {
    for (unsigned int col = 1; col < ((from->width) - 1); ++col) {
      *get_el_ptr(to, row, col) = calculate_point_temp(from, row, col);
      sum += get_val(to, row, col);
    }
  }
  return sum * divisor;
}

/*
 * This is the only fuction you should be using
 */
double calculate_heatconduct(Array* arr, const unsigned int max_iters)
{

  if (max_iters == 0 || arr->width < 3 || arr->height < 3)
    return -1;

  Array* temp_arr = new_array(arr->width, arr->height);
  copy_array(arr, temp_arr);
  
  const double mean_divisor = 1.0 / ((arr->width - 2) * (arr->height * 2));
  
  double prev_mean = -1;
  for (unsigned int i = 0; i < max_iters; ++i) {
    double new_mean = calculate_iteration(arr, temp_arr, mean_divisor);

    swap_ptrs((void**) &arr, (void**) &temp_arr);

    //printf("Iter: %d Mean: %.15f\n", i + 1, new_mean);


    if (fabs(new_mean - prev_mean) < 0.0000000000001) {
      printf("Found balance after %d iterations.\n", i);
      del_array(temp_arr);
      return new_mean;
    }

    prev_mean = new_mean;
  }
  del_array(temp_arr);
  printf("Didn't find balance after %d iterations.\n", max_iters);
  return prev_mean;
}

double fabs(const double x)
{
  if (x < 0)
    return -x;
  return x;
}
