jlink --add-modules java.base,java.desktop --output Win32
copy "%~dp0release" "%~dp0Win32\release"