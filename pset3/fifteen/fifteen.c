/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // TODO
    // top left corner starts one less than dimension of the board squared
    int k = (d*d) - 1;
    
    // iterate over entire board
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // insert into board value of counter (being 'k'), then decrement counter
            board[i][j] = k--;
        }
    }
    // '_' or ASCII 95 will represent blank tile
    board[d-1][d-1] = '_';
    
    // if even dimensions, create a solveable board by switching positions of a and 2
    if (d % 2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    // iterate over board
    for (int i = 0; i < d; i++)
    { 
        for (int j = 0; j < d; j++)
        {
            // if current position is blank,  print out "_"
            if (board[i][j] == 95)
            {
                printf(" _ ");
            }
            // else print out value in board
            else
            {
                printf("%2d ", board[i][j]);
            }
        }
    // move to next row
    printf("\n");
    }
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    for(int row = 0; row < d; row++)
    {
        for(int column = 0; column < d; column++)
        {
            if (board[row][column] == tile)
            {   // top of blank
                // if current tile is blank
                if (board[row-1][column] == 95)
                {   
                    // switch blank and tile
                    board[row-1][column] = tile;
                    board[row][column] = 95;
                    return true;
                }
                // left of blank
                // if current tile is blank
                else if (board[row][column-1] == 95)
                {
                    // switch blank and tile
                    board[row][column-1] = tile;
                    board[row][column] = 95;
                    return true;
                }
                // right of blank
                // if current tile is blank
                else if (board[row][column+1] == 95)
                {
                    // switch blank and tile
                    board[row][column+1] = tile;
                    board[row][column] = 95;
                    return true;
                }
                // below blank
                // if current tile is blank
                else if (board[row+1][column] == 95)
                {
                    // switch blank and tile
                    board[row+1][column] = tile;
                    board[row][column] = 95;
                    return true;
                }
                return false;
             }
          }
       }
       return 0;
 }

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
// TODO
    // top left of board is 1
    int count = 1;
    // iterate over board to make sure current tile is equal to current count value
    for(int row = 0; row < d; row++)
    {
        for(int column = 0; column < d; column++)
        {
            // do not check last tile in board b/c it should be blank
            if (row == d-1 && column == d-1)
            {
                continue;
            }
            // check to see that current board position has value stored in counter
            if (board[row][column] != count++) 
            {   
                return false;
            }
        }   
    }
    return true;
}
    

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
