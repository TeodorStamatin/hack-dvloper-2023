#!bin/usr/python3

from flask import Flask, request, session, redirect, jsonify
import bcrypt
import sqlite3
def createGame():
    chessboard = []
    with open("input.txt", "r") as infile:
        for i in range(0, 8):
            chessboard.append([])
            for _ in range(0, 8):
                chessboard[i].append(None)
        for line in infile:
            (piece, i, j) = line.split(",")
            print(piece, i, j)
            print(chessboard)
            chessboard[int(i)][int(j)] = piece
    pieces = []
    for i in range(0, 8):
        for j in range(0, 8):
            if chessboard[i][j] is not None:
                position = chr(ord('A') + j) + str(i + 1)
                pieces.append({
                    "position": position,
                    "type": chessboard[i][j]
                })

    return jsonify(pieces)

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