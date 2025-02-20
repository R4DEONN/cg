import * as path from "path";
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

export default {
    mode: 'development',
    entry: './src/index.ts', // Точка входа
    devtool: 'inline-source-map',
    module: {
        rules: [
            {
                test: /\.ts$/,
                use: 'ts-loader', // Использование ts-loader для обработки TypeScript файлов
                exclude: /node_modules/,
            },
        ],
    },
    resolve: {
        extensions: ['.ts', '.js'], // Поддерживаемые расширения
    },
    output: {
        filename: 'bundle.js', // Имя выходного файла
        path: path.resolve(__dirname, 'dist'), // Путь для выходного файла
    },
    devServer: {
        static: {
            directory: path.join(__dirname, 'dist'), // Папка для статических файлов
        },
        compress: true, // Включить сжатие
        port: 9000, // Порт для dev-сервера
        hot: true, // Включить Hot Module Replacement (HMR)
        open: true, // Автоматически открыть браузер
    },
};