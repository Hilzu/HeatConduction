#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "utils.h"
#include "math.h"

int main(int argc, char** argv)
{
  parse_options(argc, argv);

  if (argc == 1 || conf.help_flag) {
    print_help();
    exit(0);
  }

  if (conf.defaults_flag) {
    set_defaults();
  }

  check_conf();

  unsigned int arr_width = conf.width * conf.multiplier;
  unsigned int arr_height = conf.height * conf.multiplier;
  printf("Creating array size of %dx%d.\n", arr_width, arr_height);
  Array* arr = new_array(arr_width, arr_height);

  printf("Initializing with side temps of %f, %f, %f, %f.\n",
          conf.top_temp, conf.right_temp, conf.bottom_temp, conf.left_temp);
  initialize_array(arr, conf.top_temp, conf.right_temp, conf.bottom_temp, conf.left_temp);

  printf("Searching for temp balance with max iterations of %d.\n", conf.max_iters);
  double mean_temp = calculate_heatconduct(arr, conf.max_iters);

  printf("Mean temperature: %f\n", mean_temp);

  return 0;
}
