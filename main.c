
// file:  bpgame.c
// Author: Carlos Ruiz Hernandez & Manav Gupta
// UIC CS 211
// Fall 2021


/** #include statements... **/
#include "bpgame.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
/** TYPEDEFS / STRUCTs HERE ***/
#define TRUE 1
#define FALSE 0



struct bpgame {
  char** board;
  int c;
  int r;
  int score;
};

/**
* Function:  bp_create
* Parameters: number of rows and columns
* Description: returns pointer to newly created
*              board with given number of rows
*              and columns.
*
*              Populates board with random balloons.
*
*              If nrows or ncols is out of range, 
*              an error message is printed to stderr
*              and NULL is returned.
*
*/
// BPGame init(int nrows, int ncols){

//   BPGame game;
//   game.board = (char**) malloc ( sizeof (char*) * nrows ); 	

//   for (int i = 0 ; i < nrows ; i++ )	{
//       game.board[i] = (char *) malloc ( sizeof (char) * ncols);
//   }
//   game.r = nrows;
//   game.c = ncols;
//   game.score = 0;
//   game.clustercount = -1;
//   return game;
// }







extern BPGame * bp_create(int nrows, int ncols) {
  srand(time(NULL));
  if (nrows > MAX_ROWS) {
    fprintf(stderr, "Rows out of range");
    return NULL;
  }
  if (nrows > MAX_COLS) {
    fprintf(stderr, "Columns out of range");
    return NULL;
  }
  BPGame* game = (BPGame*) malloc (sizeof(BPGame*));
  game->board = (char**) malloc ( sizeof (char*) * nrows ); 	

  for (int i = 0 ; i < nrows ; i++ )	{
      game->board[i] = (char *) malloc ( sizeof (char) * ncols);
  }
  for (int i = 0 ; i < nrows ; i++ )	{
    for (int j = 0 ; j < ncols ; j++ ) {
      int r = rand() % 4;
      if(r == 0)
        game->board[i][j] = Red;
      else if(r == 1)
        game->board[i][j] = Blue;
      else if(r == 2)
        game->board[i][j] = Green;
      else
        game->board[i][j] = Yellow;
    }
  }	
  game->r = nrows;
  game->c = ncols;
  game->score = 0;
  return game;
}

/**
* Function:  bp_create_from_mtx
* Parameters: number of rows and columns and 2D array of char
* Description: returns pointer to newly created
*              board with given number of rows
*              and columns.
*
*              Populates board contents of given 2D matrix (assumes
*	       given dimensions).
*
*	       Error conditions:
*              		If nrows or ncols is out of range, an error message 
*			is printed to stderr and NULL is returned.
*
*			If any element in the matrix is not one of the understood
*			color symbols (from the #define-s at top of this file),
*			an error message is pritnted to stderr and NULL is returned.
*			
*/
extern BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols) {
  if (nrows >= MAX_ROWS) {
    fprintf(stderr, "Rows out of range");
    return NULL;
  }
  if (ncols >= MAX_COLS) {
    fprintf(stderr, "Columns out of range");
    return NULL;
  }
  BPGame* game = (BPGame*) malloc (sizeof(BPGame*));
  char**  m = (char **) malloc ( sizeof (char*) * nrows ); 	

  for (int i = 0 ; i < nrows ; i++ )	{
    m[i] = (char *) malloc ( sizeof (char) * ncols);
  }
  for (int i = 0 ; i < nrows ; i++ )	{
    for (int j = 0 ; j < ncols ; j++ ) {
      m[i][j] = mtx[i][j];
    }
  }	
  game->board = m;
  game->r = nrows;
  game->c = ncols;
  game->score = 0;
  return game;
}

/**
* Function:  bp_destroy
* Description:  deallocates all dynamically allocated 
*  		memory associated with the board.
*		
*		Comment:  this might start out as
*		a one-liner.  
*
*/
extern void bp_destroy(BPGame * b) {
  for(int i = 0; i < b->r; i++) {
    free(b->board[i]);
  }
  free(b->board);
}


