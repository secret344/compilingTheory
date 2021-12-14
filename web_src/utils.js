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
export function formatterSTTIntermediate(arr, obj, idMini = false) {
    let row = arr.length;
    let col = arr[0].length;
    let result = [];

    let first = {};

    for (let i = 0; i < row; i++) {
        for (let j = 0; j < col; j++) {
            let r = arr[i][j];
            if (r != -1) {
                result.push({
                    id: j,
                    value: String.fromCharCode(i).replace(/"/g, '\\"'),
                    next1: r,
                });
                if (j === 0) {
                    first[r] = !!first[r]
                        ? [
                              ...first[r],
                              String.fromCharCode(i).replace(/"/g, '\\"'),
                          ]
                        : [String.fromCharCode(i).replace(/"/g, '\\"')];
                }
            }
        }
    }

    let dfaJson = obj.dfaJson;
    let dfaGroup = obj.minimizeDfa.dfaGroup;
    if (idMini) {
        dfaGroup.forEach((item) => {
            result.push({
                id: item.groupnum,
                tooltip: `dfa节点集合：${item.dfaset.join(",")}`,
            });
            if (first[item.groupnum]) {
                result[result.length - 1].tooltip =
                    result[result.length - 1].tooltip +
                    `\n前置输入条件:${first[item.groupnum].join(",")}`;
            }
        });
    } else {
        dfaJson.forEach((item) => {
            result.push({
                id: item.dfaStateNum,
                tooltip: `终结态:${
                    item.accepted
                };\nnfa节点集合:${item.nfaset.join(",")}`,
            });
            if (first[item.dfaStateNum]) {
                result[result.length - 1].tooltip =
                    result[result.length - 1].tooltip +
                    `\n前置输入条件:${first[item.dfaStateNum].join(",")}`;
            }
        });
    }

    return result;
}
