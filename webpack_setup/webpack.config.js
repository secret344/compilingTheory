const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const CopyPlugin = require("copy-webpack-plugin");
const { VueLoaderPlugin } = require("vue-loader");
const webpack = require("webpack");

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
    externals: {
        vue: "Vue",
    },
    resolve: {
        extensions: ["*", ".js", ".vue", ".json"],
    },
    module: {
        rules: [
            {
                test: /\.css$/i,
                use: ["vue-style-loader", "css-loader"],
            },
            {
                test: /\.js$/,
                exclude: /node_modules/,
                use: {
                    loader: "babel-loader",
                    options: {
                        presets: [
                            ["@babel/preset-env", { targets: "defaults" }],
                        ],
                    },
                },
            },
            {
                test: /\.vue$/,
                loader: "vue-loader",
                options: {
                    extractCSS: true,
                },
            },
        ],
    },
    plugins: [
        new HtmlWebpackPlugin({
            template: "./web_src/index.html",
            filename: "index.html",
            hash: true,
        }),
        new CopyPlugin({
            patterns: [
                { from: "wasm_folder/lexical.*" },
                { from: "assets/**.*", to: "[name][ext]" },
            ],
        }),
        new VueLoaderPlugin(),
        new webpack.SourceMapDevToolPlugin({}),
    ],
};
