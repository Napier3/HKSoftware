REM ---
REM --- This batch file should be used to build the OSILLC driver
REM --- for Windows NT on Windows NT (checked).
REM ---
md i386
md i386\checked
del obj\i386\*.obj
del obj\*.mac
copy sources.nt sources
build
md winNT
copy i386\checked\*.sys  winNT\*.sys
REM ---
REM --- Use NuMega\SoftIce\Symbol Loader to create osillc.nms file
REM --- for debugging with SoftIce.
REM ---