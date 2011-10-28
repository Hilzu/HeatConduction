#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "utils.h"
#include "math.h"

int main(int argc, char** argv)
{
  if (asking_help(argc, argv) && argc == 1) {
    print_help();
    return 0;
  } else if (is_default(argc, argv)) {
    Array* arr = new_array(1000, 2000);
    printf("Making array of size 1000x2000\n");
    //print_arr(arr);

    initialize_array(arr, 0, 1000, 1000, 1000);
    printf("Initializing array with side temperatures of 0 1000 1000 1000...\n");
    //print_arr(arr);

    double mean_temp = calculate_heatconduct(arr, 1000);
    printf("Calculating temperatures for 1000 iterations...\n");
    //print_arr(arr);

    printf("Mean temperature: %10.5f\n", mean_temp);

  } else {

  }
  return 0;
}
