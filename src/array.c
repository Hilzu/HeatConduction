#include <stdlib.h>
#include "array.h"

struct _Array {
    unsigned int width;
    unsigned int height;
    double arr[];
};

Array* new_array(unsigned int width, unsigned int height)
{
    Array* arr_ptr = malloc(sizeof(Array) + width * height * (sizeof(double)));
    return arr_ptr;
}

void del_array(Array* arr_ptr) {
    free(arr_ptr->arr);
    free(arr_ptr);
    arr_ptr = NULL;
}

double* get_val(Array* arr_ptr, unsigned int row, unsigned int col) {
    unsigned int index = 0;
    index = row * arr_ptr->width + col;
    return &(arr_ptr->arr[index]);
}
