#define _POSIX_C_SOURCE 200809L
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grid.h"

void grid_free(struct grid *grid)
{
    int i;

    if(grid == NULL)
    {
        return;
    }
    
    i = 0;
    while(i < grid->h)
    {
        free(grid->cells[i]);
        i++;
    }
    
    free(grid->cells);
    free(grid);
}

//Clean up everything allocated in grid_load
static struct grid *grid_abort(FILE *f, char *l, struct grid *g)
{
    free(l);
    fclose(f);
    grid_free(g);
    return NULL;
}

//Copy one line of n letters as a new row (in uppercase) at the end of g
//Return 0 if an allocation fails
static int grid_add(struct grid *g, const char *l, int n)
{
    char **t;
    char *s;
    int i;

    t = realloc(g->cells, sizeof(char *) * (g->h + 1));
    
    if(t == NULL)
    {
        return 0;
    }
    g->cells = t;
    s = malloc(n + 1);
    
    if(s == NULL)
    {
        return 0;
    }
    
    i = 0;
    while(i < n)
    {
        s[i] = toupper((unsigned char)l[i]);
        i++;
    }
    
    s[n] = '\0';
    g->cells[g->h] = s;
    g->h++;
    
    return 1;
}

//Reads the file line by line using `getline`;
//Since the size of the grid is unknown,
//the array of lines is expanded using `realloc`.
//The width is specified by the first line; all other lines must match it.
// Returns `NULL` if the file cannot be found, is empty, or is malformed...
struct grid *grid_load(const char *path)
{
    FILE *f;
    struct grid *g;
    char *l;
    size_t c;
    ssize_t n;

    f = fopen(path, "r");
    if(f == NULL)
    {
        return NULL;
    }
    
    g = calloc(1, sizeof(struct grid));
    l = NULL;
    c = 0;
    
    while(g != NULL && (n = getline(&l, &c, f)) != -1)
    {
        //Remove the end of line characters
        while(n > 0 && (l[n - 1] == '\n' || l[n - 1] == '\r'))
        {
            n--;
        }
        //Empty lines are ignored
        if(n > 0)
        {
            if(g->h == 0)
            {
                g->w = (int)n;
            }
            if((int)n != g->w || !grid_add(g, l, (int)n))
            {
                return grid_abort(f, l, g);
            }
        }
    }
    
    if(g == NULL || g->h == 0)
    {
        return grid_abort(f, l, g);
    }
    
    free(l);
    fclose(f);
    return g;
}
