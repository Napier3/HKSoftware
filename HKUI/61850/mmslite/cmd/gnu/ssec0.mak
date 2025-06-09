##########################################################################
# SISCO SOFTWARE MODULE HEADER ###########################################
##########################################################################
#			       						 #
# MODULE NAME : ssec0.mak                       			 #
# PRODUCT(S)  : MMS-EASE-Lite						 #
#			       						 #
# MODULE DESCRIPTION :        						 #
# This makefile is used by the Linux 'make' utility to build the Memory	 #
# allocation library for MMS-EASE-Lite.  All paths including header 	 #
# files and object modules are relative to the current project directory #
# which makes this file as environment independent as possible.  Both    #
# the DEBUG and Non DEBUG versions of the Utilities are made with this   #
# script								 #
#									 #
# To make the 'ssec0_l.a' library:					 #
# 	make -f ssec0.mak     	    DFLAG=_l   DEFS=-DDEBUG_SISCO	 #
# To make the 'ssec0_n.a' library:					 #
# 	make -f sec0.mak     	    DFLAG=_n				 #
# To make the 'ssec0_ld.a' library:					 #
# 	make -f ssec0.mak     OPT=-g DFLAG=_ld   DEFS=-DDEBUG_SISCO	 #
# To make the 'ssec0_nd.a' library:					 #
# 	make -f ssec0.mak     OPT=-g DFLAG=_nd				 #
#			       						 #
# MODIFICATION LOG :	       						 #
#  Date     Who   Rev			Comments			 #
# --------  ---  ------   -------------------------------------------	 #
# 08/04/05  EJV    04     Moved platform defs to platform.mak.
#			  Revised link & clean. Added -c in compile rule.
# 08/04/04  EJV    03     Add AIX OS support.
# 12/10/03  JRB    02     Add LYNX OS support. Del "no-stack-check" option.
# 10/17/03  JRB    01     New
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
SRCDIR = ../../security/ssec
PROJ  = ssec0$(DFLAG)
LIST  = >> cc.lst 2>&1
VPATH = $(SRCDIR) $(OBJDIR) $(LIBDIR) $(INCDIR)

ALL_CFLAGS = $(PLATFORM_CFLAGS) \
	$(OPT) -I$(INCDIR) $(DEFS) -DMMS_LITE \
	$(CFLAGS)

# setup the dependencies for the source files
INCLUDES = $(INCDIR)/glbtypes.h \
	$(INCDIR)/sysincs.h \
	$(INCDIR)/ssec.h 

# These are the objects that belong in the library
OBJECTS = $(OBJDIR)/ssecusr0.o

LIBRARY = $(LIBDIR)/$(PROJ).a

# Main target is the library
# If any objects have changed, delete and recreate it.
$(LIBRARY): $(OBJECTS)
	rm -f $(LIBRARY) $(LIST)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJECTS) $(LIST)
	echo "FINISHED CREATING $(LIBRARY) LIBRARY" $(LIST)
	echo "-----------------------------------------------------" $(LIST)

clean:
	rm -f $(OBJECTS)
	rm -f $(LIBRARY)
	echo "Finished clean" $(LIST)

# Pattern rule for all object files
# NOTE: the $@ is the complete target name including the "$(OBJDIR)/" prefix
$(OBJDIR)/%.o : %.c
#	Enable next line to log name of file being compiled (may help clarify error messages).
#	echo Compiling: $< $(LIST)
	$(CC) -c $(ALL_CFLAGS) $< -o $@ $(LIST)

# Object file target dependencies. All use the pattern rule above.
$(OBJDIR)/ssecusr0.o : ssecusr0.c $(INCLUDES)
