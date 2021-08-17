## Overall plan for chess program:
Stage 1) Chessboard\
Stage 2) Movement (per piece, check validity)\
Stage 3) Evaluate game state\
Stage 4) Turn-based game, with user input\
Stage 5) Minimal AI (random choice among greedy best moves, i.e. 1 ply)\
Stage 6) Minimax AI

## Stage 1)
1. Define a chessboard struct (i.e. 8x8 array)
2. Create a function to clear the board
3. Create a function to initialize the board with the starting position - what values to use for black and white's pieces (they must be distinguishable)? consider lower and uppercase letters, for black and white
4. Create a function to print the board - bonus: change the text color and background color
5. Create a function to copy values from one board to another
6. Test these functions!

## Stage 2)
1. Which squares can be reached by a piece?
2. Is the king (of the playing side’s color) under check (before and after move)?
3. Which moves are valid for a player to make for a piece on the board?
4. Bonus: Castling
5. Bonus: En Passant
6. Bonus: Pawn promotion

## Stage 3)
1. Determine if a player is under checkmate or stalemate
1. Assign a value to each piece
2. Calculate a value for a position (checkmate is infinite, stalemate is zero)
