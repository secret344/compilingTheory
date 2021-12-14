function initWebassembly() {
    let obj = null;
    return async function () {
        if (obj) {
            return obj;
        }
        let result = await Module();
        const regParse = result.cwrap("regParse", "string", ["string"]);
        const matchStr = result.cwrap("matchStr", "number", ["string"]);
        const dfaParse = result.cwrap("dfaParse", "string");
        console.log("加载webassembly模块完成");
        obj = { regParse, matchStr, dfaParse };
        return obj;
    };
}
export const WebAssemblyFun = initWebassembly();

// export const regstr =
//     "id:[a-zA-Z]([a-zA-Z0-9_])*\n\
// float:[0-9]+\\.[0-9]+\n\
// int:[0-9]+\n\
// punctuation:[,;]\n\
// string:([\"](.)*[\"])|(['](.)*['])";

export const regstr = "id:a|b|c";
