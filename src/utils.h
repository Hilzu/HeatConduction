#ifndef UTILS_H
#define UTILS_H
int is_default(int, char**);
void initialize_array(Array* arr, double top, double right, double bottom, double left);
void print_help();
void swap_ptrs(void* ptr1, void* ptr2);
#endif  /* UTILS_H */
