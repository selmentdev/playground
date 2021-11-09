REM Set some variables.
REM ========================================================================================================

set "CLANG_VERSION=13.0.0"
set "CLANG_ASAN_PATH=%CLANG_PATH%\\lib\\clang\\%CLANG_VERSION%\\lib\\windows"
set "PATH=%CLANG_PATH%\\bin;%CLANG_ASAN_PATH%;%PATH%"
set "WINDOWS_SDK_LIB=C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\ucrt\\x64"
set "VC_TOOLCHAIN_VERSION=14.30.30705"
set "VC_TOOLCHAIN_PATH=C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools"

set "ASAN_SYMBOLIZER_PATH=%CLANG_PATH%\bin\llvm-symbolizer.exe"

REM Find proper vc toolchain environment.
REM ========================================================================================================
call "%VC_TOOLCHAIN_PATH%\\VC\\Auxiliary\\Build\\vcvarsall.bat" amd64

@echo on
setlocal
REM Delete old files.
REM ========================================================================================================
del *.exe
del *.exp
del *.lib
del *.o
del *.pdb

REM Invoke clang.
REM ========================================================================================================

clang++ ^
-c main.cxx ^
-std=c++17 ^
-gcodeview ^
-g ^
-fsanitize=address,undefined ^
-o main.o

REM Link everything together.
lld-link ^
    /out:"main.exe" ^
    main.o ^
    -subsystem:console ^
    -debug ^
    -incremental:no ^
    -libpath:"%WINDOWS_SDK_LIB%" ^
    -libpath:"%VC_TOOLCHAIN_PATH%\\VC\\Tools\\MSVC\\%VC_TOOLCHAIN_VERSION%\\lib\\x64\\" ^
    -libpath:"%CLANG_ASAN_PATH%" ^
    clang_rt.asan_dynamic_runtime_thunk-x86_64.lib ^
    clang_rt.asan_dynamic-x86_64.lib ^
    msvcrt.lib ^
    vcruntime.lib ^
    ucrt.lib ^
    kernel32.lib ^
    user32.lib ^
    gdi32.lib ^
    winspool.lib ^
    shell32.lib ^
    ole32.lib ^
    oleaut32.lib ^
    uuid.lib ^
    comdlg32.lib ^
    advapi32.lib ^
    oldnames.lib

REM Set asan options.
REM ========================================================================================================
set ASAN_OPTIONS=debug=1,verbosity=10,abort_on_error=1,symbolize=1

REM Invoke main executable and observe the output from the asan runtime.
REM ========================================================================================================
main.exe
