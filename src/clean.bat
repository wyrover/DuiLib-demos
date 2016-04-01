@echo off
cd /d %~dp0

for %%i in (src, src_tools, 3rdparty, publish, include, lib, product, sln, docs) do (
    pushd %%i
    ::echo %%i
    del /F /S /Q *.i *.exp *.aps *.idb *.ncp *.obj *.pch *.sbr *.tmp *.bsc *.ilk *.res *.ncb *.opt *.suo *.dep *.user *.orig
    del *.suo /s /Q /ah
    popd
)

pause