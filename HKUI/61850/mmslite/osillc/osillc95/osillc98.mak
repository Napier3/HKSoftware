#
# OSILLC95.mak - makefile for OSILLC95 VxD
#
DEVICENAME = OSILLC98
DYNAMIC = 1
NDIS = 1
FRAMEWORK = C
DEBUG = 1
BROWSE = 0
XFLAGS = /I..\OsillcCommon

INCLUDES = ..\OsillcCommon\osillc.h ..\OsillcCommon\conpack.h osillc95.h
OBJECTS  = osillc95.obj openclos.obj read.obj write.obj request.obj reset.obj \
		   lock.obj framepool.obj irppool.obj

!include $(VTOOLSD)\include\vtoolsd.mak
!include $(VTOOLSD)\include\vxdtarg.mak

osillc95.obj:	osillc95.c $(INCLUDES)
openclos.obj:	openclos.c $(INCLUDES)
read.obj:	read.c $(INCLUDES)
write.obj:	write.c $(INCLUDES)
request.obj:	request.c $(INCLUDES)
reset.obj:	reset.c $(INCLUDES)
lock.obj:	lock.c $(INCLUDES)
framepool.obj:	framepool.c $(INCLUDES)
irppool.obj:	irppool.c $(INCLUDES)

