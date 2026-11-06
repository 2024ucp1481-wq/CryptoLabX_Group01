
$ProjectRoot = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$DataDir = Join-Path $ProjectRoot "data"

New-Item -ItemType Directory -Force -Path $DataDir | Out-Null

Write-Host "Generating 1 MB using Windows .NET Cryptographic RNG..."

$bytes = New-Object byte[] 1048576

$rng = [System.Security.Cryptography.RandomNumberGenerator]::Create()
$rng.GetBytes($bytes)
$rng.Dispose()

[System.IO.File]::WriteAllBytes(
    (Join-Path $DataDir "windows_cng.bin"),
    $bytes
)

Write-Host "Windows random data generated successfully."
Write-Host "File size: $($bytes.Length) bytes"
