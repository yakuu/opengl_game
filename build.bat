@echo off
del myprogram.exe
g++ -m64 -I"C:\msys64\mingw64\include" src/main.cpp src/materials.cpp -o myprogram -L"C:\glew\lib\Release\x64" -lglew32 -lfreeglut -lopengl32 -lglu32 -fpermissive
if not %errorlevel%==0 (
    echo Compilation failed!
    pause
    exit /b %errorlevel%
)
echo Compilation successful. Starting program...
start myprogram.exe
