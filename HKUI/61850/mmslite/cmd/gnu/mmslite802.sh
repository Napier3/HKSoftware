##########################################################################
# mmslite802.sh								 #
# Build file for making MMS-Lite for LINUX, QNX, etc.
# Use the first command line arg ($1) to specify the platform.
# Use the second command line arg ($2) to pass param to make (like clean).
# if $1=AIX 	Build for the AIX platform
# if $1=LYNX	Build for the LYNX platform
# if $1=LINUX	Build for the LINUX platform (default if $1 is empty)
# if $1=QNX	Build for the QNX platform
#									 #
# Examples:
#   ./mmslite802.sh LINUX
#   ./mmslite802.sh LINUX clean
#									 #
# NOTE: *ositp4e.mak, *ositpxe.mak, iecgoose.mak only work on LINUX.
#	However, these makefiles should be usable on other platforms if
#	"clnp_linux.c" is replaced with a file ported to each platform.
#									 #
##########################################################################
# MODIFICATION LOG :	       						 #
#  Date     Who   Rev			Comments			 #
# --------  ---  ------   -----------------------------------------------#
# 03/08/07  JRB    14     Add sositpxs0, uositpxs0.
# 12/01/06  JRB    13     Add ositpxs, smpval, cositpxs0, scl_tpxs0.
# 11/17/06  JRB    12     Add gse_mgmt, gse_mgmt_test
# 11/13/06  JRB    11     Del client, server, uca_srvr sample executables
#			  (they all link to ositcpe lib).
#			  Del "*ositp4e", "*ositpxe" sample executables.
# 08/16/05  RKR    10     Renamed
# 08/15/05  JRB    09     Changed name to make802.sh
# 08/08/05  EJV    08     Added arg $2, and test for correct args
#			  Rem setting AIX compiler mode (see platform.mak)
#			  Export PLATFORM variable once for all makefiles.
# 08/03/05  JRB    07     Add *ositp4e.mak, *ositpxe.mak, iecgoose.mak.
# 08/16/04  JRB    06     Use "X_$1" in "if test" to work w/ NO arg on cmdline
# 08/04/04  EJV    05     Added AIX support.
# 07/19/04  JRB    04     Add scl_srvr.mak.
# 03/15/04  GLB    03     Copy sockets executables to "/usr/bin".
# 11/18/03  JRB    02     Add ositcps_*.a, *ositcps0_ld, ssec0_*.a 
#			  Pass PLATFORM=$1 to each make command
#			   to allow use on QNX, etc.
# 12/09/02  CRM    01     Created mkall.sh from QNX script file		 #
##########################################################################
##########################################################################
#  MAKE ALL LIBRARIES 							 #
##########################################################################

# ------------------------------------------------------------------------
#  NOTE: The platform.mak included in every makefile specifies pthreads
#        support if available. There is small performance penalty when
#        multithreading support is enabled.
#        The platform.mak shows how to disable multithreading support.
# ------------------------------------------------------------------------


# check if correct parameters were passed
if test -z "$1"; then
  echo "No command-line arguments. Must specify platform (LINUX, QNX, etc.)"
  exit 0
fi

if test "$1" = "clean"; then
  echo "Must specify platform in first argument (LINUX, QNX, etc.)"
  exit 0
fi

