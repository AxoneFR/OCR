#ifndef GRID_H
#define GRID_H

struct grid
{
    char **cells;
    int w; //width of grid
    int h; //height of grid
};

struct grid *grid_load(const char *path);//Open the file, count the line and columns + malloc/realloc
void grid_free(struct grid *grid);

#endif
