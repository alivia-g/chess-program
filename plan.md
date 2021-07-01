## Overall plan for chess program:
Stage 1) Chessboard\
Stage 2) Movement (per piece, check validity)\
Stage 3) Evaluate position\
Stage 4) Turn-based game, with user input\
Stage 5) Minimal AI (random choice among greedy best moves, i.e. 1 ply)\
Stage 6) Minimax AI

## Stage 1)
1. define a chessboard struct (i.e. 8x8 array)
2. create a function to clear the board
3. create a function to initialize the board with the starting position - what values to use for black and white's pieces (they must be distinguishable)? consider lower and uppercase letters, for black and white
4. create a function to print the board - bonus: change the text color and background color
5. create a function to copy values from one board to another
6. test these functions!

## Stage 2)
1. Which squares can be reached by a piece?
2. Is the king (of the playing side’s color) under check (before and after move)?
3. Bonus: Castling
4. Bonus: En Passant
5. Bonus: Pawn promotion


## Misc todo:
Separate declarations from function definitions (implementation)
En passant
Castling

