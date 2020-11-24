CWD="`dirname "$0"`"

cd "$CWD"
if [ -d "~/Xavier-build" ]; then rm -rf ~/Xavier-build; fi

if ! command -v python3 &> /dev/null ; then
	echo python3 environment is required
	echo Press any key to continue...
	read -n 1 chr
	exit 1
fi

if ! command -v conan &> /dev/null ; then
    python3 -m pip install conan
fi

conan install --install-folder ~/Xavier-build --build missing .
cmake -B~/Xavier-build -GXcode -Wno-dev
cmake --open ~/Xavier-build
