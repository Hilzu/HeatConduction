#ifndef CALCU_H
#define CALCU_H
#include <stdint.h>
/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int thread_number;
  int max_threads;
  double mean;
  int* limits;
  Array** luettava;
  Array** kirjoitettava;
} thread_data_t;

int dividable(int,int,int);
void give_limits(const thread_data_t*);
void *thr_func(void*);
void calc(void*);

double calculate_sum(Array* of);

double calculate_point_temp(Array* arr, unsigned int row, unsigned int column);
double calculate_iteration(Array* from, Array* to);
double calculate_mean_temp(Array* arr);
double calculate_heatconduct(Array* arr, unsigned int max_iters);
double fabs(double x);
double multithread_heatconduct(Array* arr, unsigned int max_iters);
#endif /* CALCU_H */
