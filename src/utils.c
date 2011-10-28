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
    *get_el_ptr(arr, 0, i) = top;
    *get_el_ptr(arr, arr->height-1, i) = bottom;
  }
  for (unsigned int i=0; i< arr->height; ++i)
  {
    *get_el_ptr(arr, i, 0) = left;
    *get_el_ptr(arr, i, arr->width-1) = right;
  }
  double set = (top+right+bottom+left)/4;
  for (unsigned int i=1; i< arr->height - 1; ++i)
  {
    for (unsigned int k=1; k< arr->width - 1; ++k)
    {
      *get_el_ptr(arr, i, k) = set;
    }
  }
}

void print_help()
{
  printf("Usage: ./HeatConduction [options]\n\n");
  printf("HeatConduction - a schoolproject made in c. Purpose is to calculate conductivity\nof heat in an object. Important information about object should be known, like\nshape and what temperature is on the edges. You can also specify how accurate\nshould the result be and how many points should it use to calculate. Bigger\nmeans more accurate result. Default values: 1:2 times 1000 (1000x2000) where\ntemperatures are as follows: 0:1000:1000:1000\n\n");
  printf("Options:\n");
  printf("-d\t\tRun the program with default settings as described ^.\n");
  printf("-h\t\tShow this help message and exit\n");
  //printf("-a ACCURACY\taccuracy parameter to control end result\n");
  printf("-s WIDTH:HEIGHT\tHow is the box scaled. For example: 2:1 (means 2mx1m dimension\n\t\tobject)\n");
  printf("-m MULTIPLIER\tHow many times is the scale multiplied by. \n\t\tBigger number = more accurate result.\n");
  //printf("-h HEIGHT\tHeight of the object examined\n");
  //printf("-w WIDTH\tWidth of the object examined\n");
  printf("-t TOP:RIGHT:BOTTOM:LEFT\n");
  printf("\t\tAssign temperature value to corresponding place. ");
  printf("Example: \n\t\t\"-t 1000:0:50:200\" where the numbers are Kelvins.\n");
  printf("HeatConduct (C) 2011 Fail Team\n");
}
