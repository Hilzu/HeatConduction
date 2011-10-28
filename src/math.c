#include <stdio.h>
#include "array.h"
#include "math.h"

void calculate_point(Array* arr, unsigned int row, unsigned int column)
{
  double a = *get_el_ptr(arr, row-1, column);
  double b = *get_el_ptr(arr, row+1, column);
  double c = *get_el_ptr(arr, row, column-1);
  double d = *get_el_ptr(arr, row, column+1);
  *get_el_ptr(arr, column, row) = ((a+b+c+d)/4);
}

void calculate_iteration(Array* arr)
{
  for (unsigned int i=1;i < ((arr->height) -1); ++i) // rows
  {
    for (unsigned int k=1;k < ((arr->width) -1); ++k) // columns
    {
      calculate_point(arr, i ,k);
    }
  }
}

double calculate_result(Array* arr)
{
  double retu = 0;
  for (unsigned int i=1;i< arr->height-1; ++i) // rows
  {
    for (unsigned int k=1;k< arr->width-1; ++k) // columns
    {
      retu += *get_el_ptr(arr, i ,k);
    }
  }
  return retu/((arr->width-1)*(arr->height-1));
}

/*
 * This is the only fuction you should be using
 */
double calculate_heatconduct(Array* arr, unsigned int iterations)
{
  if (iterations == 0 || arr->width < 3 || arr->height < 3)
    return -1;

  for (unsigned int i = 0; i< iterations; ++i)
  {
    calculate_iteration(arr);
  }

  return calculate_result(arr);
}





