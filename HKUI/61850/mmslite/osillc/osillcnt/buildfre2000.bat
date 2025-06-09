REM ---
REM --- This batch file should be used to build the OSILLC driver
REM --- for Windows 2000/XP on Windows 2000 (cfg for DDK - Nov 2002).
REM ---
del objfre_w2k_x86\*.mac
del objfre_w2k_x86\i386\*.obj
del objfre_w2k_x86\i386\*.res
copy sources.2000 sources
build
md win2000
copy i386\*.sys win2000\*.sys
copy i386\*.pdb win2000\*.pdb
