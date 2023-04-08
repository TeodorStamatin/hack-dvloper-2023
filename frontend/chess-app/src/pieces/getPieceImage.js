import BLACK_PAWN from './BLACK_PAWN.svg';
import BLACK_ROOK from './BLACK_ROOK.svg';
import BLACK_KNIGHT from './BLACK_KNIGHT.svg';
import BLACK_BISHOP from './BLACK_BISHOP.svg';
import BLACK_QUEEN from './BLACK_QUEEN.svg';
import BLACK_KING from './BLACK_KING.svg';
import WHITE_PAWN from './WHITE_PAWN.svg';
import WHITE_ROOK from './WHITE_ROOK.svg';
import WHITE_KNIGHT from './WHITE_KNIGHT.svg';
import WHITE_BISHOP from './WHITE_BISHOP.svg';
import WHITE_QUEEN from './WHITE_QUEEN.svg';
import WHITE_KING from './WHITE_KING.svg';

export default function getPieceImage(type) {
    switch(type) {
        case 'BLACK_PAWN':
            return BLACK_PAWN;
        case 'BLACK_ROOK':
            return BLACK_ROOK;
        case 'BLACK_KNIGHT':
            return BLACK_KNIGHT;
        case 'BLACK_BISHOP':
            return BLACK_BISHOP;
        case 'BLACK_QUEEN':
            return BLACK_QUEEN;
        case 'BLACK_KING':
            return BLACK_KING;
        case 'WHITE_PAWN':
            return WHITE_PAWN;
        case 'WHITE_ROOK':
            return WHITE_ROOK;
        case 'WHITE_KNIGHT':
            return WHITE_KNIGHT;
        case 'WHITE_BISHOP':
            return WHITE_BISHOP;
        case 'WHITE_QUEEN':
            return WHITE_QUEEN;
        case 'WHITE_KING':
            return WHITE_KING;
        default:
            return null;
    }
}
