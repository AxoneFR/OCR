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
int solver(const struct grid *grid, const char *word,
    struct match *match);
//Function that finds the first letter of the word, then check the 8 directions
#endif
