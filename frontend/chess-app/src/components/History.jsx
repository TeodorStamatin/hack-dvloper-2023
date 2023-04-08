import React from "react";

export default function History(props) {
  return (
    <div>
      {props.history.map((move, index) => (
        <div key={index}>
          {index + 1}. {move.pieceType} {move.from} {move.to}
        </div>
      ))}
    </div>
  );
}