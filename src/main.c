#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "utils.h"
#include "math.h"

int main(int argc, char** argv)
{
  if (is_default(argc, argv)) {
    Array* arr = new_array(1000, 2000);
    printf("new_array\n");
    //print_arr(arr);
    
    initialize_array(arr, 0, 1000, 1000, 1000);
    printf("init_array\n");
    //print_arr(arr);
    
    double mean_temp = calculate_heatconduct(arr, 1000);
    printf("calculate_array\n");
    //print_arr(arr);
    
    printf("Mean temperature: %10.5f\n", mean_temp);
    
  }
  else if (argc == 1)
  {
    print_help();
    return 0;
  }
  return 0;
}
