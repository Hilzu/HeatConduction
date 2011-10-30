#ifndef CALCU_H
#define CALCU_H

double calculate_point_temp(Array* arr, unsigned int row, unsigned int column);
double calculate_iteration(Array* from, Array* to);
double calculate_mean_temp(Array* arr);
double calculate_heatconduct(Array* arr, unsigned int max_iters);
double fabs(double x);

#endif /* CALCU_H */
