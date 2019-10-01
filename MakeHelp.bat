@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by BOXMAN.HPJ. >"hlp\BoxMan.hm"
echo. >>"hlp\BoxMan.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\BoxMan.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\BoxMan.hm"
echo. >>"hlp\BoxMan.hm"
echo // Prompts (IDP_*) >>"hlp\BoxMan.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\BoxMan.hm"
echo. >>"hlp\BoxMan.hm"
echo // Resources (IDR_*) >>"hlp\BoxMan.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\BoxMan.hm"
echo. >>"hlp\BoxMan.hm"
echo // Dialogs (IDD_*) >>"hlp\BoxMan.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\BoxMan.hm"
echo. >>"hlp\BoxMan.hm"
echo // Frame Controls (IDW_*) >>"hlp\BoxMan.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\BoxMan.hm"
REM -- Make help for Project BOXMAN


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\BoxMan.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\BoxMan.hlp" goto :Error
if not exist "hlp\BoxMan.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\BoxMan.hlp" Debug
if exist Debug\nul copy "hlp\BoxMan.cnt" Debug
if exist Release\nul copy "hlp\BoxMan.hlp" Release
if exist Release\nul copy "hlp\BoxMan.cnt" Release
echo.
goto :done

:Error
echo hlp\BoxMan.hpj(1) : error: Problem encountered creating help file

:done
echo.
