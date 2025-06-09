@echo off
echo This batch file makes directory for 'cositpxe.exe', runs linkloc to build it.
mkdir \mmslite\mvl\usr\client\pharlap
linkloc @c:\pharemb\monitor\mytarget.lnk @\mmslite\cmd\pharlap\cositpxe.lnk @\mmslite\cmd\pharlap\ositpxed.lnk
