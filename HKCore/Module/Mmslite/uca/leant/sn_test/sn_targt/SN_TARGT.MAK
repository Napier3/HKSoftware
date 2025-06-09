##########################################################################
# SISCO SOFTWARE MODULE HEADER ###########################################
##########################################################################
#			       						 #
# MODULE NAME : sn_targt.mak                       			 #
# PRODUCT(S)  : MMS-EASE-Lite						 #
#			       						 #
# MODULE DESCRIPTION :        						 #
#	This makefile is used by the 'nmake' utility to build the target #
# subnetwork test server.  All paths including header files and          #
# object modules are relative to the current project directory which     #
# makes this file as environment independent as possible.  Both the      #
# DEBUG and Non DEBUG versions of the Utilities are made with this       #
# script								 #
#									 #
# To make the sn_targt.exe which shows calling information, enter the 	 #
# following:								 #
#									 #
# 	nmake -a -f sn_targt.mak "DEBUG=1"			         #
#									 #
# To make the sn_targt.exe, enter the following:		         #
#									 #
# 	nmake -a -f sn_targt.mak "DEBUG=0"			         #
#			       						 #
# MODIFICATION LOG :	       						 #
#  Date     Who   Rev			Comments			 #
# --------  ---  ------   -------------------------------------------    #
# 08/07/01  RKR    02     Removed S_THISFILE				 #
# 06/15/98  RWM           Created                                      	 #
##########################################################################

INCDIR = \mmslite\inc
SRCDIR = \sn_test\sn_targt
LIBDIR = \mmslite\lib

CC = cl
LINK = link

PROJ    = SN_TARGT

!if "$(DEBUG)" == "1"

OBJDIR =  .\debug
EXE     = .\debug\$(PROJ).exe
MAPFILE = .\debug\$(PROJ).map

CFLAGS = /c /f- /nologo /Fo$(OBJDIR)\ /Gs /AL /Gt16 \
          /Ot /W3 /I$(INCDIR) \
         /DDEBUG_SISCO
         
LIBS = $(LIBDIR)\slogd.lib $(LIBDIR)\utild.lib \
       $(LIBDIR)\memd.lib

!else

OBJDIR =  .\release
EXE     = .\release\$(PROJ).exe
MAPFILE = .\release\$(PROJ).map

CFLAGS = /c /f- /nologo /Fo$(OBJDIR)\ /Gs /AL /Gt16 \
          /Ot /W3 /I$(INCDIR)
                    
!endif         


LFLAGS = /CO /MAP:FULL /NOE /NOI /ST:8192

INCLUDES = 

OBJECTS = $(OBJDIR)\clnp_hc.obj  \
          $(OBJDIR)\clnp_eth.obj \
          $(OBJDIR)\llcio.obj \
          $(OBJDIR)\sn_targt.obj
          

!if "$(DEBUG)" == "1"
$(EXE): $(OBJECTS)
        $(LINK) $(OBJECTS), \
        $(EXE), \
        $(MAPFILE) $(LFLAGS), \
        $(LIBS); >> cc.lst
!else
$(EXE): $(OBJECTS)
        $(LINK) $(OBJECTS), \
        $(EXE), \
        $(MAPFILE) $(LFLAGS); >> cc.lst
!endif        
        
$(OBJDIR)\clnp_hc.obj: $(SRCDIR)\clnp_hc.c $(INCLUDES)
	$(CC) $(CFLAGS) $(SRCDIR)\clnp_hc.c ; >> cc.lst

$(OBJDIR)\clnp_eth.obj: $(SRCDIR)\clnp_eth.c $(INCLUDES)
	$(CC) $(CFLAGS) $(SRCDIR)\clnp_eth.c ; >> cc.lst
        
$(OBJDIR)\llcio.obj: $(SRCDIR)\llcio.c $(INCLUDES)
	$(CC) $(CFLAGS) $(SRCDIR)\llcio.c ; >> cc.lst

$(OBJDIR)\sn_targt.obj: $(SRCDIR)\sn_targt.c $(INCLUDES)
	$(CC) $(CFLAGS) $(SRCDIR)\sn_targt.c ; >> cc.lst
