#!bin/usr/python3

def create_chess_board():
    board = [[None] * 8 for _ in range(8)]

    # fill in pawns
    for col in range(8):
        board[1][col] = ('black', 'pawn')
        board[6][col] = ('white', 'pawn')

    # fill in other pieces
    board[0][0] = ('black', 'rook')
    board[0][1] = ('black', 'knight')
    board[0][2] = ('black', 'bishop')
    board[0][3] = ('black', 'queen')
    board[0][4] = ('black', 'king')
    board[0][5] = ('black', 'bishop')
    board[0][6] = ('black', 'knight')
    board[0][7] = ('black', 'rook')

    board[7][0] = ('white', 'rook')
    board[7][1] = ('white', 'knight')
    board[7][2] = ('white', 'bishop')
    board[7][3] = ('white', 'queen')
    board[7][4] = ('white', 'king')
    board[7][5] = ('white', 'bishop')
    board[7][6] = ('white', 'knight')
    board[7][7] = ('white', 'rook')

    return board

def print_chess_board(board):
    for row in board:
        print(row)

#function that checks if chess move is valid. this means you should check if the position where you move is NULL, and if it is not,
#you should check if your chess piece has the right movement to go there, and if a piece is there, check that is doesnt have the same 
#color. lastly, you should check that if you move the wanted piece, your king cant be taken by other color chess pieces. NOTE THAT 
#ONLY table->type->knight can jump over other piece. other pieces cand go to the wanted position if they have to go through an occupied
#position on the table.

def check_move(board, color, piece, start, end):
    if board[end[0]][end[1]] == None:
        return True
    elif board[end[0]][end[1]][0] != color:
        return True
    else:
        return False
    

def main():
    board = create_chess_board()
    print_chess_board(board)

main()