##########################################################################
# SISCO SOFTWARE MODULE HEADER ###########################################
##########################################################################
#			       						 #
# MODULE NAME : mbufcalc.mak                       			 #
# PRODUCT(S)  : MMS-EASE-Lite						 #
#			       						 #
#	This makefile is used by the Linux 'make' utility to build the   #
# utility to calculate the mms decode buffer size for MMS-EASE-Lite.     #
# All paths including header 						 #
# files and object modules are relative to the current project directory # 
# which makes this file as environment independent as possible.  	 #
# Usage instructions are given below as well as a brief description of   #
# each switch used in the process.  					 #
#									 #
# To make the MBUFCALC_LD:						 #
# 	make -f mbufcalc.mak   OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO	 #
#									 #
# MODIFICATION LOG :	       						 #
#  Date     Who   Rev			Comments			 #
# --------  ---  ------   -------------------------------------------	 #
# 08/04/05  EJV    05     Moved platform defs to platform.mak.
#			  Revised link & clean. Added -c in compile rule.
# 08/04/04  EJV    04     Add AIX OS support.
# 12/10/03  JRB    03     Add LYNX OS support. Del "no-stack-check" option.
# 10/21/03  JRB    02     Chg CFLAGS & LDFLAGS to be "user-settable",
#			  as recommended by GNU Make.
#			  Add "$(OBJDIR)/" prefix before all objects & "%.o",
#			   del "$(OBJDIR)/" prefix before "$@",
#			   then use $(OBJECTS) in link cmd.
#			  Del "LIBS" var, then chg "LIBSPATH" to "LIBS"
# 12/19/02  CRM    01     Created from QNX makefile.			 #
##########################################################################

# Include common and platform-dependent definitions
include ./platform.mak

# set the library, object, and include file path names
DFLAG  =
DEFS   =
OPT    =
LIBDIR = ../../lib
OBJDIR = obj$(DFLAG)
INCDIR = ../../inc
MMSOPDIR = ../../inc/mmsop_en
SRCDIR = ../../mvl/util/mbufcalc
PROJ  = mbufcalc$(DFLAG)
EXEDIR = ../../bin
LIST  = >> cc.lst 2>&1
VPATH = $(SRCDIR) $(OBJDIR) $(LIBDIR) $(INCDIR)

ALL_CFLAGS = $(PLATFORM_CFLAGS) \
	$(OPT) -I$(INCDIR) \
	-I$(MMSOPDIR) $(DEFS) -DMMS_LITE \
	$(CFLAGS)

LIBS = $(LIBDIR)/mmsl$(DFLAG).a $(LIBDIR)/asn1l$(DFLAG).a $(LIBDIR)/mem$(DFLAG).a \
            $(LIBDIR)/mvl$(DFLAG).a $(LIBDIR)/util$(DFLAG).a \
           $(LIBDIR)/slog$(DFLAG).a $(LIBDIR)/meml$(DFLAG).a 
     
EXE = $(EXEDIR)/$(PROJ)

# setup the dependencies for the source files
INCLUDES = $(INCDIR)/glbtypes.h \
	$(INCDIR)/sysincs.h \
	$(INCDIR)/mmsdefs.h \
	$(INCDIR)/glberror.h \
	$(INCDIR)/gen_list.h \
	$(INCDIR)/mem_chk.h \
	$(INCDIR)/mms_pvar.h \
	$(INCDIR)/mms_mp.h \
	$(INCDIR)/asn1defs.h \
	$(INCDIR)/str_util.h \
	$(INCDIR)/slog.h \
	$(INCDIR)/mms_vvar.h \
	$(INCDIR)/mms_err.h \
	$(INCDIR)/mms_def2.h \
	$(INCDIR)/mmsintr2.h \
	$(INCDIR)/mmsldefs.h \
	$(INCDIR)/mms_dfun.h \
	$(INCDIR)/mms_perr.h \
	$(INCDIR)/mms_log.h \
	$(INCDIR)/mmslog.h \
	$(INCDIR)/mms_pcon.h \
	$(INCDIR)/mms_pdom.h \
	$(INCDIR)/mms_pevn.h \
	$(INCDIR)/mms_pfil.h \
	$(INCDIR)/mms_pjou.h \
	$(INCDIR)/mms_pocs.h \
	$(INCDIR)/mms_pprg.h \
	$(INCDIR)/mms_psem.h \
	$(INCDIR)/mms_pvmd.h \
	$(INCDIR)/mmsefun.h \
	$(MMSOPDIR)/mmsop_en.h 

# object files
OBJECTS = $(OBJDIR)/mbufcalc.o

# Main target is the executable
$(EXE):	$(OBJECTS) $(LIBS)
	rm -f $(EXE)
	$(PLATFORM_LINKER) $(PLATFORM_LDFLAGS) $(LDFLAGS) $(PLATFORM_CFLAGS) $(CFLAGS) \
	  -o$(EXE) $(OBJECTS) \
	  $(LIBS) \
	  $(PLATFORM_LIBS) $(LIST)
	echo "FINISHED GENERATING $(EXE) EXECUTABLE" $(LIST)
	echo "-----------------------------------------------------" $(LIST)

clean:
	rm -f $(OBJECTS)
	rm -f $(EXE)
	echo "Finished clean" $(LIST)

# Pattern rule for all object files
# NOTE: the $@ is the complete target name including the "$(OBJDIR)/" prefix
$(OBJDIR)/%.o : %.c
#	Enable next line to log name of file being compiled (may help clarify error messages).
#	echo Compiling: $< $(LIST)
	$(CC) -c $(ALL_CFLAGS) $< -o $@ $(LIST)

# Object file target dependencies. All use the pattern rule above.
$(OBJDIR)/mbufcalc.o : mbufcalc.c $(INCLUDES)
