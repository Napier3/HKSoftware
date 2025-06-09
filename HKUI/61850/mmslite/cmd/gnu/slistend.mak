##########################################################################
# SISCO SOFTWARE MODULE HEADER ###########################################
##########################################################################
#			       						 #
# MODULE NAME : slistend.mak                       			 #
# PRODUCT(S)  : MMS-EASE-Lite						 #
#			       						 #
# MODULE DESCRIPTION :        						 #
# This makefile is used by the Linux 'make' utility to build the socket	 #
# "Listen" Task/Thread for MMS-EASE-Lite. All paths including header	 #
# files and object modules are relative to the current project 	 	 #
# directory which makes this file as environment independent as 	 #
# possible.								 #
#									 #
# To make the SLISTEND:							 #
# 	make -f slistend.mak    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO	 #
#			       						 #
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
# 12/18/02  CRM    01     Created from QNX makefile.			 #
##########################################################################

# Include common and platform-dependent definitions
include ./platform.mak

# set the library, object, and include file path names
DFLAG  =
DEFS   =
OPT    =
LIBS   =
LIBDIR = ../../lib
OBJDIR = obj$(DFLAG)
INCDIR = ../../inc
SRCDIR = ../../uca/leant
PROJ  = slistend
EXEDIR = ../../bin
LIST  = >> cc.lst 2>&1
VPATH = $(SRCDIR) $(OBJDIR) $(LIBDIR) $(INCDIR)

ALL_CFLAGS = $(PLATFORM_CFLAGS) \
	$(OPT) -I$(INCDIR) $(DEFS) -DMMS_LITE \
	-DMOSI -DLEAN_T -DTP0_ENABLED \
	$(CFLAGS)

EXE = $(EXEDIR)/$(PROJ)

# setup the dependencies for the source files
INCLUDES = $(INCDIR)/glbtypes.h \
	$(INCDIR)/sysincs.h \
	$(INCDIR)/stime.h \
	$(INCDIR)/slog.h \
	$(INCDIR)/mem_chk.h \
	$(INCDIR)/memlog.h \
	$(INCDIR)/gen_list.h \
	$(INCDIR)/stime.h \
	$(INCDIR)/lean_a.h \
	$(INCDIR)/acse2log.h \
	$(INCDIR)/asn1defs.h \
	$(INCDIR)/acse2usr.h \
	$(INCDIR)/acse2.h \
	$(INCDIR)/tp0_sock.h \
	$(INCDIR)/tp4.h \
	$(INCDIR)/tp4_encd.h \
	$(INCDIR)/tp4_log.h \
	$(INCDIR)/tp4api.h \
	$(INCDIR)/cfglog.h \
	$(INCDIR)/checksum.h \
	$(INCDIR)/cfg_util.h \
	$(INCDIR)/clnp_log.h \
	$(INCDIR)/clnp_usr.h

# object files
OBJECTS = $(OBJDIR)/tp0_list.o

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
$(OBJDIR)/tp0_list.o : tp0_list.c $(INCLUDES)
