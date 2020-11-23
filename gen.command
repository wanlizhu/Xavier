CWD="`dirname "$0"`"
cd "$CWD"
if [ -d "~/Xavier-build" ]; then rm -rf ~/Xavier-build; fi

if ! command -v conan &> /dev/null ; then
    python3 -m pip install conan
fi

conan install --install-folder ~/Xavier-build --build missing .
cmake -B~/Xavier-build -GXcode -Wno-dev
cmake --open ~/Xavier-build
