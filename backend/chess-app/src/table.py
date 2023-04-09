#!bin/usr/python3
from stockfish import Stockfish
import chess
import chess.engine
import time

stockfish = Stockfish("/usr/games/stockfish")
stockfish.set_skill_level(20)

engine = chess.engine.SimpleEngine.popen_uci("/usr/games/stockfish")
board = chess.Board()
#read the move from the move.txt file

# Play the game
def print_board(board):
    with open('matrix.txt', 'w') as f:
        for row in range(8):
            for col in range(8):
                square = chess.square(col, 7-row)
                piece = board.piece_at(square)
                if piece is not None:
                    piece_str = chess.COLOR_NAMES[piece.color].upper() + "_" + chess.PIECE_NAMES[piece.piece_type].upper()
                    x, y = chess.square_file(square), chess.square_rank(square)
                    print(f"{piece_str},{x},{y}", file=f)


def is_legal_move(board):
    with open('move.txt', 'r') as f:
        move_str = f.read()
    move = chess.Move.from_uci(move_str)
    if move in board.legal_moves:
        return 1
    else:
        return 0



print_board(board)
print(is_legal_move(board))
with open('move.txt', 'r') as f:
    move_str = f.read()
move = chess.Move.from_uci(move_str)
if is_legal_move(board):
    board.push(move)
print_board(board)
# Close the engine
engine.quit()