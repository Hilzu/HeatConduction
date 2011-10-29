#ifndef MATH_H
#define MATH_H

double calculate_point_temp(const Array* arr, const unsigned int row, const unsigned int column);
double calculate_iteration(const Array* from, Array* to, const double divisor);
double calculate_heatconduct(Array* arr, const unsigned int max_iters);
double fabs(double x);

#endif /* MATH_H */