/**
* Function:  bp_display
* Description:  pretty-prints the current board.
*
*		uses '|', '+' and '-' to "draw" the boundaries
*               of the board.
*
*		For full credit rows and columns are labeled with
* 		their indices.  Column indices displayed "vertically"
*
*		Examples:
*
*  This board is full of balloons (like at the beginning of a game).
* 
*       +-----------------------+
*		  0 | + + + = + ^ ^ o + = = |
*		  1 | ^ = = o + o + + + ^ = |
*		  2 | ^ + ^ o + o + = = = = |
*		  3 | = ^ o o = o + + + = = |
*		    +-----------------------+
* 		    0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*
*  This board has some empty slots represented by  '.'
*       +-----------------------+
*		  0 | + + + = + ^ ^ o + = = |
*		  1 | ^ = o o + o + + + ^ = |
*		  2 | ^ + . o + . + = . . = |
*		  3 | . . . o . . + + . . = |
*		    +-----------------------+
* 		    0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*
*  Here is the same board using a space ' ' to 
*  represent an empty slot.
*
*       +-----------------------+
*		  0 | + + + = + ^ ^ o + = = |
*		  1 | ^ = o o + o + + + ^ = |
*		  2 | ^ +   o +   + =     = |
*		  3 |       o     + +     = |
*		    +-----------------------+
* 		    0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*/
extern void bp_display(BPGame * b)
{
printf("   +");
  for (int i = 0; i < b->c*2+1; i++) {
    printf("-");
  }
  printf("+\n");
  for (int i = 0; i < b->r; i++) { //iterate through entire array
    if(i < 10)
      printf(" %d | ", i);
    else
      printf("%d | ", i);
    for(int j = 0; j < b->c; j++) {
        printf("%c ", b->board[i][j]); //prints elements
    }
    printf("|\n"); 
  }
  printf("   +");
  for (int i = 0; i < b->r*2+1; i++) {
    printf("-");
  }
  printf("+\n");

  printf("     ");
  for (int i = 0; i < b->c; i++) {
    if (i > 29) {
      printf("3 ");
    } else if(i > 19) {
      printf("2 ");
    } else if(i > 9) {
      printf("1 ");
    } else {
      printf("0 ");
    }
  }
  printf("\n    ");
  for (int i = 0; i < b->c; i++) {
    int k = i;
    if(i<10)
      printf(" %d", k);
    else{
      while(k>9)
      {
        k -= 10;
      }
      printf(" %d", (k));
    }
  }
  printf("\n ");
}

/**
* Function:  bp_pop
* Description:  (attempts to) "pop" the balloon at (r,c) (if any)
*               and its associated "color cluster"
*
*               Cluster must be of AT LEASE SIZE 2 (a balloon that
*   		        is its own cluster will not be popped).
*
* Returns:  number of balloons popped (which may be zero).
*
* Side effects:  
*		locations of popped balloons become None (as in the "color"
*			None in the #define at the top of this file).
*
*		adds n*(n-1) to score if n balloons were popped.
*
* Notes:  does not require that the board be "compact".  But presumably, 
*	most client applicationw would only call on a compact board.
*
*/

extern void check_iter(BPGame* b, int* r, int* c, int i)
{
  switch(i) {
    case 0:
      *r-=1;
      break;
    case 1:
      *r+=1;
      break;
    case 2:
      *c-=1;
      break;
    case 3:
      *c+=1;
      break;
  }
}

extern int some_func_check(BPGame* b, int r, int c, char color)
{
  int row;
  int column;
  for(int i = 0; i < 4; i++)
  {
    row = r;
    column = c;
    check_iter(b, &row, &column, i);
    if(row >= 0 && row < b->r && column >= 0 && column < b->c)
    {
      if (b->board[row][column] == color)
      {
        return TRUE;
      }
    }
  }
  return FALSE;
}

extern int quick(BPGame* b, int r, int c, char color)
{
  int popped = 0;
  b->board[r][c] = '.';
  popped = 1;
  int row;
  int column;
  for(int i = 0; i < 4; i++)
  {
    row = r;
    column = c;
    check_iter(b, &row, &column, i);
    if (row >= 0 && row < b->r && column >= 0 && column < b->c) {
      if (b->board[row][column] == color) {
        popped += quick(b, row, column, color);
      }
    }
  }
  return popped;
}

extern int bp_pop(BPGame * b, int r, int c)
{
  if (r >= b->r) {
    fprintf(stderr, "Rows out of range\n");
    return 0;
  }
  if (c >= b->c) {
    fprintf(stderr, "Columns out of range\n");
    return 0;
  }
  int popped = 0;
  char color = b->board[r][c];

  if(b->board[r][c] != '.') {
    if(some_func_check(b, r, c, color))
    {
      b->board[r][c] = '.';
      popped++;
      int row;
      int column;
      for(int i = 0; i < 4; i++)
      {
        row = r;
        column = c;
        check_iter(b, &row, &column, i);
        if (b->c > column && -1 < column && b->r > row && row > -1) {
          if (b->board[row][column] == color) {
            popped += quick(b, row, column, color);
          }
        }
      }
    }
  }
  b->score += (popped * (popped - 1));
  return popped;
}

