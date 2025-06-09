REM ---
REM --- This batch file should be used to build the OSILLC driver
REM --- for Windows XP on Windows XP (cfg for DDK - Nov 2002).
REM ---
REM --- This driver may run on Windows 2000, but MS does not recommend
REM --- to use the driver made on a higher version of Windows to run on
REM --- lower version.
REM ---
del objfre_wxp_x86\*.mac
del objfre_wxp_x86\i386\*.obj
del objfre_wxp_x86\i386\*.res
copy sources.2000 sources
build
md winXP
copy i386\*.sys winXP\*.sys
copy i386\*.pdb winXP\*.pdb
