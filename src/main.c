#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "utils.h"
#include "math.h"

int main(int argc, char** argv)
{
  if (is_set(argc, argv, 'h'>0) && argc == 1) {
    print_help();
    return 0;
  } else if (is_set(argc, argv, 'd')) {
    Array* arr = new_array(1000, 2000);
    printf("Making array of size 1000x2000...\n");
    //print_arr(arr);

    initialize_array(arr, 0, 1000, 1000, 1000);
    printf("Initializing array with side temperatures of 0 1000 1000 1000...\n");
    //print_arr(arr);

    double mean_temp = calculate_heatconduct(arr, 1000);
    printf("Calculating temperatures for 1000 iterations...\n");
    //print_arr(arr);

    printf("Mean temperature: %10.5f\n", mean_temp);

  } else {
    int args[4] = {0};

    get_dimensions(argc, argv, args);
    Array* arr = new_array(args[0],args[1]);
    printf("Making array of size %dx%d...", args[0], args[1]);

    get_temperatures(argc, argv, args);
    initialize_array(arr, args[0], args[1], args[2], args[3]);
    printf("Initializing array with side temperatures of %d %d %d %d...\n", args[0], args+1, 2[args], 3+args);

    double mean_temp = calculate_heatconduct(arr, 1000);
    printf("Calculating temperatures for 1000 iterations...\n");

    printf("Mean temperature: %10.5f\n", mean_temp);
  }
  return 0;
}
