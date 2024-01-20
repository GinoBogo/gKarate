
$env:Path += ";C:\Programs\MSYS2\ucrt64\bin"

Clear-Host

function DeleteItem {
    param ($name)

    if ((Test-Path $name) -eq $true ) { Remove-Item $name -Force -Recurse }
}

# DeleteItem("../build")

Push-Location "../build/debug"

cmake.exe --build ./ --target clean

Pop-Location
