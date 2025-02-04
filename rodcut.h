#ifndef RODCUT_H
#define RODCUT_H

#include "vec.h"


typedef int PieceLength;
typedef int PieceValue;

typedef struct {
    PieceLength length;
    PieceValue value;
} PieceLengthValue;

typedef struct{
    Vec rod_cuts;
    int remainder;
    int total_value;
} Results;

Vec read_list();
Results calculate_max_value(Vec pieces, int rod_length);

#endif