/**
* Function:  bp_is_compact
* Description:  determines if all balloons are as "high" as possible.
*               Returns 1 if this is the case
*               Returns 0 otherwise.
*
*               Note:  a balloon is as high as possible if and only
*     		if all slots in its column ABOVE it are also balloons
*		(non-empty)
*
*/
extern int bp_is_compact(BPGame * b)
{
  for(int i = 0; i < b->r-1; i++)
  {
    for(int j = 0; j < b->c; j++)
    {
      if(b->board[i][j] == '.' && b->board[i+1][j] != '.')
        return 0;
    }
  }
  return 1;
}

/**
* Function:  bp_float_one_step
* Description:  moves all balloons that that are NOT AS HIGH AS POSSIBLE
*               up one spot.  
*
*   Example:
*
*		before
*
*       +-----------------------+
*		  0 | + + + = + ^     + = = |
*		  1 | ^       + o + +   ^ = |
*		  2 | ^ +   o +   + =     = |
*		  3 |       o     + + =   = |
*		    +-----------------------+
* 		    0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*		after
*
*       +-----------------------+
*		  0 | + + + = + ^ + + + = = |
*		  1 | ^ +   o + o + =   ^ = |
*		  2 | ^     o +   + + =   = |
*		  3 |                     = |
*		    +-----------------------+
* 		    0 0 0 0 0 0 0 0 0 0 1
*		      0 1 2 3 4 5 6 7 8 9 0
*
*
* Note:  think animation by repeating this until it
*   is compact (perhaps displaying each intermediate
*   configuration).
*/
extern void bp_float_one_step(BPGame * b){
  for(int i = 0; i < b->c; i++)
  {
    for(int j = 0; j < b->r-1; j++)
    {
      if(b->board[j][i] == '.' && b->board[j+1][i] != '.') {
        char temp = b->board[j][i];
        b->board[j][i] = b->board[j+1][i];
        b->board[j+1][i] = temp;
      }
    }
  }
}

/**
* Function:  bp_score
* Description:  returns the current score 
*
*/
extern int bp_score(BPGame * b)
{
  return b->score;
}


/**
* Function:   bp_get_balloon
* Description:  returns color of balloon at given location as a char.
*		if (r,c) is out of range, -1 is returned.
*
*/
extern int bp_get_balloon(BPGame * b, int r, int c)
{
  if(r<0 || r>(b->r-1))
    return -1;
  if(c<0 || c>(b->c-1))
    return -1;
  return b->board[r][c];
}


/**
* Function:   bp_can_pop
* Description:  returns 1 if the player can pop some balloons;
*		        0 otherwise.
*
*		If the board is empty, of course nothing can
*			be popped.
*		If there are no adjacent balloons of the same
*		color, there also are no moves.
*	
* Notes:  probable usage is to determine when game is over.
*/
extern int bp_can_pop(BPGame * b)
{
  for(int i = 0; i < (b->r); i++)
  {
    for(int j = 0; j < (b->c); j++)
    {
      if(b->board[i][j] != '.')
      {
        if (i - 1 >= 0 && i - 1 < b->r) {
          if(b->board[i-1][j] == b->board[i][j])
            return 1;
        }
        if (i + 1 >= 0 && i + 1 < b->r) {
          if(b->board[i+1][j] == b->board[i][j])
            return 1;
        }
        if (j - 1 >= 0 && j - 1 < b->c) {
          if(b->board[i][j-1] == b->board[i][j])
            return 1;
        }
        if (j + 1 >= 0 && j + 1 < b->c) {
          if(b->board[i][j+1] == b->board[i][j])
            return 1;
        }
      }
    }
  }
  return 0;
}

void make_compact(BPGame* b)
{
  while(!bp_is_compact(b))
    bp_float_one_step(b);
}

/**
* Function:  bp_undo
* Description:  "undoes" most recent successful pop (if any), 
*		restoring the board to the exact state it was 
*		in immediately prior to that pop.
*
*               Also restores score to corresponding previous value.
*
*               Returns 1 if successful; 0 otherwise (i.e., when in the initial state --
*		no moves have been made to be undone).
*
*		NOTE:  bp_undo can be called repeatedly to back up all the way to the beginning
*		of the game.
*
*/
extern int bp_undo(BPGame * b)
{
  return 1;
}

extern void bp_display_STD(BPGame *b)
{
  for (int i = 0; i < b->r; i++) { //iterate through entire array
    for(int j = 0; j < b->c; j++) {
        printf("%c", b->board[i][j]); //prints elements
    }
    printf("\n");
  }
}

// int main ()
// {
//   BPGame* b;
//   b = bp_create(10,10);
//   bp_display(b);

//   int m;
//   int n;
//   while (m != -1) {
//     scanf("%d %d", &m, &n);
//     bp_pop(b, m, n);
//     make_compact(b);

//     printf("%d\n", bp_score(b));
//     bp_display(b);
//   }
//   bp_pop(b, m, n);

//   bp_display(b);



//   bp_destroy(b);
// }
