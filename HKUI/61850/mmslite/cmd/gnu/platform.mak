#########################################################################
# SISCO SOFTWARE MODULE HEADER ##########################################
#########################################################################
#			       					        #
# MODULE NAME : platform.mak                       			#
# PRODUCT(S)  : MMS-LITE, MMS-LITE-SECURE				#
#			       					        #
# MODULE DESCRIPTION :        					        #
#      This makefile is included by all makefiles to provide platform	#
#      dependent defines.						#
#			       						#
#									#
# MODIFICATION LOG :	       						#
#  Date     Who   Rev			Comments			#
# --------  ---  ------   -------------------------------------------	#
# 02/16/07  RKR    03     Added -lrt for STDLIB
# 09/20/05  EJV    02     Added comment for QNX flags
# 08/04/05  EJV    01     Extracted from MMS-LITE makefiles & added	#
#			  multithread support.				#
#########################################################################

# ------------------------------------------------------------------------
#  NOTE: If available, the platform.mak included in every makefile
#        specifies pthreads support. There is small performance penalty
#        when multithread support is enabled.
#        See each platform for note how to disable the multithread support.
#
#  The MMS-LITE-SECURE needs to be compiled with multithread support!
# ------------------------------------------------------------------------


# ------------------------------------------------------------------------
# default settings (for LINUX, etc.)
# ------------------------------------------------------------------------

ifeq "$(PLATFORM)" "LINUX"

  # - - - - - - - - - - - - - - - - - - - - -
  # Description of GNU compiler options used:
  # - - - - - - - - - - - - - - - - - - - - -
  #  -g     Produce symbolic info in the object file for debugger
  #  -O0    Generate non-optimized code sequences
  #  -wall                 Warning level
  #  -fsigned-char         Change char default from unsigned to signed
  #  -D_GNU_SOURCE         Enable extra prototypes in "pthread.h".
  #  -pthread              Compile for multithreaded programs, equivalent
  #                          to -D_REENTRANT and -lpthread
  #  -D_THREAD_SAFE	 Compile for multithreaded programs
  #   Note: on Suse LINUX the _THREAD_SAFE or _REENTRANT is not being defined
  #       when -pthread option is present. To compile glbsem.h properly we
  #       need to define one of these defines explicitly here.

# set compiler
PLATFORM_CFLAGS = -O0 -Wall -fsigned-char -D_GNU_SOURCE -D_THREAD_SAFE -pthread
# set linker
# on LINUX g++ linker is needed to link C++ libraries
PLATFORM_LINKER  = $(CC)
PLATFORM_LDFLAGS =
PLATFORM_LIBS    = -lpthread -lrt

# set archive
ARFLAGS = -r

# set MMS-LITE
ALIGNDIR = ../../mvl/util/foundry/linux

# NOTE: To disable multithread support: remove -D_THREAD_SAFE -pthread from
#       PLATFORM_CFLAGS and -lpthread from PLATFORM_LIBS.
endif

# ------------------------------------------------------------------------
# settings for QNX
# ------------------------------------------------------------------------

ifeq "$(PLATFORM)" "QNX"

  # - - - - - - - - - - - - - - - - - - - - -
  # Description of QNX compiler options used:
  # - - - - - - - - - - - - - - - - - - - - -
  #
  #  -c     Suppress the link phase and retain object files
  #  -g     Produce symbolic info in the object file for debugger
  #  -Od    Generate non-optimized code sequences
  #  -Wc,-s No stack overflow checking (Watcom compiler)
  #  -w3    Warning level
  #  -j     Change char default from unsigned to signed

PLATFORM_CFLAGS = -j -w3 -Od

PLATFORM_LINKER  = $(CC)
PLATFORM_LDFLAGS =
PLATFORM_LIBS    =

ARFLAGS = -n -q

ALIGNDIR = ../../mvl/util/foundry/qnx

endif

# ------------------------------------------------------------------------
# settings for LYNX
# ------------------------------------------------------------------------

ifeq "$(PLATFORM)" "LYNX"

PLATFORM_CFLAGS = -O0 -Wall -fsigned-char -D__LYNX

PLATFORM_LINKER  = $(CC)
PLATFORM_LDFLAGS =
PLATFORM_LIBS    = -lbsd

ARFLAGS = -r

ALIGNDIR = ../../mvl/util/foundry/lynx

endif

# ------------------------------------------------------------------------
# settings for AIX
# ------------------------------------------------------------------------

ifeq "$(PLATFORM)" "AIX"

# set compiler
PLATFORM_CFLAGS = -qchars=signed -flag=w:e -qcpluscmt -qmaxmem=8192 -qOPT=0
  #- - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - -
  # Compiler mode xlC_r:
  # "Invokes the compiler so that source files are compiled as C++ language
  # source code. Files with .c suffixes, assuming you have not used
  # the -+ compiler option, are compiled as C language source code with a
  # default language level of ansi, and compiler option -qansialias to allow
  # type-based aliasing. All _r-suffixed invocations additionally set the macro
  # names -D_THREAD_SAFE and add the libraries -L/usr/lib/threads,
  #  -lc_r and -lpthreads. The compiler option -qthreaded is also added."
  #- - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - -
CC=xlC_r

# set linker
PLATFORM_LINKER  = xlC_r
PLATFORM_LDFLAGS =
PLATFORM_LIBS    = -lpthreads -lm

ARFLAGS = -r

ALIGNDIR = ../../mvl/util/foundry/aix

# NOTE: To disable multithread support: change xlC_r to xlC and remove -lpthread -lm
#       from PLATFORM_LIBS.
endif

# ------------------------------------------------------------------------
# add other platforms as needed
# ------------------------------------------------------------------------
