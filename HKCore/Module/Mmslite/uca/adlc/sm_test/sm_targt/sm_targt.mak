##########################################################################
# SISCO SOFTWARE MODULE HEADER ###########################################
##########################################################################
#			       						 #
# MODULE NAME : sm_targt.mak                       			 #
# PRODUCT(S)  : MMS-EASE-Lite						 #
#			       						 #
# MODULE DESCRIPTION :        						 #
#	This makefile is used by the 'nmake' utility to build the target #
# serial manager test server.  All paths including header files and      #
# object modules are relative to the current project directory which     #
# makes this file as environment independent as possible.  Both the      #
# DEBUG and Non DEBUG versions of the Utilities are made with this       #
# script								 #
#									 #
# To make the sm_targt.exe which shows calling information, enter the 	 #
# following:								 #
#									 #
# 	nmake -a -f sm_targt.mak "DEBUG=1"			         #
#									 #
# To make the sn_targt.exe, enter the following:		         #
#									 #
# 	nmake -a -f sm_targt.mak "DEBUG=0"			         #
#			       						 #
# MODIFICATION LOG :	       						 #
#  Date     Who   Rev			Comments			 #
# --------  ---  ------   -------------------------------------------    #
# 08/07/01  RKR    02     Removed S_THISFILE				 #
# 06/15/98  RWM           Created                                      	 #
##########################################################################

INCDIR = \mmslite\inc
SRCDIR = \sm_test\sm_targt
LIBDIR = \mmslite\lib

CC = cl
LINK = link

PROJ    = SM_TARGT

!if "$(DEBUG)" == "1"

OBJDIR =  .\debug
EXE     = .\debug\$(PROJ).exe
MAPFILE = .\debug\$(PROJ).map

CFLAGS = /c /f- /nologo /Fo$(OBJDIR)\ /Gs /AL /Gt16 \
          /Ot /W3 /I$(INCDIR) \
         /DDEBUG_SISCO /DESSENTIAL_COM
         
LIBS = $(LIBDIR)\mmsld.lib $(LIBDIR)\slogd.lib $(LIBDIR)\utild.lib \
       $(LIBDIR)\memd.lib $(LIBDIR)\ecll.lib

!else

OBJDIR =  .\release
EXE     = .\release\$(PROJ).exe
MAPFILE = .\release\$(PROJ).map

CFLAGS = /c /f- /nologo /Fo$(OBJDIR)\ /Gs /AL /Gt16 \
          /Ot /W3 /I$(INCDIR) /DESSENTIAL_COM
          
LIBS = $(LIBDIR)\ecll.lib          
          
!endif         


LFLAGS = /CO /MAP:FULL /NOE /NOI /ST:8192

INCLUDES = 

OBJECTS = $(OBJDIR)\adlc_dsm.obj \
          $(OBJDIR)\sm_targt.obj

$(EXE): $(OBJECTS)
        $(LINK) $(OBJECTS), \
        $(EXE), \
        $(MAPFILE) $(LFLAGS), \
        $(LIBS); >> cc.lst
        
$(OBJDIR)\adlc_dsm.obj: $(SRCDIR)\adlc_dsm.c $(INCLUDES)
	$(CC) $(CFLAGS) $(SRCDIR)\adlc_dsm.c ; >> cc.lst

$(OBJDIR)\sm_targt.obj: $(SRCDIR)\sm_targt.c $(INCLUDES)
	$(CC) $(CFLAGS) $(SRCDIR)\sm_targt.c ; >> cc.lst


