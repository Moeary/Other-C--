@echo off
REM 编译
g++ -o Admin.exe admin.cpp -lgdi32
g++ -o Buy.exe buy.cpp -lgdi32
g++ -o Shopper.exe shopper.cpp -lgdi32
REM 运行
if exist Buy.exe (
    Buy.exe
) else (
    echo "程序编译失败。"
)