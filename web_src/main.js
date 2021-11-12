import App from "./app";

Vue.createApp(App).mount("#app");

Module().then((res) => {
    console.log("加载webassembly模块完成", res);
    const regParse = res.cwrap("regParse", "number", ["string"]);
    const matchStr = res.cwrap("matchStr", "number", ["string"]);
    regParse("id:[a-zA-Z]([a-zA-Z0-9_])*");
    matchStr("0.1le t0a 2.2 () == += -- -=,;'123'");
    console.log(
        "\n\n----------------------------执行结束-------------------------------------\n\n"
    );
});