if test "$1" = "LINUX" -o "$1" = "LYNX" -o "$1" = "QNX" -o "$1" = "AIX"; then
  if test -z "$2"; then
    echo "==============================="
    echo "= Making platform: $1"
    echo "==============================="
    mkdir obj_l
    mkdir obj_n
    mkdir obj_ld
    mkdir obj_nd

    mkdir obj_mvlu_l
    mkdir obj_mvlu_n
    mkdir obj_mvlu_ld
    mkdir obj_mvlu_nd

    mkdir obj_ositcpe_l
    mkdir obj_ositcpe_n
    mkdir obj_ositcpe_ld
    mkdir obj_ositcpe_nd

    mkdir obj_ositcps_l
    mkdir obj_ositcps_n
    mkdir obj_ositcps_ld
    mkdir obj_ositcps_nd

    mkdir obj_foundry_ld
    mkdir obj_mmslog_ld

    mkdir obj_cositcpe_ld
    mkdir obj_sositcpe_ld
    mkdir obj_uositcpe_ld

    mkdir obj_cositcps0_ld
    mkdir obj_sositcps0_ld
    mkdir obj_uositcps0_ld

    mkdir obj_scl_srvr_ld

    if test "$1" != "QNX"; then
      mkdir obj_ositp4e_l
      mkdir obj_ositp4e_n
      mkdir obj_ositp4e_ld
      mkdir obj_ositp4e_nd

      mkdir obj_ositpxe_l
      mkdir obj_ositpxe_n
      mkdir obj_ositpxe_ld
      mkdir obj_ositpxe_nd

      mkdir obj_ositpxs_l
      mkdir obj_ositpxs_n
      mkdir obj_ositpxs_ld
      mkdir obj_ositpxs_nd

      mkdir obj_cositp4e_ld
      mkdir obj_sositp4e_ld
      mkdir obj_uositp4e_ld

      mkdir obj_cositpxe_ld
      mkdir obj_sositpxe_ld
      mkdir obj_uositpxe_ld

      mkdir obj_cositpxs0_ld
      mkdir obj_sositpxs0_ld
      mkdir obj_uositpxs0_ld
      mkdir obj_scl_tpxs0_ld

      mkdir obj_iecgoose_ld
      mkdir obj_gse_mgmt_ld
    fi
  else
    if test "$2" = "clean"; then
      rm -f cc.lst
      rm -f foundry.tmp
      echo "==============================="
      echo "= Cleaning platform: $1"
      echo "==============================="
    else
      echo "ERROR: invalid second argument: $2"
      exit 0
    fi
  fi
else
  echo "ERROR: unsupported platform: $1"
  exit 0
fi


export PLATFORM=$1


# make directories
if test ! -d ../../lib; then
  mkdir ../../lib
fi
if test ! -d ../../bin; then
  mkdir ../../bin
fi


# set path to GNU make
if test "$1" = "AIX"; then
  alias make='/usr/local/bin/make'
fi


echo STARTING MAKE OF meml_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f meml.mak $2             DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF meml_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f meml.mak $2             DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF meml_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f meml.mak $2      OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF meml_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f meml.mak $2      OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF mem_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f mem.mak $2              DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF mem_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f mem.mak $2              DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF mem_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f mem.mak $2       OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF mem_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f mem.mak $2       OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF smem_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f smem.mak $2             DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF smem_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f smem.mak $2             DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF smem_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f smem.mak $2      OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF smem_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f smem.mak $2      OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF slog_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f slog.mak $2             DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF slog_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f slog.mak $2             DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF slog_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f slog.mak $2      OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF slog_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f slog.mak $2      OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF asn1l_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f asn1l.mak $2            DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF asn1l_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f asn1l.mak $2            DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF asn1l_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f asn1l.mak $2     OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF asn1l_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f asn1l.mak $2     OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF mmsl_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f mmsl.mak $2             DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF mmsl_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f mmsl.mak $2             DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF mmsl_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f mmsl.mak $2      OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF mmsl_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f mmsl.mak $2      OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF mmsle_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f mmsle.mak $2            DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF mmsle_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f mmsle.mak $2            DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF mmsle_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f mmsle.mak $2     OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF mmsle_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f mmsle.mak $2     OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF ositcpe_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositcpe.mak $2          DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF ositcpe_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositcpe.mak $2          DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF ositcpe_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositcpe.mak $2   OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF ositcpe_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositcpe.mak $2   OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF ositcps_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositcps.mak $2          DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF ositcps_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositcps.mak $2          DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF ositcps_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositcps.mak $2   OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF ositcps_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositcps.mak $2   OPT=-g DFLAG=_nd                       # no logging / debug

# CANNOT MAKE THESE ON QNX BECAUSE 'TP4' TRANPORT NOT PORTED
if test "$1" != "QNX"; then

echo STARTING MAKE OF ositp4e_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositp4e.mak $2        DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF ositp4e_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositp4e.mak $2        DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF ositp4e_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositp4e.mak $2 OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF ositp4e_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositp4e.mak $2 OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF ositpxe_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositpxe.mak $2        DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF ositpxe_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositpxe.mak $2        DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF ositpxe_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositpxe.mak $2 OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF ositpxe_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositpxe.mak $2 OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF ositpxs_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositpxs.mak $2        DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF ositpxs_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositpxs.mak $2        DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF ositpxs_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositpxs.mak $2 OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF ositpxs_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f ositpxs.mak $2 OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF gse_mgmt_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f gse_mgmt.mak $2        DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF gse_mgmt_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f gse_mgmt.mak $2        DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF gse_mgmt_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f gse_mgmt.mak $2 OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF gse_mgmt_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f gse_mgmt.mak $2 OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF smpval_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f smpval.mak $2        DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF smpval_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f smpval.mak $2        DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF smpval_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f smpval.mak $2 OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF smpval_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f smpval.mak $2 OPT=-g DFLAG=_nd                       # no logging / debug

