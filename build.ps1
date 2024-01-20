
$env:Path += ";C:\Programs\MSYS2\ucrt64\bin"

Clear-Host

Push-Location "../build/debug"

cmake.exe --build ./ --target all

Copy-Item -Path ./compile_commands.json -Destination "../" -Recurse

Copy-Item -Path ./*.exe -Destination "../../dist" -Recurse

Pop-Location