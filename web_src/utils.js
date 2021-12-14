function nfaRecursion(node, arr) {
    if (!arr) arr = [];
    let { edge, inputset, stateNum } = node;
    if (inputset && inputset.length === 125) {
        // 控制字符不显示
        inputset = inputset.slice(32);
    }
    let obj = {
        value:
            (edge == -2
                ? inputset.replace(/"/g, '\\"')
                : edge >= 0
                ? String.fromCharCode(edge).replace(/"/g, '\\"')
                : edge) + "",
        id: stateNum,
    };
    arr.push(obj);
    if (node.next1) {
        obj.next1 = node.next1.stateNum + "";
        nfaRecursion(node.next1, arr);
    }
    if (node.next2) {
        obj.next2 = node.next2.stateNum + "";
        nfaRecursion(node.next2, arr);
    }
    return arr;
}

export function formatterNFAIntermediate(obj) {
    let keys = Object.keys(obj);
    let result = [];
    for (let i = 0; i < keys.length; i++) {
        const key = keys[i];
        let graph = nfaRecursion(obj[key]);
        result.push({
            id: key,
            value: graph,
        });
    }
    return result;
}
/**
 * STT :StateTransformTable
 * @date 14/12/2021
 */
export function formatterSTTIntermediate(arr) {
    let row = arr.length;
    let col = arr[0].length;
    let result = [];
    for (let i = 0; i < row; i++) {
        for (let j = 0; j < col; j++) {
            let r = arr[i][j];
            if (r != -1) {
                result.push({
                    id: j,
                    value: String.fromCharCode(i).replace(/"/g, '\\"'),
                    next1: r,
                });
            }
        }
    }
    console.log(result);
    return result;
}
