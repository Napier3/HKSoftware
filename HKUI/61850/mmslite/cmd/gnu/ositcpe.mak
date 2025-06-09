##########################################################################
# SISCO SOFTWARE MODULE HEADER ###########################################
##########################################################################
#			       						 #
# MODULE NAME : ositcpe.mak                       			 #
# PRODUCT(S)  : MMS-EASE-Lite						 #
#			       						 #
# MODULE DESCRIPTION :        						 #
# This makefile is used by the Linux 'make' utility to build the         #
# LEANT-MOSI TP0 (RFC 1006) library for MMS-EASE-Lite.All paths including#
# header files and object modules are relative to the current project	 #
# directory which makes this file as environment independent as 	 #
# possible.  Both the DEBUG and Non DEBUG versions of the Utilities are  #
# made with this script.  						 #
#									 #
# To make the 'ositcpe_l.a' library:					 #
# 	make -f ositcpe.mak         DFLAG=_l   DEFS=-DDEBUG_SISCO	 #
# To make the 'ositcpe_n.a' library:					 #
# 	make -f ositcpe.mak   	    DFLAG=_n				 #
# To make the 'ositcpe_ld.a' library:					 #
# 	make -f ositcpe.mak  OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO	 #
# To make the 'ositcpe_nd.a' library:					 #
# 	make -f ositcpe.mak  OPT=-g DFLAG=_nd				 #
#			       						 #
# MODIFICATION LOG :	       						 #
#  Date     Who   Rev			Comments			 #
# --------  ---  ------   -------------------------------------------	 #
# 08/04/05  EJV    07     Moved platform defs to platform.mak.
#			  Revised link & clean. Added -c in compile rule.
# 01/24/05  JRB    06     Add lean_var.c
# 08/04/04  EJV    05     Add AIX OS support.
#			  Del tp4main.c
# 12/10/03  JRB    04     Add LYNX OS support. Del "no-stack-check" option.
# 10/21/03  JRB    03     Chg CFLAGS & LDFLAGS to be "user-settable",
#			   use $(AR), as recommended by GNU Make.
#			  Add "$(OBJDIR)/" prefix before all objects & "%.o",
#			   del "$(OBJDIR)/" prefix before "$@",
#			   then use $(OBJECTS) in $(AR) cmd.
#			  Use ARFLAGS (for QNX = -n -q, default = -r).
#			  Chg OBJDIR to "ositcpe...."
# 08/01/03  GLB    02     Add "acse2dib.c"				 #
# 12/18/02  CRM    01     Created from QNX makefile.			 #
##########################################################################

# Include common and platform-dependent definitions
include ./platform.mak

DFLAG  =
DEFS   =
OPT    =
LIBDIR = ../../lib
INCDIR = ../../inc
SRCDIR = ../../uca/leant ../../uca/acse
PROJ  = ositcpe$(DFLAG)
OBJDIR = obj_$(PROJ)
LIST  = >> cc.lst 2>&1
VPATH = $(SRCDIR) $(OBJDIR) $(LIBDIR) $(INCDIR)

ALL_CFLAGS = $(PLATFORM_CFLAGS) \
	$(OPT) -I$(INCDIR) $(DEFS) -DMMS_LITE \
	-DMOSI -DLEAN_T -DTP0_ENABLED \
	$(CFLAGS)

LIBRARY = $(LIBDIR)/$(PROJ).a

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

# These are the objects that belong in the library
OBJECTS = \
	$(OBJDIR)/acse2dec.o \
	$(OBJDIR)/acse2dib.o \
	$(OBJDIR)/acse2enc.o \
	$(OBJDIR)/acse2var.o \
	$(OBJDIR)/checksum.o \
	$(OBJDIR)/coppdaru.o \
	$(OBJDIR)/coppdcp.o \
	$(OBJDIR)/coppdcpr.o \
	$(OBJDIR)/copp_dec.o \
	$(OBJDIR)/copp_enc.o \
	$(OBJDIR)/cospmain.o \
	$(OBJDIR)/cosp_dec.o \
	$(OBJDIR)/cosp_enc.o \
	$(OBJDIR)/lean_cfg.o \
	$(OBJDIR)/lean_var.o \
	$(OBJDIR)/osicfgx.o \
	$(OBJDIR)/tp0calld.o \
	$(OBJDIR)/tp0callg.o \
	$(OBJDIR)/tp0main.o \
	$(OBJDIR)/tp0_dec.o \
	$(OBJDIR)/tp0_sock.o \
	$(OBJDIR)/tp0_unix.o \
	$(OBJDIR)/tp4calld.o \
	$(OBJDIR)/tp4callg.o \
	$(OBJDIR)/tp4port.o \
	$(OBJDIR)/tp4_enc.o \
	$(OBJDIR)/tpx_dec.o


