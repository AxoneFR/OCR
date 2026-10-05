#include <ctype.h>
#include <string.h>
#include "solver.h"

//The 8 directions as (dx, dy): right, left, down, up and the 4 diagonals
static const int direct[8][2] =
{
    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
};

//The grid is in uppercase so the word has to be in uppercase too
void word_upper(char *word)
{
    int i;

    i = 0;
    while(word[i] != '\0')
    {
        word[i] = toupper((unsigned char)word[i]);
        i++;
    }
}

//We check if the word starts at (x,y) and goes in the direction d
//it first look at the last letter to see if the word fits in the grid,
//then we compare the letters one by one
static int check_d(const struct grid *grid, const char *word,
    int x, int y, int d)
{
    int n;
    int i;
    int u;
    int v;

    n = (int)strlen(word);
    u = x + direct[d][0] * (n - 1);
    v = y + direct[d][1] * (n - 1);
    
    if(u < 0 || u >= grid->w || v < 0 || v >= grid->h)
    {
        return 0;
    }
    
    i = 0;
    while(i < n)
    {
        u = x + direct[d][0] * i;
        v = y + direct[d][1] * i;
        if(grid->cells[v][u] != word[i])
        {
            return 0;
        }
        i++;
    }
    
    return 1;
}

//Find the first letter of the word, then check the 8 directions
//Return 1 and fill match with the first and last letter if its found
int solver(const struct grid *grid, const char *word,
    struct match *match)
{
    int x;
    int y;
    int d;
    int n;

    n = (int)strlen(word);
    
    if(n == 0)
    {
        return 0;
    }
    
    y = 0;
    while(y < grid->h)
    {
        x = 0;
        while(x < grid->w)
        {
            d = 0;
            while(grid->cells[y][x] == word[0] && d < 8)
            {
                if(check_d(grid, word, x, y, d))
                {
                    match->x0 = x;
                    match->y0 = y;
                    match->x1 = x + direct[d][0] * (n - 1);
                    match->y1 = y + direct[d][1] * (n - 1);
                    return 1;
                }
                d++;
            }
            x++;
        }
        y++;
    }
    return 0;
}
