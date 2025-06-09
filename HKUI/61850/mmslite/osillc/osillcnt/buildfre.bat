REM ---
REM --- This batch file should be used to build the OSILLC driver
REM --- for Windows NT on Windows NT.
REM ---
md i386
md i386\free
del obj\i386\*.obj
copy sources.nt sources
build
md winNT
copy i386\free\*.sys  winNT\*.sys

