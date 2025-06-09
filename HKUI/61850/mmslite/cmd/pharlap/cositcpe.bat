@echo off
echo This batch file makes directory for 'cositcpe.exe', runs linkloc to build it.
mkdir \mmslite\mvl\usr\client\pharlap
linkloc @c:\pharemb\monitor\mytarget.lnk @\mmslite\cmd\pharlap\cositcpe.lnk @\mmslite\cmd\pharlap\mmslibd.lnk
