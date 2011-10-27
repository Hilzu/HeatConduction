#include <stdio.h>

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
