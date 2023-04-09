export function getPosByName(name) {
    let row = name.charCodeAt(0) - "A".charCodeAt(0);
    let col = name.charCodeAt(1) - "1".charCodeAt(0);
    return [col, row];
}

export function getNameByPos(i, j) {
    let col = String.fromCharCode("A".charCodeAt(0) + j);
    let row = String.fromCharCode("1".charCodeAt(0) + i);
    return col + row;
}
