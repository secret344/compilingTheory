import App from "./app";

Vue.createApp(App).mount("#app");

Module().then((res) => {
    let str = "";

    console.log("加载webassembly模块完成", res);
    const regParse = res.cwrap("regParse", "string", ["string"]);
    const matchStr = res.cwrap("matchStr", "number", ["string"]);

    let ptr = regParse(str);
    matchStr("0.1le t0a 2.2 () == += -- -=,;'123'");
    console.log(
        "\n\n----------------------------执行结束-------------------------------------\n\n"
    );
    setTimeout(() => {
        console.log("正则格式化结果JSON：", ptr);
        console.log("\n正则格式化结果JSON：", JSON.parse(ptr));
    }, 1000);
});
