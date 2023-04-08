// table component react component

import React from 'react';
import Piece from './Piece.jsx';
import { useState } from 'react';

function Chessboard() {
    const [chessboard, setChessboard] = useState(
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

      const listItems = chessboard.map((piece) => <Piece piece={piece} key={piece.position}/>);
      console.log(listItems);
  return (
    <div className="chessboard">
        <div className="row">
            {listItems}
        </div>
    </div>
    )
}

export default Chessboard;