fi

echo STARTING MAKE OF ssec0_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f ssec0.mak $2          DFLAG=_l   DEFS=-DDEBUG_SISCO     # logging    / no debug
echo STARTING MAKE OF ssec0_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f ssec0.mak $2          DFLAG=_n                          # no logging / no debug
echo STARTING MAKE OF ssec0_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f ssec0.mak $2   OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO     # logging    / debug
echo STARTING MAKE OF ssec0_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f ssec0.mak $2   OPT=-g DFLAG=_nd                         # no logging / debug

echo STARTING MAKE OF slistend EXECUTABLE for $1 >> cc.lst 2>&1
make -f slistend.mak $2  OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF sreadd EXECUTABLE for $1 >> cc.lst 2>&1
make -f sreadd.mak $2    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF mvl_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f mvl.mak $2              DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF mvl_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f mvl.mak $2              DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF mvl_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f mvl.mak $2       OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF mvl_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f mvl.mak $2       OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF mvlu_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f mvlu.mak $2             DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF mvlu_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f mvlu.mak $2             DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF mvlu_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f mvlu.mak $2      OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF mvlu_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f mvlu.mak $2      OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF util_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f util.mak $2             DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF util_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f util.mak $2             DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF util_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f util.mak $2      OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF util_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f util.mak $2      OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF mlogl_l.a LIBRARY for $1  >> cc.lst 2>&1
make -f mlogl.mak $2            DFLAG=_l   DEFS=-DDEBUG_SISCO   # logging    / no debug
echo STARTING MAKE OF mlogl_n.a LIBRARY for $1  >> cc.lst 2>&1
make -f mlogl.mak $2            DFLAG=_n                        # no logging / no debug
echo STARTING MAKE OF mlogl_ld.a LIBRARY for $1  >> cc.lst 2>&1
make -f mlogl.mak $2     OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug
echo STARTING MAKE OF mlogl_nd.a LIBRARY for $1  >> cc.lst 2>&1
make -f mlogl.mak $2     OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF findalgn_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f findalgn.mak $2  OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF mbufcalc_nd EXECUTABLE for $1 >> cc.lst 2>&1
make -f mbufcalc.mak $2  OPT=-g DFLAG=_nd                       # no logging / debug

echo STARTING MAKE OF foundry_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f foundry.mak $2   OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF mmslog_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f mmslog.mak $2    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

#
# The following executables link to the "ositcps" library.
#
echo STARTING MAKE OF cositcps0_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f cositcps0.mak $2    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF sositcps0_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f sositcps0.mak $2    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF uositcps0_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f uositcps0.mak $2    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF scl_srvr_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f scl_srvr.mak $2     OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

# CANNOT MAKE THESE ON QNX BECAUSE 'TP4' TRANPORT NOT PORTED
if test "$1" != "QNX"; then

#
# The following executables link to the "ositpxs" library.
#
echo STARTING MAKE OF cositpxs0_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f cositpxs0.mak $2    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF sositpxs0_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f sositpxs0.mak $2    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF uositpxs0_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f uositpxs0.mak $2    OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

echo STARTING MAKE OF scl_tpxs0_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f scl_tpxs0.mak $2     OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

#
# The following executable tests the IEC-61850 GOOSE Framework.
#
echo STARTING MAKE OF iecgoose_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f iecgoose.mak $2  OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

#
# The following executable tests the IEC 61850 GSE Management.
#
echo STARTING MAKE OF gse_mgmt_ld EXECUTABLE for $1 >> cc.lst 2>&1
make -f gse_mgmt_test.mak $2  OPT=-g DFLAG=_ld  DEFS=-DDEBUG_SISCO   # logging    / debug

fi

#
# Copy sockets executables to "/usr/bin".
# NOTE: if a different path is preferred, these commands should be changed appropriately.
#
cp ../../bin/slistend /usr/bin
cp ../../bin/sreadd   /usr/bin
