import React from "react";

import getPieceImage from '../pieces/getPieceImage';

export default function History(props) {
  return (
    <div className="historyBox">
      {props.history.map((move, index) => (
        <div className="historyEntry" key={index}>
          {index + 1}. <img className="historyImg" src={getPieceImage(move.pieceType)} alt={move.pieceType}/> {move.from} {move.to}
        </div>
      ))}
    </div>
  );
}