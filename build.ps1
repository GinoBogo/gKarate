
$env:Path += ";C:\Programs\MSYS2\ucrt64\bin"

Clear-Host

Set-Location "../build"

qmake6.exe "../gKarate/gKarate.pro" -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"

mingw32-make.exe -f Makefile qmake_all

mingw32-make.exe -j4

Copy-Item -Path ./debug/*.exe -Destination "../dist" -Recurse