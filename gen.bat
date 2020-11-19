@echo off

set bindir=C:/Users/%username%/Maxine-build
if exist %bindir% (rd /s/q %bindir%)

for /F "delims=" %%i in ("conan.exe") do (
    if exist %%~$PATH:i (
        conan -v
    ) else (
        pip install conan
    )
)

conan install --install-folder "%bindir%" --build missing .
cmake -B"%bindir%" -G"Visual Studio 16 2019" -Ax64 -Wno-dev
cmake --open "%bindir%"

pause