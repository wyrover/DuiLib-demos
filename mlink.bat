@echo off
@mode con cp select=936  >nul
cd /d "%~dp0"
RMDIR "%~dp0\boost" >nul 2>nul
if not exist "%~dp0\3rdparty\boost" (
    mklink /d /j "%~dp0\3rdparty\boost" "H:\rover\rover-self-work\cpp\boost_1_60_0\boost" 
)

if not exist "%~dp0\lib" (
    mklink /d /j "%~dp0\lib" "F:\kuaipan1\lib" 
)
