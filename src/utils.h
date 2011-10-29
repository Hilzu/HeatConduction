#ifndef UTILS_H
#define UTILS_H
void initialize_array(Array* arr, double top, double right, double bottom, double left);
void print_help();
void swap_ptrs(void** ptr1, void** ptr2);
void parse_options(int argc, char** argv);
void set_defaults();
void check_conf();
typedef struct {
  int defaults_flag;
  int help_flag;
  int verbose_flag;
  unsigned int multiplier;
  unsigned int max_iters;
  unsigned int width;
  unsigned int height;
  double top_temp;
  double left_temp;
  double bottom_temp;
  double right_temp;
}Conf;
Conf conf;
#endif  /* UTILS_H */
