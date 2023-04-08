export function getPosByName(name) {
    let col = name.charCodeAt(0) - "A".charCodeAt(0);
    let row = name.charCodeAt(1) - "1".charCodeAt(0);
    return [row, col];
}

export function getNameByPos(i, j) {
    let col = String.fromCharCode("A".charCodeAt(0) + j);
    let row = String.fromCharCode("1".charCodeAt(0) + i);
    return col + row;
}
