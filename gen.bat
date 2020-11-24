@echo off

set bindir=C:/Users/%username%/Xavier-build
if exist %bindir% (rd /s/q %bindir%)

python3 --version > null || (
	echo install python3 and run this script again
	pause
	exit 1
)

conan --version > null || (
	python3 -m pip install conan
)

conan install --install-folder "%bindir%" --build missing .
cmake -B"%bindir%" -G"Visual Studio 16 2019" -Ax64 -Wno-dev
cmake --open "%bindir%"

pause