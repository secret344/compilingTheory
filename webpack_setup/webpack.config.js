const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const CopyPlugin = require("copy-webpack-plugin");

module.exports = {
    entry: "./web_src/main.js",
    mode: "development",
    devServer: {
        port: 9900,
        open: true,
    },
    output: {
        path: path.resolve(__dirname, "../dist"),
        filename: "[name].[hash:8].js",
        publicPath: "/",
        clean: true,
    },
    module: {},
    plugins: [
        new HtmlWebpackPlugin({
            template: "./web_src/index.html",
            filename: "index.html",
            hash: true,
        }),
        new CopyPlugin({
            patterns: [{ from: "wasm_folder/lexical.*" }],
        }),
    ],
};
