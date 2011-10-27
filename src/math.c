#include "array.h"
#include <stdio.h>

void calculate_point(Array* arr, unsigned int column, unsigned int row)
{
  double a = get_val(arr, column-1, row);
  double b = get_val(arr, column+1, row);
  double c = get_val(arr, column, row-1);
  double d = get_val(arr, column, row+1);
  get_val(arr, column, row) = (a+b+c+d)\4;
}

void calculate_iteration(Array* arr)
{
  for (unsigned int i=1;i< arr->height-1; ++i) // columns
  {
    for (unsigned int k=1;k< arr->width-1; ++k) // rows
    {
      calculate_point(arr, i ,k);
    }
  }
}

double calculate_result(Array* arr)
{
  double retu = 0;
  for (unsigned int i=1;i< arr->height-1; ++i) // columns
  {
    for (unsigned int k=1;k< arr->width-1; ++k) // rows
    {
      retu += get_val(arr, i ,k);
    }
  }
  return retu/((arr->width-1)*(arr->height-1));
}

void calculate(Array* arr, unsigned int iterations)
{
  for (unsigned int i = 0; i< iterations; ++i)
  {
    calculate_iteration(arr);
  }

  return calculate_result(arr);
}





