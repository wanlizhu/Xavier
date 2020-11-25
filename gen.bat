@echo off

:: Ensure this script was not started with UNC path (e.g. network location)
cd /d %~dp0 || (
	pause
	exit 1
)

set bindir=C:/Users/%username%/Xavier-build
if exist %bindir% ( rd /s/q %bindir% )

python --version > nul || (
	echo install python3 and run this script again
	pause
	exit 1
)

conan --version > nul || (
	python -m pip install conan
)


conan install --install-folder "%bindir%" --build missing .
cmake -B"%bindir%" -G"Visual Studio 16 2019" -Ax64 -Wno-dev

call:find_task devenv.exe return
if %return%==0 ( cmake --open "%bindir%" )

pause
goto:eof

:: %~1 image name
:: %~2 return value
:find_task
set func=%~0
set %~2=0

tasklist /v | find /i "%~1" > %tmp%\%func:~1%.tmp
for /f "delims=" %%i in (%tmp%\%func:~1%.tmp) do (
	if not "%%i"=="" (
		set %~2=1
		goto:eof
	)
) 

goto:eof