# Main target is the library
# If any objects have changed, delete and recreate it.
$(LIBRARY): $(OBJECTS)
	rm -f $(LIBRARY)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJECTS) $(LIST)
	echo "FINISHED CREATING $(LIBRARY) LIBRARY" $(LIST)
	echo "-----------------------------------------------------" $(LIST)

clean:
	rm -f $(OBJECTS)
	rm -f $(LIBRARY)
	rm -rf $(OBJDIR)
	echo "Finished clean" $(LIST)

# Pattern rule for all object files
# NOTE: the $@ is the complete target name including the "$(OBJDIR)/" prefix
$(OBJDIR)/%.o : %.c
#	Enable next line to log name of file being compiled (may help clarify error messages).
#	echo Compiling: $< $(LIST)
	$(CC) -c $(ALL_CFLAGS) $< -o $@ $(LIST)

# Object file target dependencies. All use the pattern rule above.
$(OBJDIR)/acse2dec.o : acse2dec.c $(INCLUDES)
$(OBJDIR)/acse2dib.o : acse2dib.c $(INCLUDES)
$(OBJDIR)/acse2enc.o : acse2enc.c $(INCLUDES)
$(OBJDIR)/acse2var.o : acse2var.c $(INCLUDES)
$(OBJDIR)/checksum.o : checksum.c $(INCLUDES)
$(OBJDIR)/coppdaru.o : coppdaru.c $(INCLUDES)
$(OBJDIR)/coppdcp.o : coppdcp.c $(INCLUDES)
$(OBJDIR)/coppdcpr.o : coppdcpr.c $(INCLUDES)
$(OBJDIR)/copp_dec.o : copp_dec.c $(INCLUDES)
$(OBJDIR)/copp_enc.o : copp_enc.c $(INCLUDES)
$(OBJDIR)/cospmain.o : cospmain.c $(INCLUDES)
$(OBJDIR)/cosp_dec.o : cosp_dec.c $(INCLUDES)
$(OBJDIR)/cosp_enc.o : cosp_enc.c $(INCLUDES)
$(OBJDIR)/lean_cfg.o : lean_cfg.c $(INCLUDES)
$(OBJDIR)/lean_var.o : lean_var.c $(INCLUDES)
$(OBJDIR)/osicfgx.o : osicfgx.c $(INCLUDES)
$(OBJDIR)/tp0calld.o : tp0calld.c $(INCLUDES)
$(OBJDIR)/tp0callg.o : tp0callg.c $(INCLUDES)
$(OBJDIR)/tp0main.o : tp0main.c $(INCLUDES)
$(OBJDIR)/tp0_dec.o : tp0_dec.c $(INCLUDES)
$(OBJDIR)/tp0_sock.o : tp0_sock.c $(INCLUDES)
$(OBJDIR)/tp0_unix.o : tp0_unix.c $(INCLUDES)
$(OBJDIR)/tp4calld.o : tp4calld.c $(INCLUDES)
$(OBJDIR)/tp4callg.o : tp4callg.c $(INCLUDES)
$(OBJDIR)/tp4port.o : tp4port.c $(INCLUDES)
$(OBJDIR)/tp4send.o : tp4send.c $(INCLUDES)
$(OBJDIR)/tp4_dec.o : tp4_dec.c $(INCLUDES)
$(OBJDIR)/tp4_enc.o : tp4_enc.c $(INCLUDES)
$(OBJDIR)/tpx_dec.o : tpx_dec.c $(INCLUDES)
