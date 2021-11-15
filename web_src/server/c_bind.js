function initWebassembly() {
    let obj = null;
    return async function () {
        if (obj) {
            return obj;
        }
        await Module().then((res) => {
            const regParse = res.cwrap("regParse", "string", ["string"]);
            const matchStr = res.cwrap("matchStr", "number", ["string"]);
            console.log("加载webassembly模块完成", res);
            obj = { regParse, matchStr };
            return { regParse, matchStr };
        });
    };
}
export const WebAssemblyFun = initWebassembly();
