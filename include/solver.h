#ifndef SOLVER_H
#define SOLVER_H
#include "grid.h"

struct match
{
    int x0;
    int y0;
    int x1;
    int y1;
};

void word_upper(char *word);
int solve_word(const struct grid *grid, const char *word,
    struct match *match);//This function repairs a first letter of a word and check every direction

#endif
