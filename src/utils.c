#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "array.h"
#include "utils.h"

Conf conf = {
  .defaults_flag = 0,
  .help_flag = 0,
  .verbose_flag = 0,
  .multiplier = 0,
  .max_iters = 0,
  .height = 0,
  .width = 0,
  .top_temp = 0,
  .left_temp = 0,
  .bottom_temp = 0,
  .right_temp = 0
};

void initialize_array(Array* arr, double top, double right, double bottom, double left)
{
  for (unsigned int i = 0; i < arr->width; ++i) {
    *get_el_ptr(arr, 0, i) = top;
    *get_el_ptr(arr, arr->height - 1, i) = bottom;
  }
  for (unsigned int i = 0; i < arr->height; ++i) {
    *get_el_ptr(arr, i, 0) = left;
    *get_el_ptr(arr, i, arr->width - 1) = right;
  }
  double set = (top + right + bottom + left) / 4;
  for (unsigned int i = 1; i < arr->height - 1; ++i) {
    for (unsigned int k = 1; k < arr->width - 1; ++k) {
      *get_el_ptr(arr, i, k) = set;
    }
  }
}

void print_help()
{
  printf("Usage: ./HeatConduction [options]\n\n");
  printf("HeatConduction - a schoolproject made in c. Purpose is to calculate conductivity\nof heat in an object. Important information about object should be known, like\nshape and what temperature is on the edges. You can also specify how accurate\nshould the result be and how many points should it use to calculate. Bigger\nmeans more accurate result. Default values: 1:2 times 100 (100x200) where\ntemperatures are as follows: 0:1000:1000:1000\n\n");
  printf("Options:\n");
  printf("-d\t\tRun the program with default settings as described ^.\n");
  printf("-h\t\tShow this help message and exit\n");
  printf("-W WIDTH\tRatio of width.\n");
  printf("-H HEIGHT\tratio of height.\n");
  printf("-t TEMP\t\tTemperature at top of object in Kelvins.\n");
  printf("-l TEMP\t\tTemperature left of object in Kelvins.\n");
  printf("-b TEMP\t\tTemperature at bottom of object in Kelvins.\n");
  printf("-r TEMP\t\tTemperature right of object in Kelvins.\n");
  printf("-i ITERATIONS\tMaximum number of iterations.\n");
  printf("-m MULTIPLIER\tTimes that width and height ratios are multiplied.\n");
  printf("-v\t\tPrint more information about calculation.\n");
  printf("\nHeatConduct (C) 2011 Fail Team\n");
}

void swap_ptrs(void** ptr1, void** ptr2)
{
  void* temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
}

void parse_options(int argc, char** argv)
{
  int opt;
  while ((opt = getopt(argc, argv, "dhm:W:H:t:l:b:r:i:v")) != -1) {
    switch (opt) {
    case 'd':
      conf.defaults_flag = 1;
      break;
    case 'h':
      conf.help_flag = 1;
      break;
    case 'm':
      conf.multiplier = atoi(optarg);
      break;
    case 'W':
      conf.width = atoi(optarg);
      break;
    case 'H':
      conf.height = atoi(optarg);
      break;
    case 't':
      conf.top_temp = atoi(optarg);
      break;
    case 'l':
      conf.left_temp = atoi(optarg);
      break;
    case 'b':
      conf.bottom_temp = atoi(optarg);
      break;
    case 'r':
      conf.right_temp = atoi(optarg);
      break;
    case 'i':
      conf.max_iters = atoi(optarg);
      break;
    case 'v':
      conf.verbose_flag = 1;
      break;
    default:
      conf.help_flag = 1;
      break;
    }
  }
}

void set_defaults()
{
  conf.multiplier = 100;
  conf.max_iters = 100;
  conf.height = 2;
  conf.width = 1;
  conf.top_temp = 0;
  conf.left_temp = 1000;
  conf.bottom_temp = 1000;
  conf.right_temp = 1000;
}

void check_conf()
{
  if (conf.multiplier < 1) {
    printf("Multiplier can't be less than 1!\n");
    exit(0);
  }
  if (conf.max_iters < 1) {
    printf("Max iterations can't be less than 1!\n");
    exit(0);
  }
  if (conf.height < 1) {
    printf("Height ratio can't be less than 1!\n");
    exit(0);
  }
  if (conf.width < 1) {
    printf("Width ratio can't be less than 1!\n");
    exit(0);
  }
}