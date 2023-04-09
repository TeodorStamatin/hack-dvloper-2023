import React from "react";

import getPieceImage from '../pieces/getPieceImage';

export default function History(props) {
  return (
    <div className="historyBox">
      {props.history.map((move, index) => (
        <div className="historyEntry" key={index}>
          <span>{index + 1}.</span>
          <img className="historyImg"
                src={getPieceImage(move.pieceType)}
                alt={move.pieceType}
          />
          <span>{move.from}</span>
          <span>{move.to}</span>
        </div>
      ))}
    </div>
  );
}