CWD="`dirname "$0"`"
cd "$CWD"
if [ -d "~/Maxine-build" ]; then rm -rf ~/Maxine-build; fi

if ! command -v conan &> /dev/null ; then
    python3 -m pip install conan
fi

conan install --install-folder ~/Maxine-build --build missing .
cmake -B~/Maxine-build -GXcode -Wno-dev
cmake --open ~/Maxine-build
