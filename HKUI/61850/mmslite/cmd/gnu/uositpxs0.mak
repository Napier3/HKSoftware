##########################################################################
#  SISCO SOFTWARE MODULE HEADER ##########################################
##########################################################################
#			       						 #
# MODULE NAME : uositpxs0.mak                       			 #
# PRODUCT(S)  : MMS-EASE-Lite						 #
#			       						 #
# MODULE DESCRIPTION :        						 #
# This makefile is used by the Linux 'make' utility to build the Server  #
# example for MMS-EASE-Lite. All paths including header 		 #
# files and object modules are relative to the current project directory #
# which makes this file as environment independent as possible.  	 #
# Usage instructions are given below as well as a brief description of   #
# each switch used in the process.  					 #
#									 #
# To make the uositpxs0_ld executable:					 #
# 	make -f uositpxs0.mak    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO	 #
#									 #
# MODIFICATION LOG :	       						 #
#  Date     Who   Rev			Comments			 #
# --------  ---  ------   -------------------------------------------	 #
# 03/08/07  JRB    01     Created from uositcps0.mak by replacing
#			  ositcps.a with ositpxs.a
##########################################################################

# Include common and platform-dependent definitions
include ./platform.mak

# Define directories here

OPT   =
DEFS  =
LIBDIR = ../../lib
INCDIR = ../../inc
SRCDIR = ../../mvl/usr/uca_srvr
MMSOPDIR = ../../mvl/usr/uca_srvr
MMSSRCDIR = ../../src
MVLSRCDIR = ../../mvl/src
USRSRCDIR = ../../mvl/usr
ACSESRCDIR = ../../mvl/src/acse
FOUNDRYDIR = ../../bin
EXEDIR = ../../mvl/usr/uca_srvr
VPATH = $(SRCDIR) $(MVLSRCDIR) $(ACSESRCDIR) $(MMSSRCDIR) $(USRSRCDIR) \
	$(LIBDIR) $(OBJDIR) $(INCDIR)

PROJ  = uositpxs0$(DFLAG)
OBJDIR = obj_$(PROJ)
LIST  = >> cc.lst 2>&1

ALL_CFLAGS = $(PLATFORM_CFLAGS) \
	$(OPT) -I$(INCDIR) $(DEFS) \
	-DMMS_LITE -DMOSI -DLEAN_T -I$(MMSOPDIR) -DMVL_UCA \
	$(CFLAGS)

#DEBUG: for some reason, putting ositpxs first, avoids undefined reference to asn1r_get_objid.
LIBS = \
	$(LIBDIR)/ositpxs$(DFLAG).a \
	$(LIBDIR)/mvlu$(DFLAG).a \
	$(LIBDIR)/mmsle$(DFLAG).a \
	$(LIBDIR)/mmsl$(DFLAG).a \
	$(LIBDIR)/asn1l$(DFLAG).a \
	$(LIBDIR)/mem$(DFLAG).a \
	$(LIBDIR)/slog$(DFLAG).a \
	$(LIBDIR)/util$(DFLAG).a \
	$(LIBDIR)/ssec0$(DFLAG).a

EXE = $(EXEDIR)/$(PROJ)

# Define includes dependancies
INCLUDES = $(INCDIR)/glbtypes.h \
	$(INCDIR)/sysincs.h \
	$(INCDIR)/mmsdefs.h \
	$(INCDIR)/glberror.h \
	$(INCDIR)/gen_list.h \
	$(INCDIR)/mem_chk.h \
	$(INCDIR)/mms_pvar.h \
	$(INCDIR)/mms_mp.h \
	$(INCDIR)/asn1defs.h \
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
	$(MMSOPDIR)/mmsop_en.h \
	$(MMSOPDIR)/uca_srvr.h \
	$(MMSOPDIR)/uca_obj.h

# Define objects used in the exectable
OBJECTS = \
	$(OBJDIR)/uca_srvr.o \
	$(OBJDIR)/rdwrind.o \
	$(OBJDIR)/mmsop_en.o \
	$(OBJDIR)/mvlop_en.o \
	$(OBJDIR)/mvl_acse.o \
	$(OBJDIR)/event2.o \
	$(OBJDIR)/logcfgx.o \
	$(OBJDIR)/reject.o \
	$(OBJDIR)/slogipc.o \
	$(OBJDIR)/uca_obj.o


# The main target is the executable
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
	rm -f $(SRCDIR)/uca_obj.c
	rm -f $(SRCDIR)/uca_obj.h
	rm -f $(EXE)
	rm -rf $(OBJDIR)
	echo "Finished clean" $(LIST)

# uca_obj.c (and uca_obj.h) are created using the foundry utility.
$(SRCDIR)/uca_obj.c : uca_obj.odf
	$(FOUNDRYDIR)/foundry_ld -o -c$(ALIGNDIR)/align.cfg -t$(SRCDIR)/leafmap.xml $(SRCDIR)/uca_obj.odf $(LIST)

$(SRCDIR)/uca_obj.h : uca_obj.odf
	$(FOUNDRYDIR)/foundry_ld -o -c$(ALIGNDIR)/align.cfg -t$(SRCDIR)/leafmap.xml $(SRCDIR)/uca_obj.odf $(LIST)


# Pattern rule for all object files
# NOTE: the $@ is the complete target name including the "$(OBJDIR)/" prefix
$(OBJDIR)/%.o : %.c
#	Enable next line to log name of file being compiled (may help clarify error messages).
#	echo Compiling: $< $(LIST)
	$(CC) -c $(ALL_CFLAGS) $< -o $@ $(LIST)

# Object file target dependencies. All use the pattern rule above.
$(OBJDIR)/uca_srvr.o : uca_srvr.c $(INCLUDES)
$(OBJDIR)/rdwrind.o : rdwrind.c $(INCLUDES)
$(OBJDIR)/mmsop_en.o : mmsop_en.c $(INCLUDES)
$(OBJDIR)/mvlop_en.o : mvlop_en.c $(INCLUDES)
$(OBJDIR)/mvl_acse.o : mvl_acse.c $(INCLUDES)
$(OBJDIR)/event2.o : event2.c $(INCLUDES)
$(OBJDIR)/logcfgx.o : logcfgx.c $(INCLUDES)
$(OBJDIR)/uca_obj.o : uca_obj.c $(INCLUDES)
$(OBJDIR)/reject.o : reject.c $(INCLUDES)
$(OBJDIR)/slogipc.o : $(MMSSRCDIR)/slogipc.c $(INCLUDES)
