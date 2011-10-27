#include <stdio.h>
#include "array.h"
#include "utils.h"

int is_default(int argc, char** argv)
{
  for (int i=1;i<argc;++i)
  {
    if (argv[i][0] == '-')
      if (argv[i][1] == 'd')
        return 1;
  }
  return 0;
}

void initialize_array(Array* arr, double top, double right, double bottom, double left)
{
  for (unsigned int i=0; i < arr->width; ++i)
  {
    *get_val(arr, 0, i) = top;
    *get_val(arr, arr->height-1, i) = bottom;
  }
  for (unsigned int i=0; i< arr->height; ++i)
  {
    *get_val(arr, i, 0) = left;
    *get_val(arr, i, arr->width-1) = right;
  }
  double set = (top+right+bottom+left)/4;
  for (unsigned int i=1; i< arr->height - 1; ++i)
  {
    for (unsigned int k=1; k< arr->width - 1; ++k)
    {
      *get_val(arr, i, k) = set;
    }
  }
}

void print_help()
{
  printf("Usage: ./HeatConduction [options]\n\n");
  printf("HeatConduction - a schoolproject made in c. Purpose is to calculate conductivity of heat in an object.\n\n");
  printf("Options:\n");
  printf("-d\t\tRun the program with default settings as described ^.\n");
  printf("-h\t\tShow this help message and exit\n");
  printf("-a ACCURACY\taccuracy parameter to control end result\n");
  printf("-h HEIGHT\tHeight of the object examined\n");
  printf("-w WIDTH\tWidth of the object examined\n");
  printf("-t TOP:RIGHT:BOTTOM:LEFT\n");
  printf("\t\tAssign temperature value to corresponding place\n");
  printf("\t\tExample: \"-t 1000:0:50:200\" where the numbers are\n");
  printf("\t\tKelvins.\n\n");
  printf("HeatConduct (C) 2011 Fail Team\n");
}
