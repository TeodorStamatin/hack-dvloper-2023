// piece component react component

import React from 'react';
import getPieceImage from '../pieces/getPieceImage';

function Piece(props) {
    console.log(props);
  return (
    <div className="piece">
      <img src={getPieceImage(props.piece.type)} alt={props.piece.type}/>
    </div>
  )
}

export default Piece;
