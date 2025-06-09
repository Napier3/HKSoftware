@echo off
echo This batch file makes directory for 'uositcpe.exe', runs linkloc to build it.
mkdir \mmslite\mvl\usr\uca_srvr\pharlap
linkloc @c:\pharemb\monitor\mytarget.lnk @\mmslite\cmd\pharlap\uositcpe.lnk @\mmslite\cmd\pharlap\mmslibd.lnk

