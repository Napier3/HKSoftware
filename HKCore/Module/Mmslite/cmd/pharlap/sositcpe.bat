@echo off
echo This batch file makes directory for 'sositcpe.exe', runs linkloc to build it.
mkdir \mmslite\mvl\usr\server\pharlap
linkloc @c:\pharemb\monitor\mytarget.lnk @\mmslite\cmd\pharlap\sositcpe.lnk @\mmslite\cmd\pharlap\mmslibd.lnk

