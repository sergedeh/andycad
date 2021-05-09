@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by CAD.HPJ. >"hlp\cad.hm"
echo. >>"hlp\cad.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\cad.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\cad.hm"
echo. >>"hlp\cad.hm"
echo // Prompts (IDP_*) >>"hlp\cad.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\cad.hm"
echo. >>"hlp\cad.hm"
echo // Resources (IDR_*) >>"hlp\cad.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\cad.hm"
echo. >>"hlp\cad.hm"
echo // Dialogs (IDD_*) >>"hlp\cad.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\cad.hm"
echo. >>"hlp\cad.hm"
echo // Frame Controls (IDW_*) >>"hlp\cad.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\cad.hm"
REM -- Make help for Project CAD


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\cad.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\cad.hlp" goto :Error
if not exist "hlp\cad.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\cad.hlp" Debug
if exist Debug\nul copy "hlp\cad.cnt" Debug
if exist Release\nul copy "hlp\cad.hlp" Release
if exist Release\nul copy "hlp\cad.cnt" Release
echo.
goto :done

:Error
echo hlp\cad.hpj(1) : error: Problem encountered creating help file

:done
echo.
