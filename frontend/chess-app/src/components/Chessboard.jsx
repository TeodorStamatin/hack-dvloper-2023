// table component react component

import React from 'react';
import Piece from './Piece.jsx';
import { useState } from 'react';

import { getNameByPos, getPosByName } from '../pieces/utils.js';

function Chessboard(props) {
    const [data, setData] = useState(
        [
            {
                type: 'WHITE_PAWN',
                position: 'A2',
            },
            {
                type: 'WHITE_PAWN',
                position: 'B2',
            },
            {
                type: 'WHITE_QUEEN',
                position: 'D1',
            },
            {
                type: 'BLACK_KING',
                position: 'E8',
            },
            {
                type: 'BLACK_BISHOP',
                position: 'C8',
            }
        ]
        );

    const [selectedPiece, setSelectedPiece] = useState(null);

    // create a 8x8 empty matrix
    let chessboard = [];
        
    for (let i = 0; i < 8; i++) {
        chessboard.push([]);
        for (let j = 0; j < 8; j++) {
            chessboard[i].push(null);
        }
    }
    
    // place pieces on the chessboard
    data.forEach((piece) => {
        let [row, col] = getPosByName(piece.position);
        chessboard[row][col] = piece;
    });

    function performMove(i, j) {
        if (selectedPiece === null) return;
        if (chessboard[i][j] !== null) return;
        props.setHistory([{pieceType: selectedPiece.type, from: selectedPiece.position, to: getNameByPos(i, j)}, ...props.history]);
        let [row, col] = getPosByName(selectedPiece.position);
        chessboard[row][col] = null;
        chessboard[i][j] = selectedPiece;
        selectedPiece.position = `${String.fromCharCode(j + 65)}${i + 1}`;
        setSelectedPiece(null);
    }

    let board = [];
    chessboard.forEach((row, i) => {
        let listItems = [];
        row.forEach((piece, j) => {
            let color = "";
            // set cell color based on indices
            if ((i + j) % 2 === 0)
                color = "evenColor";
            else
                color = "oddColor";
            
            let selected = false;
            let [row, col] = [-1, -1];
            if (selectedPiece !== null)
                [row, col] = getPosByName(selectedPiece.position);
            if (i === row && j === col)
                selected = true;

            if (piece !== null) {
                listItems.push(
                    <div key={piece.position} className={`piece ${color} ${selected ? "selected" : ""}`} onClick={() => setSelectedPiece(piece)}>
                        <Piece piece={piece} />
                    </div>);
            }
            else 
                listItems.push(<div key={getNameByPos(i, j)} className={`piece ${color}`} onClick={() => performMove(i, j)}></div>);
        })
        board.push(<div className="row" key={`key` + i}>{listItems}</div>)
    })
    // construct a jsx object based on chessboard
  return (
    <div className="chessBoard">
        {board}
    </div>
    )
}

export default Chessboard;
