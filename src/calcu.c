/*
 Actual calculation of temperature changes happens in this file.
 */

#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "calcu.h"
#include "utils.h"
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2

/* thread function */

int dividable(int divided_by, int width, int height)
{
  int division = width*height;
  if (division%divided_by == 0)
  {
    if (width%divided_by == 0)
    {
      return 1;
    } else if (height%divided_by == 0) {
      return 2;
    }
  }
  return 0;
}

void give_limits(const thread_data_t* data, int* array)
{
  if (dividable(data->max_threads, (int)data->luettava->width, (int)data->luettava->height) == 1)
  {
    array[0] = (int)data->luettava->width / data->max_threads * data->thread_number;
    array[2] = (int)data->luettava->width / data->max_threads * (data->thread_number +1);
    array[1] = 0;
    array[3] = (int)data->luettava->height;
  }
  else if (dividable(data->max_threads, (int)data->luettava->width, (int)data->luettava->height) == 2)

  {
    array[1] = (int)data->luettava->height / data->max_threads * data->thread_number;
    array[3] = (int)data->luettava->height / data->max_threads * (data->thread_number +1);
    array[0] = 0;
    array[2] = (int)data->luettava->width;
  }
}

void *thr_func(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;
  int calc[4] = { 0 };
  give_limits(data, &(calc[0]));
  printf("we got thread!\nmaxwdth: %u: %d %d\nmaxheight: %u %d %d\n", data->luettava->width, calc[0], calc[2], data->luettava->height, calc[1], calc[3]);
  double* mean = data->mean;

  for (int y = calc[0]; y < calc[2]; ++y)
  {
    for (int x = calc[1]; x < calc[3]; ++x)
    {
      *get_el_ptr(data->kirjoitettava, x, y) = calculate_point_temp(data->luettava, x, y);
      *mean += *get_el_ptr(data->kirjoitettava, x, y);
    }
  }

  pthread_exit(NULL);
}

void calc(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;
  int calc[4] = { 0 };
  give_limits(data, &(calc[0]));
  double* mean = data->mean;

  for (int y = calc[0]; y < calc[2]; ++y)
  {
    for (int x = calc[1]; x < calc[3]; ++x)
    {
      *get_el_ptr(data->kirjoitettava, x, y) = calculate_point_temp(data->luettava, x, y);
      *mean += *get_el_ptr(data->kirjoitettava, x, y);
    }
  }
}


/*
 * Juho Gävert
 Calculates new temperature of a point in Array. New temperature is the mean of
 temperatures of points next to current. Returns the new temperature.
 */
double calculate_point_temp(Array* arr, unsigned int row, unsigned int column)
{
  double a = *get_el_ptr(arr, row - 1, column);
  double b = *get_el_ptr(arr, row + 1, column);
  double c = *get_el_ptr(arr, row, column - 1);
  double d = *get_el_ptr(arr, row, column + 1);
  return (a + b + c + d) / 4;
}

/*
 * Juho Gävert
 Calculates new temperature for all points in Array and stores them in the
 second array. After tempterature calculation, calculates mean temperature of
 all points, excluding edges, and returns it.
 */
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
 * Juho Gävert & Santeri Hiltunen
 Starting point of calculation. Searches for temperature balance in Array for
 maximum iterations of max_iters.
 */
double calculate_heatconduct(Array* arr, unsigned int max_iters)
{

  if (max_iters == 0 || arr->width < 3 || arr->height < 3)
    return -1;

  Array* temp_arr = new_array(arr->width, arr->height);
  copy_array(arr, temp_arr);

  double prev_mean = -1;
  for (unsigned int i = 0; i < max_iters; ++i) {
    double new_mean = calculate_iteration(arr, temp_arr);

    swap_ptrs((void**) &arr, (void**) &temp_arr);

    if (conf.verbose) {
      printf("Iter: %d Mean: %.15f\n", i + 1, new_mean);
      if (conf.verbose > 1) {
        print_arr(arr);
      }
    }

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

/*
 * Santeri Hiltunen
 Returns absolute value of a double variable.
 */
double fabs(double x)
{
  if (x < 0)
    return -x;
  return x;
}

double multithread_heatconduct(Array* arr, unsigned int max_iters)
{
  pthread_t thr[NUM_THREADS-1];
  int i, rc;
  double prev_mean = -1, *mean = 0;
  thread_data_t thr_data[NUM_THREADS];
  printf("woot\n");
  if (dividable(NUM_THREADS, arr->width, arr->height) == 0)
  {
    printf("Fuck, the array wasnt dividable by %d threads\n", NUM_THREADS);
    return EXIT_FAILURE;
  }
  Array* temp_arr = new_array(arr->width, arr->height);
  copy_array(arr, temp_arr);
  printf("woot\n");
  for (i = 0; i < NUM_THREADS; ++i) {
    thr_data[i].thread_number = i;
    thr_data[i].luettava = arr;
    thr_data[i].kirjoitettava = temp_arr;
    thr_data[i].max_threads = NUM_THREADS;
    thr_data[i].mean = mean;
  }
  printf("woot\n");
  for (unsigned int i = 0; i < max_iters; ++i)
  {
    for (i = 0; i < NUM_THREADS-1; ++i) { //excluding mainthread as thread 3
      if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
        fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
        return EXIT_FAILURE;
      }
    }
    /* calculate the same that threads do to increase syncronity */
    calc(&thr_data[NUM_THREADS-1]);
    /* block until all threads complete */
    for (i = 0; i < NUM_THREADS-1; ++i) {
      pthread_join(thr[i], NULL);
    }
    double new_mean = *mean / ((arr->width-2) * (arr->height-2));
    swap_ptrs((void**) &arr, (void**) &temp_arr);
    if (conf.verbose) {
      printf("Iter: %d Mean: %.15f\n", i + 1, new_mean);
      if (conf.verbose > 1) {
        print_arr(arr);
      }
    }
    if (fabs(new_mean - prev_mean) < 0.0000000000001) {
      printf("Found balance after %d iterations.\n", i);
      del_array(temp_arr);
      return new_mean;
    }
    prev_mean = new_mean;
    *mean = 0;
  }
  del_array(temp_arr);
  printf("Didn't find balance after %d iterations.\n", max_iters);
  return prev_mean;
}