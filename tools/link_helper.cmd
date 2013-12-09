@set "PATH=C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE;%PATH%"
@"C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\bin\link.exe" /NOLOGO /DLL /SUBSYSTEM:CONSOLE %* > nul 2>&1
