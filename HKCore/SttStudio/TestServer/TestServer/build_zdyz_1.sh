#!/bin/bash
###############################################################################
#
###############################################################################

#------------------------------------------------------------------------------
# 编译工具
#------------------------------------------------------------------------------
# => ARCH指明目标体系架构，即编译好的内核运行在什么平台上，如x86_64或arm
# => Select CPU types (arm, arm64)
export ARCHXPLATFOR=linux-arm-gnueabi-g++

# => Scale the maximum concurrency with the number of CPUs.
# http://www.verydemo.com/demo_c131_i121360.html
NUMBER_THREADS=`cat /proc/cpuinfo | grep "processor" | wc -l`
# Do not run with really big numbers unless you want your machine to be dog-slow!
if [ ${NUMBER_THREADS} -le 8 ] ; then
    export MAKE_JOBS="-j${NUMBER_THREADS}"
    export PARALLEL_MAKE="-j${NUMBER_THREADS}"
else
    export MAKE_JOBS="-j`expr ${NUMBER_THREADS} / 2`"
    export PARALLEL_MAKE="-j`expr ${NUMBER_THREADS} / 2`"
fi

#------------------------------------------------------------------------------
# 项目基本设置
#------------------------------------------------------------------------------
# => QT5 Version (V5.x.x)
export QT5_MAJOR_VERSION=5
export QT5_MINOR_VERSION=13
export QT5_PATCH_VERSION=2
export QT5_VERSION=${QT5_MAJOR_VERSION}.${QT5_MINOR_VERSION}.${QT5_PATCH_VERSION}

# => QT5 Source
export QT_QT5_SRC_DIR=/home/zy/work_hf/qt-everywhere-src-5.13.2

# => QT5 Library
export QTDIR=/home/zy/work_hf/arm-qt-full
export QT_QT5_LIB_DIR=/home/zy/work_hf/arm-qt-full
export PATH=${QT_QT5_LIB_DIR}/bin:${PATH}
export LD_LIBRARY_PATH=${QT_QT5_LIB_DIR}/lib:${LD_LIBRARY_PATH}

#------------------------------------------------------------------------------
# => The end
#------------------------------------------------------------------------------


###############################################################################
export QMAKESPEC=${QTDIR}/mkspecs/$ARCHXPLATFOR
export PATH=$PATH:${QTDIR}/bin/

qmake && make
#qmake CONFIG+=debug && make

# => The end
###############################################################################
