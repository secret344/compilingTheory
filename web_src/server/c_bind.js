function initWebassembly() {
    let obj = null;
    return async function () {
        if (obj) {
            return obj;
        }
        let result = await Module();
        const regParse = result.cwrap("regParse", "string", ["string"]);
        const matchStr = result.cwrap("matchStr", "number", ["string"]);
        console.log("加载webassembly模块完成", result);
        obj = { regParse, matchStr };
        return obj;
    };
}
export const WebAssemblyFun = initWebassembly();
