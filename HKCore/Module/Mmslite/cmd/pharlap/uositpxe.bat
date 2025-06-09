@echo off
echo This batch file makes directory for 'uositpxe.exe', runs linkloc to build it.
mkdir \mmslite\mvl\usr\uca_srvr\pharlap
linkloc @c:\pharemb\monitor\mytarget.lnk @\mmslite\cmd\pharlap\uositpxe.lnk @\mmslite\cmd\pharlap\ositpxed.lnk

