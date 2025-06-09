@echo off
echo This batch file makes directory for 'sositpxe.exe', runs linkloc to build it.
mkdir \mmslite\mvl\usr\server\pharlap
linkloc @c:\pharemb\monitor\mytarget.lnk @\mmslite\cmd\pharlap\sositpxe.lnk @\mmslite\cmd\pharlap\ositpxed.lnk

