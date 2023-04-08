#!/usr/bin/python3

from flask import Flask, jsonify, request
import json
from ctypes import *

(BLACK, WHITE) = (0, 1)
(PAWN, BISHOP, KNIGHT, KING, QUEEN, ROOK) = (0, 1, 2, 3, 4, 5)

class Piece(Structure):
    _fields_ = [
        ('color', c_int),
        ('type', c_int),
        ('hasMoved', c_int),
    ]

app = Flask(__name__)

chessSDK = CDLL("./src/table.so")  

@app.route("/api/createGame", methods = ['GET'])
def createGame():
    chessboard = POINTER(Piece)()
    print(bool(chessboard))
    return jsonify({})


if __name__ == "__main__":
    app.run(debug=True)

