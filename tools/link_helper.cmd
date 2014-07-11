@set "PATH=C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE;%PATH%"
@set "LIB=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\LIB;C:\Program Files (x86)\Windows Kits\8.0\lib\win8\um\x86;%LIB%"
@"C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\link.exe" /NOLOGO /DLL /SUBSYSTEM:CONSOLE %* > nul 2>&1
