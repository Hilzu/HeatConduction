#ifndef UTILS_H
#define UTILS_H
int is_set(int, char**, char);
void initialize_array(Array* arr, double top, double right, double bottom, double left);
int get_number(char* string, int* pos);
void get_dimensions(int, char**, int*);
void get_temperatures(int, char**, int*);
void print_help();
void swap_ptrs(void** ptr1, void** ptr2);
#endif  /* UTILS_H */
