#include <stdio.h>
#include "grid.h"
#include "solver.h"

int main(int argc, char **argv)
{
    struct grid *g;
    struct match m;
    int r;

    if(argc != 3)
    {
        fprintf(stderr, "usage: %s <grid_file> <word>\n", argv[0]);
        return 2;
    }
    g = grid_load(argv[1]);
    if(g == NULL)
    {
        fprintf(stderr, "error: cannot load grid\n");
        return 2;
    }
    word_upper(argv[2]);
    r = solver(g, argv[2], &m);
    if(r)
    {
        printf("(%d,%d)(%d,%d)\n", m.x0, m.y0, m.x1, m.y1);
    }
    else
    {
        printf("Not Found\n");
    }
    grid_free(g);
    return 0;
}
