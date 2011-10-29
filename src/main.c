#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "array.h"
#include "utils.h"
#include "math.h"

int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
    return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) - ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}


int main(int argc, char** argv)
{
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  if (is_set(argc, argv, 'h') > 0 || argc <= 1) {
    print_help();
    return 0;
  } else if (is_set(argc, argv, 'd') > 0) {
    Array* arr = new_array(100, 200);
    //printf("Making array of size 100x200...\n");
    //print_arr(arr);

    initialize_array(arr, 0, 1000, 1000, 1000);
    //printf("Initializing array with side temperatures of 0 1000 1000 1000...\n");
    //print_arr(arr);

    //printf("Calculating temperatures for 100000 iterations...\n");
    double mean_temp = calculate_heatconduct(arr, 1000000);
    //print_arr(arr);
    del_array(arr);


    clock_gettime(CLOCK_MONOTONIC, &end);
    uint64_t timeElapsed = timespecDiff(&end, &start);

    printf("sometime : %ld\n", timeElapsed);
    printf("Mean temperature: %10.5f\n", mean_temp);
    return 0;
  }
  int args[4] = {0};
  get_dimensions(argc, argv, args);
  Array* arr = new_array(args[0],args[1]);
  //printf("Making array of size %dx%d...\n", args[0], args[1]);
  get_temperatures(argc, argv, args);
  initialize_array(arr, args[0], args[1], args[2], args[3]);
  //printf("Initializing array with side temperatures of %d %d %d %d...\n", args[0], *(args+1), 2[args], *(3+args));

  //printf("Calculating temperatures for 100000 iterations...\n");
  double mean_temp = calculate_heatconduct(arr, 1000000);

  clock_gettime(CLOCK_MONOTONIC, &end);
  uint64_t timeElapsed = timespecDiff(&end, &start);

  printf("sometime : %ld\n", timeElapsed);
  del_array(arr);
  printf("Mean temperature: %10.5f\n", mean_temp);
  return 0;
}
