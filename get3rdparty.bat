echo off

REM Because we use IF statements, we need this setlocal statement and we will
REM to expand environment variables using exclamation syntax !<var>! instead of
REM percent syntax %<var>%.



SETLOCAL ENABLEEXTENSIONS
SETLOCAL ENABLEDELAYEDEXPANSION

REM Set SRCDIR_ROOT directory to the current folder.  This assumes that this 
REM batch file lives at the root of the SDK tree.

set SRCDIR_ROOT=%~dp0

REM Currently we only build for x64 so this is simple

set SDKDIR=%SRCDIR_ROOT%GelSightSdk

echo "SDKROOT is %SDKROOT%"

REM Copy 3rd party DLLs to build output folders so we 
REM can run the app with everything we need present
REM (i.e. no need for adding any other folder to the PATH)
if DEFINED GS_THIRDPARTYDIR goto gsthirdpartydir_defined

    echo "The required environment variable GS_THIRDPARTYDIR% is not defined"
    echo "    You must define GS_THIRDPARTYDIR to point to the root of the third party repository"
    echo "    get3rdparty cannot continue"
    pause
    exit /b

:gsthirdpartydir_defined

IF EXIST %GS_THIRDPARTYDIR% goto gsthirdpartydir_exists

    echo "The required thirdparty directory %GS_THIRDPARTYDIR% does not exist"
    echo "    get3rdparty cannot continue"
    pause
    exit /b


:gsthirdpartydir_exists

REM Verify that the Ximea folder is there.

if DEFINED GS_XIMEAVER goto gsximeaver_defined

    echo "The required environment variable GS_XIMEAVER% is not defined"
    echo "    You must define GS_THIRDPARTYDIR to the proper version of the"
    echo "    Ximea driver.  Something like 4.14.01"
    pause
    exit /b

:gsximeaver_defined


set XIMEADIR=!GS_THIRDPARTYDIR!\ximea\sdk\v!GS_XIMEAVER!\api


REM TODO:  Make all these things parameters (e.g. Release/Debug, Eigen/gtest/libpng, v110/v120) 
REM so that I don't have to repeat the same line so many times


REM For each configuration C -- aks VS macro $(Configuration)

for %%C in  (
        Debug
        Release
    ) do (

        REM For each toolset T  -- aka VS macro $(PlatformToolset)


        for %%T in (
            v140
        ) do (

            REM For each platform (short name) P -- aka VS macro $(PlatformShortName)

            for %%P in (
                x64
            ) do (
                set DLL_SFX=""
                if "%%C"=="Debug" set DLL_SFX="d"

                if "%%P"=="x86"  set MSVC_PLAT=32
                if "%%P"=="x64"  set MSVC_PLAT=64

                REM "OUTDIR" is the directory to which we copy stuff for this
                REM loop iteration

                set OUTDIR=!SRCDIR_ROOT!%%P\%%C\%%T\

                REM Copy dlls

                set SDIR=!SDKDIR!\%%P\%%C\%%T
                xcopy /D/I/Y !SDIR!\*.dll !OUTDIR!
				xcopy /D/I/Y !SDIR!\*.pdb !OUTDIR!
                

                REM --------------------------------------------------------------------------------
                REM Ximea  (xiC camera)
                REM --------------------------------------------------------------------------------
                xcopy /D/I/Y !XIMEADIR!\%%P\xiapi!MSVC_PLAT!.dll                                    !OUTDIR! 

                set OPENCVDIR=!GS_THIRDPARTYDIR!\OpenCV\v3.4.3
                xcopy /D/I/Y !OPENCVDIR!\%%P\%%C\%%T\opencv_world343!DLL_SFX!.dll                   !OUTDIR! 
       
            )


        )
    )





pause
