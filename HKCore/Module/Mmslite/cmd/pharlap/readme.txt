INSTRUCTIONS FOR BUILDING SAMPLE TARGET EXECUTABLES WITH PHARLAP TNT/ETS 9.1
----------------------------------------------------------------------------
USING "MICROSOFT VISUAL C++ VERSION 5.0"
------------------------------------------------------

Object and Library files for Pharlap targets are built using the same
"Project" and "Workspace" files as for WIN32 (i.e. Windows 95/NT).
Although it is not absolutely necessary
to build the WIN32 "executables", it is advisable to do so, if only to verify
that all the objects and libraries are compiled correctly.

There are only a few additional steps that must be taken to build Pharlap
target executables:

1.  Modify the "Util" project to add the following "Preprocessor
    definition":

       PHARLAP_ETS

    Then rebuild the library.

2.   Modify "server.c" (or "uca_srvr.c", etc.) to set
    "m_heap_check_enable = SD_FALSE" so that Heap checking
    is NOT performed.  Pharlap does not support the "_heapwalk" function
    which would be called if this flag was SD_TRUE.


3.  Control-C does not seem get passed to the Pharlap application, so the
    Control-C handling code in server.c, etc. never gets executed. If a
    "graceful" exit is needed under Pharlap, it can be done by simply setting
    "doIt = SD_FALSE" on an appropriate event. If checking for "_kbhit" is
    appropirate for your target, the following could be added to the main
    loop:

      if (_kbhit ())
        doIt = SD_FALSE;


4.  Use the "Visual System Builder" provided by Pharlap to create a new
    boot disk for your target.  This is described very simply in Section 4.3
    of "Getting Started with ETS TCP/IP Networking" (pg 21).  Make sure that
    the ethernet driver settings are correct for the ethernet hardware on
    your target.

5.  Modify the batch files in
    "\mmslite\cmd\pharlap" to replace "mytarget.lnk" with the appropriate "lnk"
    file for your target (created by Step #2 above).

6.  Run the batch files to build the appropriate Pharlap target executable.
    These can be run from the command
    line or from the Developer Studio, depending on how you set up your
    Pharlap environment.  See pg 46 of "ETS Kernel User's Guide: Basics of
    Operation" for how to set up the environment.

    Building from the Developer Studio should make debugging more convenient.
    To do so, follow the instructions on page 54 of "ETS Kernel User's Guide:
    Basics of Operation".

      For the "Build command line" enter:

        \mmslite\cmd\pharlap\cositcpe.bat		#for Client
        \mmslite\cmd\pharlap\sositcpe.bat		#for Server
        \mmslite\cmd\pharlap\uositcpe.bat		#for UCA Server

      For the "Output file name" enter:

         \mmslite\mvl\usr\client\pharlap\cositcpe.exe	#for Client
         \mmslite\mvl\usr\server\pharlap\sositcpe.exe	#for Server
         \mmslite\mvl\usr\uca_srvr\pharlap\uositcpe.exe	#for UCA Server

7.  With Pharlap ETS Version 9.1, if you run the sample applications from the
    debugger, the "Working directory" setting in the Developer Studio does
    not appear to work.  Instead it appears to use the directory where your
    "Project" file (*.dsp) resides.  You may need move configuration files
    there, and look for log files there.

    If you run with "runemb" it appears to use the current directory.



INSTRUCTIONS FOR ADDING OSI SUPPORT
-----------------------------------
If OSI support is needed, it can easily be added, but because of the Phar Lap
driver architecture, it can only be done with TCP/IP support enabled.  This
means that you must use the "ositpxe" library (not the "ositp4e" library).
Also the ethernet driver must be modified slightly to make this work.

Changes that must be made to the Ethernet Driver
------------------------------------------------------------
1.  Add the following include statement after "#include <tcpdrivr.h>":

      #include <clnp_tnt.h>       // SISCO stub function prototypes

2.  Replace the call to "EtsTCPRegisterDeviceFuncs"
    with a call to      "stubEtsTCPRegisterDeviceFuncs".
    Do NOT change the arguments to the function.


3.  Replace the call to "EtsTCPSetDeviceEthernetInfo"
    with a call to      "stubEtsTCPSetDeviceEthernetInfo"
    Do NOT change the arguments to the function.

3.  Replace the call to "EtsTCPQueueRecvBuffer"
    with a call to      "stubEtsTCPQueueRecvBuffer"
    and add "pkt_len" as argument #3
    and     "pRecvBuf" as argument #4.
    For the NE2K driver, for example, it would be as follows:

      stubEtsTCPQueueRecvBuffer(n2kCfg->deviceHandle, hMsg, pkt_len, pRecvBuf);

    NOTE: for other drivers, the names of argument #3 and 4 might be different.

4.  Add the following "case" to the "xxxx_ioctl" function to enable
    reception of Multicast packets:

      case ENIOADDMULTI:
        /* Insert code here to enable reception of Multicast packets.	*/
        /* This is different for every ethernet driver.			*/
        break;

5.  Add the following to the compile command so the include file "clnp_tnt.h"
    will be found:

      -I\mmslite\inc

6.  Build the new library and copy it to "\pharemb\lib" so the linker can
    find it.

     
Changes that must be made to the "ositpxe.lib" library
------------------------------------------------------------
1.  In the makefile (or Microsoft Developer Studio project) replace
    "clnp_w32.c" (Windows Subnet code) with
    "clnp_tnt.c" (Phar Lap Subnet code).

2.  Add "\pharemb\lib\build\eth-drv\inc" to the set of directories to search
    for include files.  This is needed to find "tcpdrivr.h". Modify this
    path appropriately if this file is stored in a different location.

3.  Rebuild the library "ositpxe.lib" (or "ositpxed.lib" for DEBUG version).

