// table component react component

import React from 'react';
import Piece from './Piece.jsx';
import { useState } from 'react';

import { getNameByPos, getPosByName } from '../pieces/utils.js';

function Chessboard({data,
                    history,
                    setHistory,
                    gameNumber,
                    resignGame,
                    loadGame,
                    loadInput,
                    setLoadInput}
                    ) {
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
        let [row, col] = getPosByName(selectedPiece.position);

        fetch("http://localhost:5000/api/checkMove",
        {
            method: "POST",
            body: JSON.stringify({
                pieces: data,
                from_row: row,
                from_col: col,
                to_row: i,
                to_col: j,
        })})
        .then(res => res.json())
        .then((data) => {console.log(data)});

        setHistory(
        [
            {
                pieceType: selectedPiece.type,
                from: selectedPiece.position,
                to: getNameByPos(i, j)
            }, ...history
        ]);
        chessboard[row][col] = null;
        chessboard[i][j] = selectedPiece;
        selectedPiece.position = `${String.fromCharCode(j + 65)}${i + 1}`;
        setSelectedPiece(null);
        saveMove(i, j);
    }

    function saveMove(i, j) {
        fetch("http://localhost:5000/api/saveMove",
        {
            method: "POST",
            body: JSON.stringify({
                game_id: gameNumber,
                piece: selectedPiece.type,
                positionFrom: selectedPiece.position,
                positionTo: getNameByPos(i, j),
        })})
        .then(res => res.json())
        .then((data) => {console.log(data)});
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
                    <div key={piece.position}
                        className={`piece ${color} ${selected ? "selected" : ""}`}
                        onClick={() => setSelectedPiece(piece)}>
                        <Piece piece={piece} />
                    </div>);
            }
            else 
                listItems.push(<div key={getNameByPos(i, j)} 
                                    className={`piece ${color}`}
                                    onClick={() => performMove(i, j)}>
                                </div>);
        })
        board.push(<div className="row" key={`key` + i}>{listItems}</div>)
    })
    // construct a jsx object based on chessboard
  return (
    <div>
        <div className="btnBox">
            <input className="loadInput"
                    placeholder='Game ID'
                    value={loadInput}
                    onChange={(event) => setLoadInput(event.target.value)}
            />
            <button className="loadBtn"onClick={() => loadGame()}>
              <b>Load game</b>
            </button>
        </div>
        <h2>Game: <span className="gameNumber">#{gameNumber}</span></h2>
        <div className="chessBoard">
            {board}
        </div>
        <div className="resignBtnBox">
            <button className="resignBtn"
                    onClick={() => resignGame()}>
            Resign game
            </button>
        </div>
    </div>
    )
}

export default Chessboard;
